package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Accessor 'has';

has [qw(
  log_dir
  log_file_base_name
  log_entries_h
  log_fh
)];

sub new {
  my $class = shift;
  
  my $self = {
    log_entries_h => {},
    log_file => '.ninja_log',
    @_
  };
  
  return bless $self, ref $class || $class;
}

sub log_file {
  my ($self) = @_;

  my $log_dir = $self->log_dir;

  # Raise an exception if log_dir is not defined
  unless (defined $log_dir) {
    confess("The \"log_dir\" property must be defined");
  }

  my $log_file_base_name = $self->log_file_base_name;
  my $log_file = "$log_dir/$log_file_base_name";

  return $log_file;
}

sub open_log {
  my ($self) = @_;

  return if $self->{log_fh};

  my $log_file = $self->log_file;
  my $must_write_header = !-f $log_file;

  open my $fh, '>>', $log_file or confess("Can't open $log_file for appending: $!");
  
  binmode $fh;

  if ($must_write_header) {
    print $fh "# ninja log v5\x0A";
  }

  $self->{log_fh} = $fh;
}

sub add_log {
  my ($self, $new_record_h) = @_;

  my $fh = $self->{log_fh} 
    or confess("Ninja log is not open. Call open_log() first.");

  my $output_file  = $new_record_h->{output_file};
  my $command_hash = $new_record_h->{command_hash};

  $self->log_entries_h->{$output_file} = $new_record_h;

  my $start_time = $new_record_h->{start_time} || 0;
  my $end_time   = $new_record_h->{end_time}   || 0;
  my $mtime      = $new_record_h->{mtime}      || 0;

  my $record = sprintf("%d\t%d\t%d\t%s\t%s\x0A", 
    $start_time, 
    $end_time, 
    $mtime, 
    $output_file, 
    $command_hash);
    
  print $fh $record;
}

sub close_log {
  my ($self) = @_;
  
  if (my $fh = delete $self->{log_fh}) {
    close $fh;
  }
}

sub load_log {
  my ($self) = @_;

  my $log_file = $self->log_file;
  my $log_entries_h = {};

  # Return an empty hash if the log file does not exist
  if (!-f $log_file) {
    $self->log_entries_h($log_entries_h);
    return $log_entries_h;
  }

  open my $fh, '<', $log_file or confess("Can't open $log_file for reading: $!");
  
  # Use binary mode to handle physical LF (0x0A) consistently across platforms
  binmode $fh;

  while (my $line = <$fh>) {
    # Remove the physical LF (0x0A) and optional CR (0x0D) just in case
    $line =~ s/[\x0A\x0D]+$//;

    # Skip the Ninja version header (e.g., "# ninja log v5")
    next if $line =~ /^#/;

    # Parse tab-separated values
    my @fields = split(/\t/, $line);

    if (@fields >= 5) {
      my ($start_time, $end_time, $mtime, $output_file, $command_hash) = @fields;

      # Store the record.
      $log_entries_h->{$output_file} = {
        start_time   => $start_time,
        end_time     => $end_time,
        mtime        => $mtime,
        output_file  => $output_file,
        command_hash => $command_hash,
      };
    }
  }

  close $fh;

  # Update internal state
  $self->log_entries_h($log_entries_h);

  return $log_entries_h;
}

sub need_generate {
  my ($self, $options) = @_;
  
  my $log_entries_h = $self->log_entries_h;
  
  my $force       = $options->{force};
  my $input_files = $options->{input_files} || [];
  my $output_file = $options->{output_file};
  my $command     = $options->{command};
  
  # Always generate if force is true
  if ($force) {
    return 1;
  }

  # Generate if output file does not exist
  if (!-f $output_file) {
    return 1;
  }
  
  # If command_hash differs, rebuild.
  if (defined $command) {
    my $entry = $log_entries_h->{$output_file};
    
    if ($entry) {
      my $last_command_hash = $entry->{command_hash}; 
      
      my $sha = Digest::SHA->new(1);
      $sha->add($command);
      my $current_command_hash = $sha->hexdigest;

      if (!defined $last_command_hash || $current_command_hash ne $last_command_hash) {
        return 1;
      }
    } else {
      # No log entry found for this file; treat as a new or modified build rule
      return 1;
    }
  }

  # Timestamp-based check
  my $input_files_mtime_max = 0;
  my $exists_input_file = 0;

  for my $input_file (@$input_files) {
    if (-f $input_file) {
      $exists_input_file = 1;
      my $mtime = (Time::HiRes::stat($input_file))[9];
      if ($mtime > $input_files_mtime_max) {
        $input_files_mtime_max = $mtime;
      }
    }
  }

  if ($exists_input_file) {
    my $spvm_version_header_file = SPVM::Builder::Util::get_spvm_version_header_file();
    if (-f $spvm_version_header_file) {
      my $version_mtime = (Time::HiRes::stat($spvm_version_header_file))[9];
      if ($version_mtime > $input_files_mtime_max) {
        $input_files_mtime_max = $version_mtime;
      }
    }

    my $output_file_mtime = (Time::HiRes::stat($output_file))[9];
    
    if ($input_files_mtime_max > $output_file_mtime) {
      return 1;
    }
  }

  return 0;
}

sub need_recompact {
  my ($self) = @_;

  my $log_file = $self->log_file;

  # Return 0 if the log file does not exist
  return 0 unless -f $log_file;

  # Count the total number of records in the log file
  my $total_count = 0;
  open my $fh, '<', $log_file or confess("Can't open $log_file for reading: $!");
  while (<$fh>) {
    $total_count++;
  }
  close $fh;

  # Number of valid records in memory
  my $log_entries_h = $self->log_entries_h;
  my $valid_count = keys %$log_entries_h;

  # Ninja's threshold: Recompact if total records > 3 * valid records
  if ($total_count > 3 * $valid_count) {
    return 1;
  }

  return 0;
}

sub recompact {
  my ($self) = @_;

  my $log_entries_h = $self->log_entries_h;

  # Get the log file path
  my $log_file = $self->log_file;

  # Delete the log file if it exists
  if (-f $log_file) {
    unlink $log_file or confess("Can't unlink $log_file: $!");
  }

  # Open the log file and write the header
  $self->open_log;

  # Get the file handle
  my $log_fh = $self->log_fh;

  # Sort by start_time (ascending)
  my @sorted_outputs = sort {
    $log_entries_h->{$a}{start_time} <=> $log_entries_h->{$b}{start_time}
  } keys %$log_entries_h;

  # Write each valid record
  for my $output_file (@sorted_outputs) {
    my $record_h = $log_entries_h->{$output_file};

    my $start_time   = $record_h->{start_time}   || 0;
    my $end_time     = $record_h->{end_time}     || 0;
    my $mtime        = $record_h->{mtime}        || 0;
    my $command_hash = $record_h->{command_hash} || '';

    my $record = sprintf("%d\t%d\t%d\t%s\t%s\x0A",
      $start_time,
      $end_time,
      $mtime,
      $output_file,
      $command_hash);

    print $log_fh $record;
  }
}

sub DESTROY {
  my ($self) = @_;

  # Ensure the log file handle is closed
  $self->close_log;
}
1;