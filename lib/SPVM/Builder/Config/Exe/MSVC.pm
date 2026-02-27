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
    
    # Enable function-level linking
    push @{$config->compiler_ccflags}, '-Gy';
    
    # Static runtime
    push @{$config->ld_ccflags}, '-MT';

    if ($lang eq 'c') {
      # Force C compiler
      push @{$config->language_ccflags}, '-TC';
    }
    elsif ($lang eq 'cpp') {
      # Force C++ compiler and enable exceptions
      push @{$config->language_ccflags}, '-TP';
      push @{$config->runtime_ccflags}, '-EHsc';
    }
  }
}

1;