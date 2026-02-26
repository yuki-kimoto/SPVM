package SPVM::Builder::Config::Exe::MSVC;

use strict;
use warnings;
use Carp ();
use File::Basename 'dirname';
use File::Spec;

# Inherit from SPVM::Builder::Config::Exe
use base 'SPVM::Builder::Config::Exe';

sub apply {
  my ($self, $options) = @_;

  # MSVC compiler must be 'cl.exe'
  my $cc_exe = 'cl.exe';

  # Search only cl.exe in PATH
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

  # Linker must be 'link.exe' in the same directory as cl.exe
  my $msvc_bin_dir = File::Basename::dirname($cc_path);
  my $link_path = File::Spec->catfile($msvc_bin_dir, 'link.exe');

  unless (-f $link_path && -x _) {
    Carp::confess("Can't find linker 'link.exe' in the same directory as '$cc_path'.");
  }

  # MSYS2 safety: convert to backslashes
  $cc_path =~ s/\//\\/g;
  $link_path =~ s/\//\\/g;

  $self->cc($cc_path);
  $self->ld($link_path);

  $self->long_option_sep(':');
  $self->lib_dir_option_name('-libpath:');

  $self->clear_system_settings;

  # Optimization flags
  $self->optimize('-O2');
  $self->ld_optimize('-OPT:REF');

  # --- Language specific flags via callback (Static Linking) ---
  $self->add_before_compile_cb_global(sub {
    my ($config, $compile_info) = @_;
    
    my $lang = $config->language // '';
    my $dialect = $config->dialect;
    
    # Check if dialect is undefined to avoid overriding specific configurations
    if (!defined $dialect) {
      if ($lang eq 'c') {
        # Static runtime for C
        $config->add_ccflags('-MT');
      }
      elsif ($lang eq 'cpp') {
        # Static runtime and Exception Handling for C++
        $config->add_ccflags('-EHsc', '-MT');
      }
    }
  });

  return $self;
}

1;