package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;
use Digest::SHA;
use Carp 'confess';
use File::Path 'mkpath';
use Fcntl qw(:flock :seek :mode);
use SPVM::Builder::Accessor 'has';
use File::Find;
use Cwd ();
use File::Spec;

has [qw(
  log_dir
  log_file_base_name
  log_fh
  entries_h
  entries_length
  lock_file_base_name
  lock_fh
)];

sub new {
  my $class = shift;
  
  my $self = {
    entries_h => {},
    log_file_base_name => '.ninja_log',
    entries_length => 0,
    lock_file_base_name => '.ninja_lock',
    @_
  };
  
  bless $self, ref $class || $class;
  
  $self->prepare;
  
  return $self;
}

sub prepare {
  my ($self) = @_;
  
  $self->open_lock_file;
  
  $self->create_log;
  
  $self->open_log('+<');
  
  $self->recompact;
  
  $self->load_log;
}

sub log_file {
  my ($self) = @_;

  my $log_dir = $self->log_dir;

  # Raise an exception if log_dir is not defined
  unless (defined $log_dir) {
    confess("The \"log_dir\" field must be defined");
  }

  my $log_file_base_name = $self->log_file_base_name;
  my $log_file = "$log_dir/$log_file_base_name";

  return $log_file;
}

sub lock_file {
  my ($self) = @_;

  my $log_dir = $self->log_dir;

  # Raise an exception if log_dir is not defined
  unless (defined $log_dir) {
    confess("The \"log_dir\" field must be defined");
  }
  
  my $lock_file_base_name = $self->lock_file_base_name;
  my $lock_file = "$log_dir/$lock_file_base_name";

  return $lock_file;
}

sub open_lock_file {
  my ($self) = @_;
  
  mkpath $self->log_dir;
  
  my $lock_file = $self->lock_file;
  
  open my $lock_fh, '>>', $lock_file
    or confess("Cannot open the file '$lock_file' with '>>' mode:$!");
  
  $self->{lock_fh} = $lock_fh;
  
  return $lock_file;
}

sub open_log {
  my ($self, $mode) = @_;
  
  unless ($mode) {
    confess "The open mode \$mode must be defined.";
  }
  
  my $log_file = $self->log_file;
  
  if ($self->{log_fh}) {
    confess "The file '$log_file' is already opened";
  }
  
  open my $fh, $mode, $log_file
    or confess("Can't open '$log_file' with the mode '$mode': $!");
  
  $self->{log_fh} = $fh;
}

sub opened {
  my ($self) = @_;
  
  return $self->{log_fh} ? 1 : 0;
}

sub add_log {
  my ($self, @args) = @_;
  
  $self->write_lock_with_flush(sub {
    seek($self->log_fh, 0, SEEK_END)
      or confess("Can't seek to end: $!");
    $self->add_log_without_lock(@args);
  });
}

sub add_log_without_lock {
  my ($self, $new_entry_h, $options) = @_;
  
  $options //= {};
  
  my $fh = $self->{log_fh};
  unless (defined $fh) {
    confess("Ninja log is not open. Call open_log() first.");
  }

  my $output_file = $new_entry_h->{output_file};
  unless (defined $output_file) {
    confess("output_file must be defined.");
  }

  my $command_hash = $new_entry_h->{command_hash};
  unless (defined $command_hash) {
    confess("command_hash must be defined.");
  }

  my $start_time = $new_entry_h->{start_time};
  unless (defined $start_time) {
    confess("start_time must be defined.");
  }

  my $end_time = $new_entry_h->{end_time};
  unless (defined $end_time) {
    confess("end_time must be defined.");
  }

  my $mtime = $new_entry_h->{mtime};
  unless (defined $mtime) {
    confess("mtime must be defined.");
  }

  my $normalized_output_file = $options->{no_normalize_output_file} ? $output_file : SPVM::Builder::Util::normalize_path($output_file, $self->log_dir);
  
  my $entry_line = sprintf("%d\t%d\t%d\t%s\t%s\x0A", 
    $start_time, 
    $end_time, 
    $mtime, 
    $normalized_output_file, 
    $command_hash);
    
  print $fh $entry_line;
  
  $new_entry_h->{mtime} = $mtime;
  $self->entries_h->{$normalized_output_file} = $new_entry_h;
}

sub close_log {
  my ($self) = @_;
  
  if (my $fh = delete $self->{log_fh}) {
    close $fh;
  }
}

sub add_log_header {
  my ($self, @args) = @_;
  
  $self->write_lock_with_flush(sub {
    seek($self->log_fh, 0, SEEK_END)
      or confess("Can't seek to end: $!");
    $self->add_log_header_without_lock(@args);
  });
  
}

