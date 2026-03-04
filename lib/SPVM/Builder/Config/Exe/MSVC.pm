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

  # Search only cl.exe in PATH
  my $cc_exe = 'cl.exe';
  my $cc_path;
  my @path_dirs = File::Spec->path;

  for my $dir (@path_dirs) {
    my $abs_path = File::Spec->catfile($dir, $cc_exe);
    if (-f $abs_path && -x _) {
      $cc_path = $abs_path;
      last;
    }
  }

  unless (defined $cc_path) {
    Carp::confess("Can't find compiler 'cl.exe' in PATH.");
  }

  # Linker must be link.exe
  my $msvc_bin_dir = File::Basename::dirname($cc_path);
  my $link_path = File::Spec->catfile($msvc_bin_dir, 'link.exe');

  unless (-f $link_path && -x _) {
    Carp::confess("Can't find linker 'link.exe' in the same directory as '$cc_path'.");
  }

  # Convert for MSYS2
  $cc_path =~ s/\//\\/g;
  $link_path =~ s/\//\\/g;

  $self->cc($cc_path);
  $self->ld($link_path);

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
  
  # Set compiler callback
  $self->add_before_compile_cb_global(sub {
    my ($config) = @_;
    
    $self->_apply_msvc_settings_to_config($config);
  });
  
  # Apply settings to resources
  my $resources = $self->resources;
  for my $resource (@$resources) {
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
  my ($self) = @_;
  
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
  elsif ($arch eq 'x86') {
    $host_target = 'Hostx86/x86';
  }
  else {
    Carp::confess("Unsupported processor architecture: $arch");
  }
  
  # Search for cl.exe in Visual Studio installation directories
  my @search_dirs = (
    'C:/Program Files/Microsoft Visual Studio',
    'C:/Program Files (x86)/Microsoft Visual Studio',
  );
  
  my $cc_long_path;
  
  for my $base_dir (@search_dirs) {
    next unless -d $base_dir;
    
    File::Find::find({
      wanted => sub {
        return if $cc_long_path; # Already found
        return unless $_ eq 'cl.exe';
        
        my $full_path = $File::Find::name;
        # Check if path contains the correct host/target
        if (index($full_path, $host_target) != -1) {
          $cc_long_path = $full_path;
        }
      },
      no_chdir => 1,
    }, $base_dir);
    
    last if $cc_long_path;
  }
  
  unless ($cc_long_path) {
    Carp::confess("Can't find cl.exe in Microsoft Visual Studio directories for architecture: $arch");
  }
  
  # Convert to short path (handle spaces)
  my $cc_short_path = Win32::GetShortPathName($cc_long_path);
  unless ($cc_short_path) {
    Carp::confess("Failed to convert path to short format: $cc_long_path");
  }
  
  # Derive vcvarsall.bat path from cl.exe path
  # Replace: VC/Tools/MSVC/{version}/bin/Hostx64/x64
  # With:    VC/Auxiliary/Build
  my $vcvars_path = $cc_short_path;
  $vcvars_path =~ s|VC/Tools/MSVC/[^/]+/bin/[^/]+/[^/]+|VC/Auxiliary/Build|i;
  $vcvars_path =~ s/cl\.exe$/vcvarsall.bat/i;
  
  unless (-f $vcvars_path) {
    Carp::confess("Can't find vcvarsall.bat at: $vcvars_path");
  }
  
  # Determine vcvarsall.bat argument based on architecture
  my $vcvars_arg;
  if ($arch eq 'AMD64') {
    $vcvars_arg = 'x64';
  }
  elsif ($arch eq 'ARM64') {
    $vcvars_arg = 'arm64';
  }
  elsif ($arch eq 'x86') {
    $vcvars_arg = 'x86';
  }
  else {
    Carp::confess("Unsupported architecture for vcvarsall.bat: $arch");
  }
  
  # For system/backtick execution, convert path to Windows format with backslashes
  my $vcvars_path_win = $vcvars_path;
  $vcvars_path_win =~ s|/|\\|g;
  
  # Execute vcvarsall.bat and capture environment variables
  # Set MSYS2_ARG_CONV_EXCL to prevent MSYS2 path conversion in Git Bash
  local $ENV{MSYS2_ARG_CONV_EXCL} = '*';
  
  my $cmd = qq{cmd.exe /c "$vcvars_path_win" $vcvars_arg && set};
  my @output = `$cmd`;
  
  if ($? != 0) {
    Carp::confess("Failed to execute vcvarsall.bat: $vcvars_path");
  }
  
  my %msvc_env;
  for my $line (@output) {
    chomp $line;
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