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
  my $ld = $options->{ld} // 'link.exe';
  
  # --- Initialize Global Config ---
  $self->clear_system_settings;
  $self->cc($cc);
  $self->long_option_sep(':');
  
  # Linker settings
  $self->ld($ld);
  $self->static_lib_ldflag(["", ""]);
  $self->lib_prefix("");
  $self->lib_option_name("");
  $self->lib_option_suffix(".lib");
  $self->ld_output_option_name('-OUT');
  $self->ld_optimize('-OPT:REF,ICF');
  $self->lib_dir_option_name('-LIBPATH');
  $self->bcrypt_ldflags(['bcrypt.lib']);
  $self->warn_ldflags(['-nologo']);

  # --- Rules for each Config ---

  # 1. Common settings for all configs
  $self->compile_match_any({
    config_global         => $self,
    cc                    => 'cl',
    long_option_sep       => ':',
    cc_output_option_name => '-Fo',
    warn_ccflags          => ['-nologo'],
    optimize              => $self->optimize // '-O2',
  });
  
  # Clear system settings before other rules
  $self->compile_match_any(sub { $_[0]->clear_system_settings });

  # 2. Common C/C++ flags (when dialect is undefined)
  # Use '+' to preserve existing flags (equivalent to push)
  $self->compile_match({language => qr/^(c|cpp)$/, dialect => undef}, {
    '+compiler_ccflags' => ['-utf-8', '-Gy'],
    '+ld_ccflags'       => ['-MT'],
  });

  # 3. C specific rules
  $self->compile_match({language => 'c', dialect => undef}, {
    '+language_ccflags' => ['-TC'],
  });
  
  # Ensure C11 as baseline if unspecified or c99
  $self->compile_match({language => 'c', dialect => undef, std => qr/^(|c99)$/}, {
    std => 'c11',
  });

  # 4. C++ specific rules
  $self->compile_match({language => 'cpp', dialect => undef}, {
    '+language_ccflags' => ['-TP'],
    '+cpp_exception_handling_ccflags'  => ['-EHsc'],
  });

  # Ensure C++14 as baseline if specified as c++11
  $self->compile_match({language => 'cpp', dialect => undef, std => 'c++11'}, {
    std => 'c++14',
  });

  return $self;
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