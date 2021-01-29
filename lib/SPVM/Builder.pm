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

sub build_dll_native_dist {
  my ($self, $package_name) = @_;
  
  $self->compile_spvm($package_name, '(build_dll_native_dist)', 0);

  my $sub_names = $self->get_native_sub_names($package_name);

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'native',
    builder => $self,
    quiet => 0,
  );
  
  $cc_native->build_dll_native_dist($package_name, $sub_names);
}

sub build_dll_precompile_dist {
  my ($self, $package_name) = @_;
  
  my $compile_success = $self->compile_spvm($package_name, '(build_dll_precompile_dist)', 0);
  unless ($compile_success) {
    die "Compile error";
  }
  
  my $sub_names = $self->get_precompile_sub_names($package_name);

  my $cc_precompile = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => 'precompile',
    builder => $self,
    quiet => 0,
  );
  
  $cc_precompile->build_dll_precompile_dist($package_name, $sub_names);
}

sub build_if_needed_and_bind_shared_lib {
  my ($self, $package_name, $category) = @_;
  
  my $cc = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    category => $category,
    builder => $self,
    quiet => 1,
  );
  
  my $sub_names;
  if ($category eq 'native') {
    $sub_names = $cc->builder->get_native_sub_names($package_name)
  }
  elsif ($category eq 'precompile') {
    $sub_names = $cc->builder->get_precompile_sub_names($package_name)
  }
  
  if (@$sub_names) {
    # Shared library is already installed in distribution directory
    my $dll_file = $cc->get_dll_file_dist($package_name);
    
    # Try runtime compile if shared objectrary is not found
    unless (-f $dll_file) {
      if ($category eq 'native') {
        $cc->build_dll_native_runtime($package_name, $sub_names);
      }
      elsif ($category eq 'precompile') {
        $cc->build_dll_precompile_runtime($package_name, $sub_names);
      }
      $dll_file = $cc->get_dll_file_runtime($package_name);
    }
    $self->bind_subs($cc, $dll_file, $package_name, $sub_names);
  }
}

sub bind_subs {
  my ($self, $cc, $dll_file, $package_name, $sub_names) = @_;
  
  # m library is maybe not dynamic link library
  my %must_not_load_libs = map { $_ => 1 } ('m');
  
  # Load pre-required dynamic library
  my $category = $cc->category;
  my $bconf = $cc->get_config_runtime($package_name, $category);
  my $lib_dirs = $bconf->get_lib_dirs;
  {
    local @DynaLoader::dl_library_path = (@$lib_dirs, @DynaLoader::dl_library_path);
    my $libs = $bconf->get_libs;
    for my $lib (@$libs) {
      unless ($must_not_load_libs{$lib}) {
        my ($lib_file) = DynaLoader::dl_findfile("-l$lib");
        my $dll_libref = DynaLoader::dl_load_file($lib_file);
        unless ($dll_libref) {
          my $dl_error = DynaLoader::dl_error();
          confess "Can't load dll file \"$dll_file\": $dl_error";
        }
      }
    }
  }
  
  for my $sub_name (@$sub_names) {
    my $sub_abs_name = "${package_name}::$sub_name";

    my $cfunc_name = $cc->create_cfunc_name($package_name, $sub_name);
    my $cfunc_address;
    if ($dll_file) {
      my $dll_libref = DynaLoader::dl_load_file($dll_file);
      if ($dll_libref) {
        $cfunc_address = DynaLoader::dl_find_symbol($dll_libref, $cfunc_name);
        unless ($cfunc_address) {
          my $dl_error = DynaLoader::dl_error();
          my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to $sub_abs_name in \"$dll_file\"

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
        confess "Can't load dll file \"$dll_file\": $dl_error";
      }
    }
    else {
      confess "DLL file is not specified";
    }
    
    if ($category eq 'native') {
      $cc->bind_sub_native($package_name, $sub_name, $cfunc_address);
    }
    elsif ($category eq 'precompile') {
      $cc->bind_sub_precompile($package_name, $sub_name, $cfunc_address);
    }
  }
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Builder - Compile SPVM program, bind native and precompile subroutines, generate Perl subrotuines correspoing to SPVM subroutines.
