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
    
    # Strictly check for file existence and executable bit
    if (-f $abs_path && -x _) {
      $cc_path = $abs_path;
      last;
    }
  }

  unless (defined $cc_path) {
    Carp::confess("Can't find compiler 'cl.exe' in PATH.");
  }

  # Linker must be 'link.exe' in the same directory
  my $msvc_bin_dir = File::Basename::dirname($cc_path);
  my $link_path = File::Spec->catfile($msvc_bin_dir, 'link.exe');

  unless (-f $link_path && -x _) {
    Carp::confess("Can't find linker 'link.exe' in the same directory as '$cc_path'.");
  }

  # Avoid MSYS2 path conversion issues by forcing backslashes
  $cc_path =~ s/\//\\/g;
  $link_path =~ s/\//\\/g;

  # Set paths
  $self->cc($cc_path);
  $self->ld($link_path);

  # --- Optimization: Remove redundant options found in ExtUtils::CBuilder ---
  
  # CBuilder handles '-nologo' and option prefixes (-I, -out:, -libpath:),
  # and also handles '-c' and output filenames.
  
  $self->long_option_sep(':');
  $self->lib_dir_option_name('-libpath:'); # Use '-' instead of '/' for MSYS2

  # Clear existing settings to avoid pollution
  $self->clear_system_settings;

  # Global compiler flags:
  # CBuilder already adds '-nologo', so we only add necessary runtime/exception flags.
  # Use '-' prefix for all to satisfy MSYS2.
  $self->add_ccflag_global('-EHsc', '-MD');

  # Optimization flags
  $self->optimize('-O2');
  $self->ld_optimize('-OPT:REF');

  return $self;
}

1;