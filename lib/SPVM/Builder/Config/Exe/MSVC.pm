package SPVM::Builder::Config::Exe::MSVC;

use strict;
use warnings;
use Carp ();
use File::Basename 'dirname';
use File::Spec;
use File::Find;
use Win32;

# Inherit from SPVM::Builder::Config::Exe
use base 'SPVM::Builder::Config::Exe';

sub apply {
  my ($self, $options) = @_;
  
  $options //= {};
  
  $self->setup_env($options);
  
  my $cc = $options->{cc} // 'cl';
  my $ld = $options->{ld} // 'link';
  
  $self->cc($cc);
  $self->ld($ld);
  
  $self->long_option_sep(':');
  $self->lib_dir_option_name('-libpath');
  
  # Clear and set optimization
  $self->clear_system_settings;
  $self->optimize('-O2');
  
  # Optimization for dead code elimination and identical code folding
  $self->ld_optimize('-OPT:REF,ICF');
  
  $self->static_lib_ldflag(["", ""]);
  
  $self->lib_prefix("");
  
  $self->lib_option_name("");
  
  $self->lib_option_suffix(".lib");
  
  $self->cc_output_option_name('-Fo');
  
  $self->ld_output_option_name('-out');
  
  # Set compiler callback
  $self->add_before_compile_cb_global(sub {
    my ($config) = @_;
    
    $self->_apply_msvc_settings_to_config($config);
  });
  
  # Apply settings to resources
  my $resource_names = $self->get_resource_names;
  for my $resource_name (@$resource_names) {
    my $resource = $self->get_resource($resource_name);
    my $resource_config = $resource->config;
    $self->_apply_msvc_settings_to_config($resource_config);
  }
  
  return $self;
}

sub _apply_msvc_settings_to_config {
  my ($self, $config) = @_;
  
  my $lang = $config->language // '';
  my $dialect = $config->dialect;
  
  if (($lang eq 'c' || $lang eq 'cpp') && !defined $dialect) {
    $config->clear_system_settings;
    
    # Common flags
    push @{$config->compiler_ccflags}, '-Gy';
    push @{$config->ld_ccflags}, '-MT';

    my $std = $config->std // '';
    
    if ($lang eq 'c') {
      # C compiler
      push @{$config->language_ccflags}, '-TC';

      # Ensure C11 as baseline if unspecified or c99
      if (!length $std || (length $std && $std eq 'c99')) {
        $config->std('c11');
      }
    }
    elsif ($lang eq 'cpp') {
      # C++ compiler
      push @{$config->language_ccflags}, '-TP';
      push @{$config->runtime_ccflags}, '-EHsc';

      # Ensure C++14 as baseline if unspecified or c++11
      if (length $std && $std eq 'c++11') {
        $config->std('c++14');
      }
    }
  }
}

sub setup_env {
  my ($self, $options) = @_;
  
  $options //= {};
  
  my $cl_long_path = $options->{cl};
  
  unless (defined $cl_long_path) {
    # Determine architecture (Windows only)
    my $arch = $ENV{PROCESSOR_ARCHITECTURE} || '';
    
    unless ($arch) {
      Carp::confess("Can't determine processor architecture. PROCESSOR_ARCHITECTURE environment variable not set.");
    }
    
    # Map Windows architecture to MSVC host/target path
    my $host_target;
    if ($arch eq 'AMD64') {
      $host_target = 'Hostx64/x64';
    }
    elsif ($arch eq 'ARM64') {
      $host_target = 'Hostarm64/arm64';
    }
    else {
      Carp::confess("Unsupported processor architecture: $arch");
    }
    
    # Search for cl.exe in Visual Studio installation directories
    my @search_dirs = (
      'C:/Program Files/Microsoft Visual Studio',
      'C:/Program Files (x86)/Microsoft Visual Studio',
    );
    
    for my $base_dir (@search_dirs) {
      next unless -d $base_dir;
      
      File::Find::find({
        wanted => sub {
          return if $cl_long_path; # Already found
          
          my $full_path = $File::Find::name;
          # Check if path contains the correct host/target
          if ($full_path =~ m#\Q$host_target\E/cl.exe$#i) {
            $cl_long_path = $full_path;
          }
        },
        no_chdir => 1,
      }, $base_dir);
      
      last if $cl_long_path;
    }
    
    unless (defined $cl_long_path) {
      Carp::confess("Can't find cl.exe in Microsoft Visual Studio directories for architecture: $arch");
    }
  }
  
  unless (-f $cl_long_path && -x $cl_long_path) {
    Carp::confess("'$cl_long_path' is not an executable file.");
  }
  
  # Convert to short path (handle spaces)
  my $cl_short_path = Win32::GetShortPathName($cl_long_path);
  unless ($cl_short_path) {
    Carp::confess("Failed to convert path to short format: $cl_long_path");
  }
  
  # Derive vcvarsall.bat path from cl.exe path
  # Replace: VC/Tools/MSVC/{version}/bin/Hostx64/x64
  # With:    VC/Auxiliary/Build
  my $vcvarsall_path = $cl_short_path;
  $vcvarsall_path =~ s|VC/Tools/MSVC/[^/]+/bin/[^/]+/[^/]+|VC/Auxiliary/Build|i;
  $vcvarsall_path =~ s/cl\.exe$/vcvarsall.bat/i;
  
  unless (-f $vcvarsall_path) {
    Carp::confess("Can't find vcvarsall.bat at: $vcvarsall_path");
  }
  
  # Parse Host and Target from path
  unless ($cl_short_path =~ m#bin/Host(x64|x86|arm64|arm)/(x64|x86|arm64|arm)/cl\.exe#i) {
    Carp::confess("Failed to parse architecture from cl.exe path: $cl_short_path");
  }
  my $host   = lc $1;
  my $target = lc $2;

  # Determine vcvarsall.bat argument
  my $vcvarsall_arg = ($host eq $target) ? $target : "${host}_${target}";
  
  # For system/backtick execution, convert path to Windows format with backslashes
  my $vcvarsall_path_win = $vcvarsall_path;
  $vcvarsall_path_win =~ s|/|\\|g;
  
  # Execute vcvarsall.bat and capture environment variables
  # Set MSYS2_ARG_CONV_EXCL to prevent MSYS2 path conversion in Git Bash
  local $ENV{MSYS2_ARG_CONV_EXCL} = '*';
  
  my $cmd = qq{cmd.exe /c "$vcvarsall_path_win" $vcvarsall_arg && set};
  my $vcvarsall_output = `$cmd`;
  my @vcvarsall_lines = split /\x0D?\x0A/, $vcvarsall_output;
  
  if ($? != 0) {
    Carp::confess("Failed to execute vcvarsall.bat: $vcvarsall_path");
  }
  
  # Remove all environment variables that match INCLUDE, LIB, or PATH case-insensitively
  for my $name (keys %ENV) {
    if ($name =~ /^(?:INCLUDE|LIB|PATH)$/i) {
        delete $ENV{$name};
    }
  }
  
  my %msvc_env;
  for my $line (@vcvarsall_lines) {
    $line =~ s/[\x0D\x0A]//g;
    
    if ($line =~ /^(INCLUDE|LIB|PATH)=(.*)$/) {
      my ($name, $value) = ($1, $2);
      $ENV{$name} = $value;
      unless (length $ENV{$name}) {
        Carp::confess("Failed to capture $name environment variable from vcvarsall.bat");
      }
    }
  }
}

1;