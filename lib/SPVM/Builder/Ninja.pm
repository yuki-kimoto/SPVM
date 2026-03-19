package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;

use SPVM::Builder::Accessor 'has';

has [qw(
  log_dir
  log_entries_h
  log_fh
)];

sub new {
  my $class = shift;
  
  my $self = {
    log_entries_h => {},
    @_
  };
  
  return bless $self, ref $class || $class;
}

sub open_ninja_log {
  my ($self) = @_;

  return if $self->{log_fh};

  my $log_dir_name = $self->log_dir;
  my $log_file = "$log_dir_name/.ninja_log";
  my $must_write_header = !-f $log_file;

  open my $fh, '>>', $log_file or die "Can't open $log_file for appending: $!";
  
  binmode $fh;

  if ($must_write_header) {
    print $fh "# ninja log v5\x0A";
  }

  $self->{log_fh} = $fh;
}

sub add_ninja_log {
  my ($self, $new_record_h) = @_;

  my $fh = $self->{log_fh} 
    or die "Ninja log is not open. Call open_ninja_log() first.";

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

sub close_ninja_log {
  my ($self) = @_;
  
  if (my $fh = delete $self->{log_fh}) {
    close $fh;
  }
}

sub load_ninja_log {
  my ($self) = @_;

  my $log_dir_name = $self->log_dir;
  my $log_file = "$log_dir_name/.ninja_log";
  my $log_entries_h = {};

  # Return an empty hash if the log file does not exist
  if (!-f $log_file) {
    $self->log_entries_h($log_entries_h);
    return $log_entries_h;
  }

  open my $fh, '<', $log_file or die "Can't open $log_file for reading: $!";
  
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
  if ($log_entries_h && defined $command) {
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

1;