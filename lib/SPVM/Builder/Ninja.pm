package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;
use Digest::SHA;
use Carp 'confess';
use File::Path 'mkpath';

use SPVM::Builder::Accessor 'has';

has [qw(
  log_dir
  log_file_base_name
  log_entries_h
  log_fh
  log_entries_length
  header_exts
)];

sub new {
  my $class = shift;
  
  my $self = {
    log_entries_h => {},
    log_file_base_name => '.ninja_log',
    log_entries_length => 0,
    header_exts => [qw(h hpp hh hxx h++ inc inl c cpp cc cxx c++)],
    @_
  };
  
  bless $self, ref $class || $class;
  
  my $log_file = $self->log_file;
  
  unless (-f $log_file) {
    $self->create_log;
  }
  
  $self->load_log;
  
  $self->recompact_if_needed;
  
  $self->open_log;
  
  return $self;
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

sub create_log {
  my ($self) = @_;
  
  # Create the log directory if it does not exist
  my $log_dir = $self->log_dir;
  unless (-d $log_dir) {
    mkpath($log_dir)
      or confess("Can't create directory $log_dir: $!");
  }
  
  my $log_file = $self->log_file;
  
  open my $fh, '>', $log_file or confess("Can't open $log_file for appending: $!");
  binmode $fh;
  
  print $fh "# ninja log v5\x0A";
}

sub open_log {
  my ($self) = @_;
  
  if ($self->{log_fh}) {
    return ;
  }
  my $log_file = $self->log_file;
  
  open my $fh, '>>', $log_file
    or confess("Can't open $log_file for appending: $!");
  
  $self->{log_fh} = $fh;
}

sub add_log {
  my ($self, $new_log_entry_h) = @_;
  
  my $fh = $self->{log_fh};
  unless (defined $fh) {
    confess("Ninja log is not open. Call open_log() first.");
  }

  my $output_file = $new_log_entry_h->{output_file};
  unless (defined $output_file) {
    confess("output_file must be defined.");
  }

  my $command_hash = $new_log_entry_h->{command_hash};
  unless (defined $command_hash) {
    confess("command_hash must be defined.");
  }

  my $start_time = $new_log_entry_h->{start_time};
  unless (defined $start_time) {
    confess("start_time must be defined.");
  }

  my $end_time = $new_log_entry_h->{end_time};
  unless (defined $end_time) {
    confess("end_time must be defined.");
  }

  my $mtime = $new_log_entry_h->{mtime};
  unless (defined $mtime) {
    confess("mtime must be defined.");
  }

  my $normalized_output_file = SPVM::Builder::Util::normalize_path($output_file, $self->log_dir);

  my $log_entry_line = sprintf("%d\t%d\t%d\t%s\t%s\x0A", 
    $start_time, 
    $end_time, 
    $mtime, 
    $normalized_output_file, 
    $command_hash);
    
  print $fh $log_entry_line;
  
  $new_log_entry_h->{mtime} = $mtime;
  $self->log_entries_h->{$normalized_output_file} = $new_log_entry_h;
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
  my $log_entries_length = 0;
  
  open my $log_fh, '<', $log_file
    or confess "Cannot open the log file '$log_file':$!";
  
  while (my $line = <$log_fh>) {
    $line =~ s/[\x0A\x0D]+$//;

    next if $line =~ /^#/;

    my @fields = split(/\t/, $line);

    if (@fields >= 5) {
      my ($start_time, $end_time, $mtime, $normalized_output_file, $command_hash) = @fields;

      $log_entries_h->{$normalized_output_file} = {
        start_time   => $start_time,
        end_time     => $end_time,
        mtime        => $mtime,
        output_file  => $normalized_output_file,
        command_hash => $command_hash,
      };
      
      $log_entries_length++;
    }
  }
  
  $self->log_entries_length($log_entries_length);
  
  $self->log_entries_h($log_entries_h);
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

sub need_generate_v2 {
  my ($self, $options) = @_;
  
  my $force       = $options->{force};
  my $output_file = $options->{output_file};
  unless (defined $output_file) {
    confess("output_file must be defined.");
  }
  
  my $command     = $options->{command};
  unless (defined $command ) {
    confess("command must be defined.");
  }
  
  my $input_files = $options->{input_files};
  unless (defined $input_files) {
    confess("input_files must be defined.");
  }
  
  my $need_generate = 0;

  if ($force) {
    $need_generate = 1;
  }
  elsif (!-f $output_file) {
    $need_generate = 1;
  }
  else {
    # Generate a robust hash of the command and the content of input files
    my $current_command_hash = $self->create_command_hash({
      command     => $command,
      input_files => $input_files,
    });

    # Retrieve the recorded log entry for the output file
    my $log_entries_h = $self->log_entries_h;
    my $normalized_output_file = SPVM::Builder::Util::normalize_path($output_file, $self->log_dir);
    my $log_entry = $log_entries_h->{$normalized_output_file};

    # If the entry doesn't exist, or the hash simply doesn't match, rebuild.
    # $log_entry->{command_hash} が undef の場合も ne で真になるからこれで十分や。
    if (!$log_entry || $current_command_hash ne $log_entry->{command_hash}) {
      $need_generate = 1;
    }
  }

  return $need_generate;
}

sub recompact_if_needed {
  my ($self) = @_;
  
  unless ($self->log_entries_h) {
    confess("Entries are not loaded.");
  }
  
  # Ninja's threshold: Recompact if total log entries > 3 * valid log entries
  my $threshold = 3;
  my $log_entries_length = $self->log_entries_length;
  my $log_entries_h = $self->log_entries_h;
  my $do_recompact = $log_entries_length > $threshold * keys %$log_entries_h;
  
  if ($do_recompact) {
    my $log_file = $self->log_file;
    
    unlink $log_file
      or confess("Cannot unlink the file '$log_file': $!");
    
    $self->create_log;
    
    $self->open_log;
    
    # Sort by start_time (ascending)
    my @normalized_output_files = sort {
      $log_entries_h->{$a}{start_time} <=> $log_entries_h->{$b}{start_time}
    } keys %$log_entries_h;
    
    # Write each valid log entry
    for my $normalized_output_file (@normalized_output_files) {
      my $log_entory_h = $log_entries_h->{$normalized_output_file};
      $self->add_log($log_entory_h);
    }
    
    $self->log_entries_length(keys %$log_entries_h);
    
    $self->close_log;
  }
}

sub create_command_hash {
  my ($self, $options) = @_;

  my $input_files = $options->{input_files} || [];
  my $command     = $options->{command} // '';
  
  # Get extensions from the object accessor (default or user-defined in new)
  my $extensions = $self->header_exts || [];
  
  # Build the regex from the extension array with proper escaping
  my $ext_list = join '|', map { quotemeta $_ } @$extensions;
  my $valid_ext_re = qr/\.(?:$ext_list)$/i;

  my @all_input_files;

  for my $path (@$input_files) {
    if (-d $path) {
      require File::Find;
      File::Find::find({
        wanted => sub {
          my $full_path = $File::Find::name;
          
          # Extract the base name for hidden file and extension checks
          my $base_name = $full_path;
          $base_name =~ s|.*/||; 

          # Check if the path is a file and matches the allowed C/C++ extensions
          if (-f $full_path && $base_name =~ $valid_ext_re) {
            push @all_input_files, $full_path;
          }
        },
        no_chdir    => 1,
        follow      => 1,
        follow_skip => 2,
      }, $path);
    }
    elsif (-f $path) {
      # Directly specified files are always included
      push @all_input_files, $path;
    }
  }

  # Sort input files by name to ensure consistent hash generation
  @all_input_files = sort @all_input_files;

  my $sha = Digest::SHA->new(1);

  # Add SHA1 of the command string followed by a newline
  $sha->add(Digest::SHA::sha1_hex($command) . "\x0A");

  for my $input_file (@all_input_files) {
    
    # Add SHA1 of the file path followed by a newline
    my $normalized_input_file = SPVM::Builder::Util::normalize_path($input_file, $self->log_dir);
    $sha->add(Digest::SHA::sha1_hex($normalized_input_file) . "\x0A");
    
    # Add SHA1 of the file content followed by a newline
    $sha->addfile($input_file);
    $sha->add("\x0A");
  }

  return $sha->hexdigest;
}

sub DESTROY {
  my ($self) = @_;
  
  # Ensure the log file handle is closed
  $self->close_log;
}

1;