package SPVM::Builder::Config::Exe::MSVC;

use parent 'SPVM::Builder::Config::Exe';

use strict;
use warnings;
use Carp ();
use File::Basename 'dirname', 'basename';
use File::Spec;
use File::Find;

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->init;
  
  return $self;
}

sub init {
  my ($self, $options) = @_;
  
  $options //= {};
  
  if (exists $options->{hint_cc}) {
    $self->{hint_cc} = $options->{hint_cc};
  }
  else {
    delete $self->{hint_cc};
  }
  
  if (exists $options->{ld}) {
    $self->{ld} = $options->{ld};
  }
  else {
    $self->{ld} = 'link.exe';
  }
  
  $self->setup_env;
  
  # --- Initialize Global Config ---
  $self->clear_system_fields;
  $self->long_option_sep(':');
  $self->thread_ldflags([]);
  $self->ld_version($self->create_cc_version);
  
  # Linker settings
  $self->static_lib_braces(["", ""]);
  $self->lib_prefix("");
  $self->lib_option_name("");
  $self->lib_option_suffix(".lib");
  $self->ld_output_option_name('-OUT');
  $self->ld_optimize('-OPT:REF,ICF');
  $self->lib_dir_option_name('-LIBPATH');
  $self->libbcrypt_ldflags(['bcrypt.lib']);
  $self->copyright_print_ldflags(['-nologo']);
  $self->debug_info_ldflags(['-DEBUG']);
  
  # --- Rules for each Config ---

  # Clear system settings before other rules
  $self->compile_rule_any(sub { $_[0]->clear_system_fields });

  # 1. Common settings for all configs
  $self->compile_rule_any({
    cc                    => 'cl',
    long_option_sep       => ':',
    cc_output_option_name => '-Fo',
    copyright_print_ccflags          => ['-nologo'],
    '+extra_ccflags' => ['-FS'],
    thread_ccflags => [],
    cc_version => $self->create_cc_version,
    optimize           => '-O2',
    ndebug_ccflags     => ['-DNDEBUG'],
  });
  
  # 2. Common C/C++ flags
  # Use '+' to preserve existing flags (equivalent to push)
  $self->compile_rule({language => qr/^(c|cpp)$/}, {
    'function_level_linking_ccflags' => ['-Gy'],
    'source_encoding_ccflags' => ['-utf-8'],
    'library_linkage_ccflags'       => ['-MT'],
    'debug_info_ccflags'            => ['-Zi'],
  });

  # 3. C specific rules
  $self->compile_rule({language => 'c'}, {
    'language_ccflags' => ['-TC'],
  });
  
  # Ensure C11 as baseline if unspecified or c99
  $self->compile_rule({language => 'c', std => qr/^(|c99)$/}, {
    std => 'c11',
  });

  # 4. C++ specific rules
  $self->compile_rule({language => 'cpp'}, {
    'language_ccflags' => ['-TP'],
    'cpp_exception_handling_ccflags'  => ['-EHsc'],
  });

  # Ensure C++14 as baseline if specified as c++11
  $self->compile_rule({language => 'cpp', std => 'c++11'}, {
    std => 'c++14',
  });
  
  # --- MSVC Build Type Rules (CMake-Compatible & Binary Safe) ---

  # Debug: Equivalent to CMake's Debug but uses -MT to avoid LNK4098.
  # Includes debug symbols and disables optimization for a smooth debugging experience.
  $self->compile_rule(
    { global => {build_type => 'Debug'} },
    {
      optimize           => '-Od',               # Disable optimization
      debug_info_ccflags => ['-Zi', '-RTC1'],    # Generate PDB and enable runtime stack checks
      ndebug_ccflags     => [],                  # Enable assertions
    }
  );

  # Release: Optimized for speed, no debug symbols.
  $self->compile_rule(
    { global => {build_type => 'Release'} },
    {
      optimize           => '-O2',               # Maximize speed
      debug_info_ccflags => [],
      ndebug_ccflags     => ['-DNDEBUG'],        # Disable assertions
    }
  );

  # RelWithDebInfo: Optimized for speed but includes debug symbols for backtracing.
  $self->compile_rule(
    { global => {build_type => 'RelWithDebInfo'} },
    {
      optimize           => '-O2',               # Maximize speed
      debug_info_ccflags => ['-Zi'],             # Generate PDB
      ndebug_ccflags     => ['-DNDEBUG'],        # Disable assertions
    }
  );

  # MinSizeRel: Optimized for binary size.
  $self->compile_rule(
    { global => {build_type => 'MinSizeRel'} },
    {
      optimize           => '-O1',               # Minimize size
      debug_info_ccflags => [],
      ndebug_ccflags     => ['-DNDEBUG'],        # Disable assertions
    }
  );
  
  return $self;
}

sub setup_env {
  my ($self) = @_;
  
  my $cl_long_path = $self->hint_cc;
  
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
  
  $self->hint_cc(basename $cl_long_path);
  
  require Win32;
  
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

sub create_cc_version {
  my ($self) = @_;
  
  my $hint_cc = $self->hint_cc;
  
  my $cc_version = `$hint_cc 2>&1` // '';
  
  $cc_version =~ s/\r?\n.*//s;
  
  return $cc_version;
}

1;

=head1 Name

SPVM::Builder::Config::Exe::MSVC - Configuration for Executable Files for MSVC

=head1 Description

L<SPVM::Builder::Config::Exe::MSVC> managaes configurations for generating executable files for MSVC.

=head2 Usage

  use SPVM::Builder::Config::Exe::MSVC;

  my $config_global = SPVM::Builder::Config::Util::load_base_config(__FILE__);
  
  $config_global = SPVM::Builder::Config::Exe::MSVC->new_with_config($config_global);
  
  $config_global->init;

  $config_global;

=head1 Super Class

L<SPVM::Builder::Config::Exe>

=head1 Class Methods

=head2 new

  my $config_global = SPVM::Builder::Config::Exe::MSVC->new(%fields);

Creates a new L<SPVM::Builder::Config::Exe::MSVC> object by calling C<new> method in the super class with I<%fields>, and calls L</"init"> method with I<%fields>.

=head1 Instance Methods

=head2 init
  
  $config_global->init(%fields);

Initialize this instance for MSVC compiler and linker.
