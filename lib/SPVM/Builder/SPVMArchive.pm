package SPVM::Builder::SPVMArchive;

use strict;
use warnings;
use JSON::PP;
use File::Find 'find';

# Fields
sub info {
  my $self = shift;
  if (@_) {
    $self->{info} = $_[0];
    return $self;
  }
  else {
    return $self->{info};
  }
}

sub dir {
  my $self = shift;
  if (@_) {
    $self->{dir} = $_[0];
    return $self;
  }
  else {
    return $self->{dir};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {};
  
  return bless $self, $class || ref $class;
}

sub create_class_name_from_object_path {
  my ($class, $tar_file) = @_;
  
  my $class_name = $tar_file;
  $class_name =~ s|^object/||;
  $class_name =~ s/\..+$//;
  $class_name =~ s/\//::/g;
  $class_name =~ s/^SPVM:://;
  
  return $class_name;
}

# Class Methods
sub copy_spvm_archive_files {
  my ($class, $src_dir, $dest_dir, $info) = @_;
  
  my $classes_h = $info->{classes_h};
  
  # Normalize the base source directory to use forward slashes for robust matching
  my $normalized_src_dir = $src_dir;
  $normalized_src_dir =~ tr|\\|/|;
  $normalized_src_dir =~ s|/+$||; # Remove trailing slash for consistent substitution

  File::Find::find(
    {
      wanted => sub {
        my $src_path = $File::Find::name;
        
        # 1. Normalize the current found path to forward slashes for logic
        my $normalized_src_path = $src_path;
        $normalized_src_path =~ tr|\\|/|;
        
        # 2. Extract the relative path correctly by using normalized strings
        my $rel_path = $normalized_src_path;
        unless ($rel_path =~ s/^\Q$normalized_src_dir\E\///) {
          # Skip if the path normalization failed to match the base directory
          return if $rel_path eq $normalized_src_path;
        }

        # Skip if not a file
        return unless -f $src_path;

        my $should_copy = 0;

        # 3. Check for files based on specific rules for directories and extensions

        # 3-1. SPVM source files (.spvm) from SPVM directory
        if ($rel_path =~ m|^SPVM/| && $rel_path =~ /\.spvm$/) {
          my $class_name = __PACKAGE__->create_class_name_from_object_path($rel_path);
          if ($classes_h->{$class_name}) {
            $should_copy = 1;
          }
        }
        # 3-2. Object files (.o) from object directory or SPVM directory
        elsif (($rel_path =~ m|^object/| || $rel_path =~ m|^SPVM/|) && $rel_path =~ /\.o$/) {
          my $class_name = __PACKAGE__->create_class_name_from_object_path($rel_path);
          if ($classes_h->{$class_name}) {
            $should_copy = 1;
          }
        }
        # 3-3. Library files (.a, .lib) from lib directory
        elsif ($rel_path =~ m|^lib/| && $rel_path =~ /\.(a|lib)$/) {
          $should_copy = 1;
        }
        # 3-4. Header files from include directory (excluding hidden files)
        elsif ($rel_path =~ m|^include/|) {
          my $basename = File::Basename::basename($rel_path);
          unless ($basename =~ /^\./) {
            $should_copy = 1;
          }
        }

        return unless $should_copy;
        
        # 4. Build the destination path by joining the base and the relative part
        # We use File::Spec for cross-platform safety
        my $dest_path = File::Spec->catfile($dest_dir, split('/', $rel_path));
        
        # 5. Ensure the destination directory exists (File::Basename is safe with catfile result)
        my $dest_parent = File::Basename::dirname($dest_path);
        unless (-d $dest_parent) {
          File::Path::mkpath($dest_parent) or Carp::confess "Cannot create directory '$dest_parent': $!";
        }
        
        # 6. Copy and preserve mtime
        File::Copy::copy($src_path, $dest_path) or Carp::confess "Copy failed from '$src_path' to '$dest_path': $!";
        my $mtime = (stat $src_path)[9];
        utime $mtime, $mtime, $dest_path;
      },
      no_chdir => 1,
    },
    $src_dir
  );
}

sub merge_info {
  my ($class, $info1, $info2) = @_;
  
  my $merged_info = {};
  $merged_info->{app_name} = $info2->{app_name};
  if (defined $info2->{mode}) {
    $merged_info->{mode} = $info2->{mode};
  }
  if (defined $info2->{version}) {
    $merged_info->{version} = $info2->{version};
  }
  
  $merged_info->{classes_h} = {};
  
  if ($info1) {
    for my $class_name (keys %{$info1->{classes_h}}) {
      next if $class_name =~ /^eval::anon_class::\d+$/a;
      $merged_info->{classes_h}{$class_name} = $info1->{classes_h}{$class_name};
    }
  }
  
  if ($info2) {
    for my $class_name (keys %{$info2->{classes_h}}) {
      next if $class_name =~ /^eval::anon_class::\d+$/a;
      $merged_info->{classes_h}{$class_name} = $info2->{classes_h}{$class_name};
    }
  }
  
  return $merged_info;
}

# Instance Methods
sub load {
  my ($self, $spvm_archive) = @_;

  my $spvm_archive_dir;

  # 1. Normalize input to a directory (Extract if it is a tar.gz)
  if (-f $spvm_archive) {
    unless ($spvm_archive =~ /\.tar\.gz$/) {
      Carp::confess("SPVM archive file '$spvm_archive' must have '.tar.gz' extension");
    }
    
    # Use a temporary directory for extraction
    my $spvm_archive_dir_obj = File::Temp->newdir(TEMPLATE => 'tmp_spvm_archive_XXXXXXX');
    $spvm_archive_dir = $spvm_archive_dir_obj->dirname;
    
    my $tar = Archive::Tar->new;
    $tar->read($spvm_archive) or die $tar->error;
    $tar->extract_all($spvm_archive_dir) or die "Could not extract $spvm_archive to $spvm_archive_dir";
  }
  elsif (-d $spvm_archive) {
    $spvm_archive_dir = $spvm_archive;
  }
  else {
    Carp::confess("SPVM archive '$spvm_archive' not found");
  }

  # 2. Read and decode JSON metadata
  my $json_file = "$spvm_archive_dir/spvm-archive.json";
  unless (-f $json_file) {
    Carp::confess("SPVM archive '$spvm_archive' must contain spvm-archive.json");
  }
  my $spvm_archive_json = SPVM::Builder::Util::slurp_binary($json_file);
  
  my $info = JSON::PP->new->decode($spvm_archive_json);
  
  # Set the field in $self
  $self->{info} = $info;

  # 3. Prepare the final temporary directory for the compiler
  my $dir_obj = File::Temp->newdir(TEMPLATE => 'tmp_spvm_archive_extract_XXXXXXX');
  $self->{dir_obj} = $dir_obj;
  my $dir = $dir_obj->dirname;
  $self->{dir} = $dir;

  # 4. Copy and filter files
  File::Copy::copy($json_file, "$dir/spvm-archive.json");
  
  $self->copy_spvm_archive_files($spvm_archive_dir, $dir, $info);
  
  $self->{dir} = $dir;
}

sub exists {
  my ($self, $class_name) = @_;
  
  my $exists;
  my $info = $self->{info};
  if ($info) {
    
    my $classes_h = $info->{classes_h};
    
    if ($classes_h->{$class_name}) {
      $exists = 1;
    }
  }
  
  return $exists;
}

sub find_object_files {
  my ($self) = @_;
  
  my $dir = $self->{dir};
  
  my @object_files;
  
  find(
    {
      wanted => sub {
        my $path = $File::Find::name;
        
        if (-f $path) {
          if ($path =~ /\.o$/) {
            push @object_files, $path;
          }
        }
      },
      no_chdir => 1,
    },
    $dir
  );
  
  return \@object_files;
}

1;