sub add_log_header_without_lock {
  my ($self) = @_;
  
  my $log_fh = $self->log_fh;
  
  print $log_fh "# ninja log v5\x0A";
}

sub load_log {
  my ($self, @args) = @_;
  
  $self->read_lock(sub {
     $self->load_log_without_lock(@args);
  });
  
}

sub load_log_without_lock {
  my ($self) = @_;
  
  my $entries_h = {};
  my $entries_length = 0;
  
  my $log_fh = $self->log_fh;
  seek($log_fh, 0, SEEK_SET);
  
  while (my $line = <$log_fh>) {
    $line =~ s/[\x0A\x0D]+$//;

    next if $line =~ /^#/;

    my @fields = split(/\t/, $line);

    if (@fields >= 5) {
      my ($start_time, $end_time, $mtime, $normalized_output_file, $command_hash) = @fields;

      $entries_h->{$normalized_output_file} = {
        start_time   => $start_time,
        end_time     => $end_time,
        mtime        => $mtime,
        output_file  => $normalized_output_file,
        command_hash => $command_hash,
      };
      
      $entries_length++;
    }
  }
  
  $self->entries_length($entries_length);
  
  $self->entries_h($entries_h);
  
  seek($log_fh, 0, SEEK_END);
}

sub need_generate {
  my ($self, $options) = @_;
  
  my $command_hash = $options->{command_hash};
  unless (defined $command_hash) {
    confess("'command_hash' option must be defined.");
  }
  
  my $output_file = $options->{output_file};
  unless (defined $output_file) {
    confess("'output_file' option must be defined.");
  }
  
  my $need_generate = 0;
  
  if (!-f $output_file) {
    $need_generate = 1;
  }
  else {
    # Retrieve the recorded log entry for the output file
    my $entries_h = $self->entries_h;
    my $normalized_output_file = SPVM::Builder::Util::normalize_path($output_file, $self->log_dir);
    my $entry = $entries_h->{$normalized_output_file};
    
    # If the entry doesn't exist, or the hash simply doesn't match, rebuild.
    if (!$entry || $command_hash ne $entry->{command_hash}) {
      $need_generate = 1;
    }
  }

  return $need_generate;
}

my %NORMALIZE_PATH_CACHE;
my %DEPENDENT_CONTENT_CACHE;
my %DEPENDANT_FILE_HASH_CACHE;
my %STAT_RESULT_CACHE;

