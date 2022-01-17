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
sub module_dirs { shift->{module_dirs} }

sub new {
  my $class = shift;
  
  my $self = {
    module_dirs => [map { "$_/SPVM" } @INC],
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

sub get_shared_lib_file_dist {
  my ($self, $class_name, $category) = @_;

  my $module_module_file = $self->get_module_file($class_name);
  
  my $shared_lib_file = SPVM::Builder::Util::convert_module_file_to_shared_lib_file($module_module_file, $category);
  
  return $shared_lib_file;
}

sub build_shared_lib_dist {
  my ($self, $class_name, $category) = @_;

  my $compile_success = $self->compile_spvm($class_name, '(build_shared_lib_dist)', 0);
  unless ($compile_success) {
    exit(255);
  }

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => $category,
    builder => $self,
    quiet => 0,
  );
  
  my $method_names = $self->get_method_names($class_name, $category);
  $cc_native->build_shared_lib_dist($class_name);
}

sub build_and_bind_shared_lib {
  my ($self, $class_name, $category) = @_;
  
  my $cc = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => $category,
    builder => $self,
    quiet => 1,
  );
  
  my $method_names = $self->get_method_names($class_name, $category);
  
  if (@$method_names) {
    # Shared library which is already installed in distribution directory
    my $shared_lib_file = $self->get_shared_lib_file_dist($class_name, $category);

    
    # Try runtime compile if shared library is not found
    unless (-f $shared_lib_file) {
      $shared_lib_file = $cc->build_shared_lib_runtime($class_name);
    }
    $self->bind_methods($cc, $shared_lib_file, $class_name, $category);
  }
  
}

sub bind_methods {
  my ($self, $cc, $shared_lib_file, $class_name, $category) = @_;

  my $method_names = $self->get_method_names($class_name, $category);
  my $method_infos = [];
  for my $method_name (@$method_names) {
    my $method_info = {};
    $method_info->{class_name} = $class_name;
    $method_info->{method_name} = $method_name;
    push @$method_infos, $method_info;
  }
  
  # Add anon class sub names if precompile
  if ($category eq 'precompile') {
    my $anon_class_names = $self->get_anon_class_names_by_parent_class_name($class_name);
    for my $anon_class_name (@$anon_class_names) {
      my $method_info = {};
      $method_info->{class_name} = $anon_class_name;
      $method_info->{method_name} = "";
      push @$method_infos, $method_info;
    }
  }

  for my $method_info (@$method_infos) {
    my $class_name = $method_info->{class_name};
    my $method_name = $method_info->{method_name};

    my $method_abs_name = "${class_name}::$method_name";
    
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);

    my $cfunc_address;
    if ($shared_lib_file) {
      my $shared_lib_libref = DynaLoader::dl_load_file($shared_lib_file);
      
      if ($shared_lib_libref) {

        $cfunc_address = DynaLoader::dl_find_symbol($shared_lib_libref, $cfunc_name);
        unless ($cfunc_address) {
          my $dl_error = DynaLoader::dl_error();
          my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to ${class_name}->$method_name in \"$shared_lib_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
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

    $self->bind_method($class_name, $method_name, $cfunc_address, $category);
  }

}

sub get_config {
  my ($self, $class_name, $category) = @_;

  my $module_file = $self->get_module_file($class_name);
  my $src_dir = SPVM::Builder::Util::remove_class_part_from_file($module_file, $class_name);
  
  # Config file
  my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'config');
  my $config_file = "$src_dir/$config_rel_file";
  
  # Config
  my $config;
  if (-f $config_file) {
    $config = SPVM::Builder::Util::load_config($config_file);
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
my \$config = SPVM::Builder::Config->new_gnu99;

\$config;
----------------------------------------------
$@
EOS
      confess $error;
    }
    else {
      $config = SPVM::Builder::Config->new_gnu99;
    }
  }


  return $config;
}

1;

=encoding utf8

=head1 NAME

SPVM::Builder - Build SPVM program

=head1 DESCRIPTION

Build SPVM program. Compile SPVM source codes. Bind native and precompile methods. Generate Perl subrotuines correspoing to SPVM methods. After that, run SPVM program.
