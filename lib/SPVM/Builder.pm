package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';

use SPVM::Builder::CC;

# This SPVM load is needed for SPVM::Builder XS method binding to Perl
# because SPVM::Builder XS method is loaded when SPVM is loaded
use SPVM();

# Accessors
sub build_dir { shift->{build_dir} }

sub new {
  my $class = shift;
  
  my $self = {
    include_dirs => \@INC,
    @_
  };
  
  bless $self, ref $class || $class;
  
  $self->create_compiler;
  
  return $self;
}

sub create_build_src_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_src_path = "$build_dir/work/src";
  if (defined $rel_file) {
    $build_src_path .= "/$rel_file";
  }
  
  return $build_src_path;
}

sub create_build_include_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_include_path = "$build_dir/work/include";
  if (defined $rel_file) {
    $build_include_path .= "/$rel_file";
  }
  
  return $build_include_path;
}

sub create_build_object_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_object_path = "$build_dir/work/object";
  if (defined $rel_file) {
    $build_object_path .= "/$rel_file";
  }
  
  return $build_object_path;
}

sub create_build_lib_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_lib_path = "$build_dir/work/lib";
  if (defined $rel_file) {
    $build_lib_path .= "/$rel_file";
  }
  
  return $build_lib_path;
}

sub get_shared_lib_file_runtime {
  my ($self, $package_name, $category) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $shared_lib_rel_file = SPVM::Builder::Util::convert_package_name_to_shared_lib_rel_file($package_name, $category);
  my $shared_lib_file = $self->create_build_lib_path($shared_lib_rel_file);
  
  return $shared_lib_file;
}

sub get_shared_lib_file_dist {
  my ($self, $package_name, $category) = @_;
  
  my @package_name_parts = split(/::/, $package_name);
  my $module_module_file = $self->get_module_file($package_name);
  
  my $shared_lib_file = SPVM::Builder::Util::convert_module_file_to_shared_lib_file($module_module_file, $category);
  
  return $shared_lib_file;
}

sub get_config_file {
  my ($self, $package_name) = @_;
  
  my $module_file = $self->get_module_file($package_name);
  
  my $config_file;
  if (defined $module_file) {
    $config_file = $module_file;
    $config_file =~ s/\.spvm$/.config/;
  }
  
  return $config_file;
}

sub build_shared_lib_dist {
  my ($self, $package_name, $category) = @_;
  
  $self->compile_spvm($package_name, '(build_shared_lib_${category}_dist)', 0);

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => $category,
    builder => $self,
    quiet => 0,
  );
  
  my $sub_names = $self->get_sub_names($package_name, $category);
  $cc_native->build_shared_lib_dist($package_name, $sub_names);
}

sub build_if_needed_and_bind_shared_lib {
  my ($self, $package_name, $category) = @_;
  
  my $cc = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => $category,
    builder => $self,
    quiet => 1,
  );
  
  my $sub_names = $self->get_sub_names($package_name, $category);
  
  if (@$sub_names) {
    # Shared library which is already installed in distribution directory
    my $shared_lib_file = $self->get_shared_lib_file_dist($package_name, $category);
    
    # Try runtime compile if shared objectrary is not found
    unless (-f $shared_lib_file) {
      $shared_lib_file = $cc->build_shared_lib_runtime($package_name, $sub_names);
    }
    $self->bind_subs($cc, $shared_lib_file, $package_name, $sub_names, $category);
  }
}

sub bind_subs {
  my ($self, $cc, $shared_lib_file, $package_name, $sub_names, $category) = @_;
  
  # m library is maybe not dynamic link library
  my %must_not_load_libs = map { $_ => 1 } ('m');
  
  # Load pre-required dynamic library
  my $bconf = $self->get_config_runtime($package_name, $category);
  my $lib_dirs = $bconf->get_lib_dirs;
  {
    local @DynaLoader::dl_library_path = (@$lib_dirs, @DynaLoader::dl_library_path);
    my $libs = $bconf->get_libs;
    for my $lib (@$libs) {
      unless ($must_not_load_libs{$lib}) {
        my ($lib_file) = DynaLoader::dl_findfile("-l$lib");
        my $shared_lib_libref = DynaLoader::dl_load_file($lib_file);
        unless ($shared_lib_libref) {
          my $dl_error = DynaLoader::dl_error();
          confess "Can't load shared_lib file \"$shared_lib_file\": $dl_error";
        }
      }
    }
  }
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($package_name, $sub_name, $category);
    my $cfunc_address;
    if ($shared_lib_file) {
      my $shared_lib_libref = DynaLoader::dl_load_file($shared_lib_file);
      if ($shared_lib_libref) {
        $cfunc_address = DynaLoader::dl_find_symbol($shared_lib_libref, $cfunc_name);
        unless ($cfunc_address) {
          my $dl_error = DynaLoader::dl_error();
          my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to $sub_abs_name in \"$shared_lib_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return SPVM_SUCCESS;
}
--------------------------------------------------

$dl_error
EOS
          confess $error;
        }
      }
      else {
        my $dl_error = DynaLoader::dl_error();
        confess "Can't load shared_lib file \"$shared_lib_file\": $dl_error";
      }
    }
    else {
      confess "DLL file is not specified";
    }
    
    if ($category eq 'native') {
      $self->bind_sub_native($package_name, $sub_name, $cfunc_address);
    }
    elsif ($category eq 'precompile') {
      $self->bind_sub_precompile($package_name, $sub_name, $cfunc_address);
    }
  }
}

sub get_config_runtime {
  my ($self, $package_name, $category) = @_;
  
  my $module_file = $self->get_module_file($package_name);
  my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($module_file, $package_name);

  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file($package_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $bconf;
  if (-f $config_file) {
    $bconf = SPVM::Builder::Util::load_config($config_file);
  }
  else {
    if ($category eq 'native') {
      my $error = <<"EOS";
Can't find $config_file.

Config file must contains at least the following code
----------------------------------------------
use strict;
use warnings;

use SPVM::Builder::Config;
my \$bconf = SPVM::Builder::Config->new_c99;

\$bconf;
----------------------------------------------
$@
EOS
      confess $error;
    }
    else {
      $bconf = SPVM::Builder::Config->new_c99;
    }
  }
  
  return $bconf;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Builder - Compile SPVM program, bind native and precompile subroutines, generate Perl subrotuines correspoing to SPVM subroutines.