sub create_command_hash {
  my ($self, $options) = @_;
  
  my $command = $options->{command}
    // confess("'command' option must be defined.");
  
  my $command_version = $options->{command_version}
    // confess("'command_version' option must be defined.");
  
  my $dependent_files = $options->{dependent_files}
    // confess("'dependent_files' optioon must be defined.");
  
  my $log_dir = $self->log_dir;
  
  # Create regex for dependent file exclusion extensions
  # Get exclude extensions from environment variable: Comma-separated, no dots, trim whitespace
  my $env_dependent_file_exclude_exts = $ENV{SPVM_DEPENDENT_FILE_EXCLUDE_EXTS} // '';
  my @dependent_file_exclude_exts_list = grep { length $_ } map { s/^\s+|\s+$//gr } split(/,/, $env_dependent_file_exclude_exts);
  my $dependent_file_exclude_exts_pattern = join('|', map { quotemeta $_ } @dependent_file_exclude_exts_list);
  my $dependent_file_exclude_exts_re = $dependent_file_exclude_exts_pattern ? qr/(?:$dependent_file_exclude_exts_pattern)$/i : qr/$^/;
  
  my $sha = Digest::SHA->new(1);
  $sha->add(Digest::SHA::sha1_hex($command));
  $sha->add(Digest::SHA::sha1_hex($command_version));
  
  @$dependent_files = sort grep { length $_ } @$dependent_files;
  for my $dependent_file (@$dependent_files) {
    my $dependant_file_hash = $DEPENDANT_FILE_HASH_CACHE{$dependent_file};
    unless (defined $dependant_file_hash) {
      my @child_dependent_files;
      
      # Check cache or fetch lstat
      my $state_result = $STAT_RESULT_CACHE{$dependent_file};
      unless ($state_result) {
        my @stat_result = lstat $dependent_file;
        if (@stat_result) {
          $state_result = \@stat_result;
        }
      };
      next unless $state_result;
      
      my $mode = $state_result->[2];
      my $is_dir = S_ISDIR($mode);
      my $is_file = S_ISREG($mode);

      if ($is_dir) {
        # Check if the file has an extension
        my $has_ext_re = qr/\.[^.\\\/]+$/;

        File::Find::find({
          wanted => sub {
            my $full_path = $File::Find::name;
            
            # 1. Fetch from cache or execute lstat
            my $state_result = $STAT_RESULT_CACHE{$full_path} //= do {
              my @stat_result = lstat $full_path;
              @stat_result ? \@stat_result : undef;
            };
            return unless $state_result;

            # 2. Get mode and check file types using constants
            my $mode = $state_result->[2];
            my $is_dir  = S_ISDIR($mode);
            my $is_file = S_ISREG($mode);

            # Normalize for regex
            my $normalized_path = $full_path;
            $normalized_path =~ s|\\|/|g;

            # 3. Directory handling
            if ($is_dir) {
              # Prune hidden directories
              if ($normalized_path =~ m|/\.[^/]+$|) {
                $File::Find::prune = 1;
              }
              return;
            }

            # 4. File handling
            if ($is_file) {
              # Match specs: has extension, not excluded, not in hidden dir
              if ($normalized_path =~ $has_ext_re && 
                  $normalized_path !~ $dependent_file_exclude_exts_re && 
                  $normalized_path !~ m|[\\/]\.[^\\/]+|) {
                
                push @child_dependent_files, $full_path;
              }
            }
          },
          no_chdir => 1,
          follow   => 1,
        }, $dependent_file);
      }
      elsif ($is_file) {
        push @child_dependent_files, $dependent_file;
      }
      
      my $dependent_file_sha = Digest::SHA->new(1);
      
      @child_dependent_files = sort @child_dependent_files;
      for my $child_file (@child_dependent_files) {
        my $is_under_current_dir = $self->is_under_current_dir_without_log_dir($child_file);
      
        # Path hash
        my $normalized = $NORMALIZE_PATH_CACHE{$child_file}{$log_dir} //= 
          SPVM::Builder::Util::normalize_path($child_file, $log_dir);
        $dependent_file_sha->add(Digest::SHA::sha1_hex($normalized));
        
        # Content or Mtime hash
        if ($is_under_current_dir && -T $child_file) {
          my $content = $DEPENDENT_CONTENT_CACHE{$child_file};
          unless (defined $content) {
            my $tmp_sha = Digest::SHA->new(1);
            $tmp_sha->addfile($child_file);
            $content = $tmp_sha->hexdigest;
            $DEPENDENT_CONTENT_CACHE{$child_file} = $content;
          }
          $dependent_file_sha->add($content);
        }
        else {
          # Retrieve the stat object from cache
          my $state_result = $STAT_RESULT_CACHE{$child_file} // [stat $child_file];
          # Use mtime ($st[9]) and size ($st[7]) for the hash
          $dependent_file_sha->add("mtime:$state_result->[9] size:$state_result->[7]");
        }
      }
      $dependant_file_hash = $DEPENDANT_FILE_HASH_CACHE{$dependent_file} = $dependent_file_sha->hexdigest;
    }
    $sha->add($dependant_file_hash);
  }

  return $sha->hexdigest;
}

my $RECOMPACTED = 0;
sub recompact {
  my ($self) = @_;
  
  if ($RECOMPACTED) {
    return;
  }
  
  $self->write_lock_with_flush(sub {
    $self->load_log_without_lock;
    
    my $log_fh = $self->log_fh;
    
    # Truncate the file to 0 bytes
    # This is safe because we hold the write lock.
    truncate($log_fh, 0)
      or confess("Can't truncate log file: $!");
    
    # Move the file pointer back to the beginning
    # Crucial for Windows to avoid sparse files (null bytes at the start).
    seek($log_fh, 0, SEEK_SET)
      or confess("Can't seek to the start of log file: $!");
    
    # Write header
    $self->add_log_header_without_lock;
    
    my $entries_h = $self->entries_h;
    
    # Sort by start_time (ascending)
    my @normalized_output_files = sort {
      $entries_h->{$a}{start_time} <=> $entries_h->{$b}{start_time}
    } keys %$entries_h;
    
    # Write each valid log entry
    for my $normalized_output_file (@normalized_output_files) {
      my $entory_h = $entries_h->{$normalized_output_file};
      $self->add_log_without_lock($entory_h, {no_normalize_output_file => 1});
    }
  });
  
  $RECOMPACTED = 1;
}

sub read_lock {
  my ($self, $cb) = @_;
  
  # Ensure the lock file handle is already opened
  my $lock_fh = $self->lock_fh;
  unless (defined $lock_fh) {
    confess("Log lock file handle 'lock_fh' must be defined.");
  }

  # Shared lock for concurrent reading
  flock($lock_fh, LOCK_SH)
    or confess("Can't get shared lock: $!");
  
  my $result;
  eval { $result = $cb->() };
  my $error = $@;
  
  # Unlock but keep the file handle open for reuse
  flock($lock_fh, LOCK_UN);
  
  if ($error) {
    die $error;
  }
  
  return $result;
}

