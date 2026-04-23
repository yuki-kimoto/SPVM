package SPVM::Builder::Ninja;

# SPVM::Builder::Ninja is used from Makefile.PL
# so this class must be wrote as pure perl. Do not contain XS functions.

use strict;
use warnings;
use Digest::SHA;
use Carp 'confess';
use File::Path 'mkpath';
use Fcntl qw(:flock :seek);
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
  source_exts
  dependent_content_hashes_h
)];

sub new {
  my $class = shift;
  
  my $self = {
    entries_h => {},
    log_file_base_name => '.ninja_log',
    entries_length => 0,
    source_exts => [qw(h hpp hh hxx h++ inc inl c cpp cc cxx c++)],
    lock_file_base_name => '.ninja_lock',
    dependent_content_hashes_h => {},
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
my %DEPENDENT_FILES_CACHE;
my %STAT_CACHE;

sub create_command_hash {
  my ($self, $options) = @_;
  
  # Command string
  my $command = $options->{command};
  unless (defined $command) {
    confess("command must be defined.");
  }
  
  # Command version
  my $command_version = $options->{command_version};
  unless (defined $command_version) {
    confess("command_version must be defined.");
  }
  
  # Dependent files or directories (Secondary inputs)
  my $dependent_files = $options->{dependent_files};
  unless (defined $dependent_files) {
    confess("dependent_files must be defined.");
  }
  
  my $extensions = $self->source_exts || [];
  my $ext_list = join '|', map { quotemeta $_ } @$extensions;
  my $valid_ext_re = qr/\.(?:$ext_list)$/i;

  # Process dependent files/directories
  my @all_dependent_files;
  for my $path (@$dependent_files) {
    next unless defined $path;

    unless (exists $DEPENDENT_FILES_CACHE{$path}) {
      # write brief comment in English
      # Scan and cache files in path if not already cached
      my @found;
      if (-d $path) {
        File::Find::find({
          wanted => sub {
            my $full_path = $File::Find::name;
            my $base_name = $full_path;
            $base_name =~ s|.*/||; 
            if (-f $full_path && $base_name =~ $valid_ext_re) {
              push @found, $full_path;
            }
          },
          no_chdir => 1,
          follow   => 1,
        }, $path);
      }
      elsif (-f $path) {
        push @found, $path;
      }
      $DEPENDENT_FILES_CACHE{$path} = \@found;
    }
    push @all_dependent_files, @{$DEPENDENT_FILES_CACHE{$path}};
  }


  # Sort and unique for dependent files
  my %seen_dependent_files_h;
  @all_dependent_files = sort grep { !$seen_dependent_files_h{$_}++ } @all_dependent_files;
  
  my $sha = Digest::SHA->new(1);

  # Add command and version hashes
  $sha->add(Digest::SHA::sha1_hex($command) . "\x0A");
  $sha->add(Digest::SHA::sha1_hex($command_version) . "\x0A");

  my $log_dir = $self->log_dir;
  
  # Add dependent files hashes (Using in-memory cache)
  # Add dependent files hashes (Using in-memory cache)
  for my $dependent_file (@all_dependent_files) {
    my $normalized_dependent_file = $NORMALIZE_PATH_CACHE{$dependent_file}{$log_dir};
    
    unless (defined $normalized_dependent_file) {
      $normalized_dependent_file = SPVM::Builder::Util::normalize_path($dependent_file, $log_dir);
      $NORMALIZE_PATH_CACHE{$dependent_file}{$log_dir} = $normalized_dependent_file;
    }
    
    $sha->add(Digest::SHA::sha1_hex($normalized_dependent_file) . "\x0A");
    
    # Check if the file is under the current working directory AND has source extensions
    my $is_current_source = is_under_cwd($dependent_file) && ($dependent_file =~ $valid_ext_re);
    
    my $file_id_info;
    if ($is_current_source) {
      # Use content hash for current source files
      $file_id_info = $self->dependent_content_hashes_h->{$dependent_file};
      unless (defined $file_id_info) {
        my $tmp_sha = Digest::SHA->new(1);
        
        $tmp_sha->addfile($dependent_file);
        $file_id_info = $tmp_sha->hexdigest;
        $self->dependent_content_hashes_h->{$dependent_file} = $file_id_info;
      }
    }
    else {
      # Use modification time and size for others (external or non-source files)
      # Using package-level %STAT_CACHE to avoid repeated I/O
      my $stat_info = $STAT_CACHE{$dependent_file};
      unless (defined $stat_info) {
        my @s = stat $dependent_file;
        $stat_info = "mtime:$s[9] size:$s[7]";
        $STAT_CACHE{$dependent_file} = $stat_info;
      }
      $file_id_info = $stat_info;
    }
    
    $sha->add($file_id_info . "\x0A");
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

# Get and cache the absolute current directory once at startup
my $CWD_ABS = File::Spec->rel2abs(Cwd::getcwd());

# Add a trailing slash to avoid partial match (e.g., /home/user/spvm vs /home/user/spvm_extra)
my $CWD_CHECK_STR = $CWD_ABS;
unless ($CWD_CHECK_STR =~ m|[\\/]$|) {
  $CWD_CHECK_STR .= '/';
}
# Normalize to forward slashes for consistent string comparison
$CWD_CHECK_STR =~ s|\\|/|g;

sub is_under_cwd {
  my ($path) = @_;
  
  # 1. Convert to absolute without hitting disk (rel2abs is mostly string op)
  # 2. Normalize slashes
  my $abs_path = File::Spec->rel2abs($path);
  $abs_path =~ s|\\|/|g;
  
  # 3. Fast string prefix match
  return index($abs_path, $CWD_CHECK_STR) == 0;
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