sub write_lock {
  my ($self, $cb) = @_;
  
  # Ensure the lock file handle is already opened
  my $lock_fh = $self->lock_fh;
  unless (defined $lock_fh) {
    confess("Log lock file handle 'lock_fh' must be defined.");
  }
  
  # Exclusive lock for writing
  flock($lock_fh, LOCK_EX)
    or confess("Can't get exclusive lock: $!");
  
  my $result;
  eval { $result = $cb->() };
  my $error = $@;
  
  # Unlock but keep the file handle open for reuse
  flock($lock_fh, LOCK_UN);
  
  if ($error) {
    die $error;
  }
  
  return $result;
}

sub write_lock_with_flush {
  my ($self, $cb) = @_;
  
  return $self->write_lock(sub {
    my $result = $cb->();
    
    # Flush the log file handle directly
    $self->log_fh->flush;
    
    return $result;
  });
}

sub create_log {
  my ($self) = @_;
  
  mkpath $self->log_dir;
  
  $self->open_log('>>');
  $self->close_log;
}

use Cwd 'abs_path';

# Get the real physical path at startup
my $CURRENT_DIR_ABS = abs_path(Cwd::getcwd());

# Normalize to forward slashes and add trailing slash
$CURRENT_DIR_ABS =~ s|\\|/|g;
unless ($CURRENT_DIR_ABS =~ m|/$|) {
  $CURRENT_DIR_ABS .= '/';
}

sub is_under_current_dir_without_log_dir {
  my ($self, $path) = @_;
  
  # Use abs_path to resolve symlinks (especially for Mac /var -> /private/var)
  my $log_dir_abs = $self->{log_dir_abs} //= do {
    # If log_dir doesn't exist yet, abs_path might fail, 
    # so we may need a fallback or ensure it exists.
    my $ld = abs_path($self->log_dir) || File::Spec->rel2abs($self->log_dir);
    $ld =~ s|\\|/|g;
    $ld;
  };

  # Resolve the input path to its real physical path
  my $abs_path = abs_path($path);
  $abs_path =~ s|\\|/|g;
  
  # Now the comparison should work even on Mac's temp dirs
  if (index($abs_path, $CURRENT_DIR_ABS) == 0) {
    if (index($abs_path, $log_dir_abs) == 0) {
      return 0;
    }
    return 1;
  }
  
  return 0;
}

sub DESTROY {
  my ($self) = @_;
  
  # Ensure the log file handle is closed
  $self->close_log;
}

# Parallel Note
# Use open mode '>>' and '+<' for other process to open the same file.
# Open the log file in new and close the log file in DESTROY.

1;

=head1 Name

SPVM::Builder::Ninja - Incremental Build Management using Ninja Log Format

=head1 Description

L<SPVM::Builder::Ninja> manages incremental builds for the SPVM build system. It uses a build log format compatible with the Ninja build tool (C<.ninja_log>) to determine if a target file needs to be regenerated.

Unlike traditional C<make>, which relies solely on file modification times (mtime), this class provides a more robust re-generation logic by considering command-line arguments and the content hashes of dependent files.

=head1 Overview of the Build System

This class implements a high-performance and reliable build system based on the following four pillars:

=head2 1. Content-Based Re-generation (Command Hash)

To ensure build correctness, this system generates a B<SHA-1 hash (Command Hash)> by combining various factors:

=over 2

=item * The command-line string itself.

=item * The version of the compiler or tool used.

=item * The paths and B<content hashes> of all dependent files (e.g., header files).

=back

This allows the system to accurately detect when a rebuild is necessary, such as when a source file is modified, an include file is changed, or a compiler flag is updated (e.g., from C<-O2> to C<-O3>).

=head2 2. Ninja-Compatible Log Management

Each successful build entry is recorded in C<.ninja_log>, including the output file name, command hash, start/end times, and mtime. This format is compatible with Ninja v5. The class also includes a "Recompact" feature that cleans up old entries and rewrites the log to prevent it from growing indefinitely.

=head2 3. Concurrency Safety via File Locking

SPVM supports parallel builds to leverage multi-core processors. To prevent data corruption when multiple processes write to the same log file, this class implements strict B<advisory locking (LOCK_SH / LOCK_EX)> using a C<.ninja_lock> file. This ensures that concurrent build processes can operate safely and efficiently.

=head2 4. Dependency Scanning

The system recursively scans specified directories to collect dependencies such as C/C++ header files. Since the state of these files is reflected in the command hash, any change to a deep-level header file will correctly trigger a re-compilation of the dependent source files.

=cut
