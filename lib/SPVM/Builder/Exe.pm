package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp 'confess';
use Pod::Usage 'pod2usage';
use Config;

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use File::Find 'find';

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Scalar::Util 'weaken';

use File::Basename 'dirname', 'basename';

sub builder { shift->{builder} }

sub build_dir { shift->{build_dir} }

sub new {
  my $class = shift;
  
  my $self = {@_};

  # Package name
  my $package_name = $self->{package_name};
  unless (defined $package_name) {
    confess "Package name not specified";
  }
  
  # Excutable file name
  my $exe_name = $self->{exe_name};
  unless (defined $exe_name) {
    $exe_name = $package_name;
    $exe_name =~ s/::/__/g;
    $self->{exe_name} = $exe_name;
  }
  
  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir) {
    $self->{build_dir} = '.spvm_build';
  }
  
  # Quiet output
  unless (exists $self->{quiet}) {
    $self->{quiet} = 0;
  }
  
  # Library paths
  unless (exists $self->{library_path}) {
    $self->{library_path} = [];
  }

  # Library
  unless (exists $self->{library}) {
    $self->{library} = [];
  }

  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(build_dir => $build_dir);
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Package name
  my $package_name = $self->{package_name};
  
  # Excutable file name
  my $exe_name = $self->{exe_name};
  
  # Build directory
  my $build_dir = $self->{build_dir};
  mkpath $build_dir;
  
  # Compile SPVM
  my $file = 'internal';
  my $line = 0;
  my $compile_success = $builder->compile_spvm($package_name, $file, $line);
  unless ($compile_success) {
    exit(255);
  }
  
  # Create module source csources
  my $module_source_info_h = $self->create_module_source_csources;

  # Create boot csource
  $self->create_boot_csource($package_name, $module_source_info_h);


  # Create main csouce
  $self->create_boot_csource($package_name);

  # compile main
  $self->compile_main($package_name);
}

sub create_module_source_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  my $module_source_info_h = {};

  # Compiled package names
  my $package_names = $builder->get_package_names;
  
  for my $package_name (@$package_names) {
    # This source is UTF-8 binary
    my $module_source = $builder->get_module_source($package_name);
    
    my $module_source_c_hex = $module_source;
    
    # Escape to Hex C launguage string literal
    $module_source_c_hex =~ s/(.)/$_ = sprintf("\\x%02X", ord($1));$_/ges;
    
    # native package name
    my $native_package_name = $package_name;
    $native_package_name =~ s/::/__/g;

    my $get_module_source_header = <<"EOS";
const char* SPMODSRC__${native_package_name}__get_module_source();
EOS
    
    my $get_module_source_csource = <<"EOS";
const char* module_source = "$module_source_c_hex";
const char* SPMODSRC__${native_package_name}__get_module_source() {
  return module_source;
}
EOS

    my $module_source_base = $package_name;
    $module_source_base =~ s|::|/|g;
    
    my $build_dir = $self->build_dir;
    
    # Build header directory
    my $build_header_dir = "$build_dir/work/include";
    mkpath $build_header_dir;

    my $module_source_header_file = "$build_header_dir/$module_source_base.modsrc.h";
    
    mkpath dirname $module_source_header_file;

    open my $module_source_header_fh, '>', $module_source_header_file
      or die "Can't open file $module_source_header_file:$!";
    
    print $module_source_header_fh $get_module_source_header;
    
    $module_source_info_h->{$package_name}{header_file} = $module_source_header_file;
    
    # Build source directory
    my $build_src_dir = "$build_dir/work/src";
    mkpath $build_src_dir;
    
    my $module_source_csource_file = "$build_src_dir/$module_source_base.modsrc.c";

    mkpath dirname $module_source_csource_file;
    
    open my $module_source_csource_fh, '>', $module_source_csource_file
      or die "Can't open file $module_source_csource_file:$!";

    print $module_source_csource_fh $get_module_source_csource;

    $module_source_info_h->{$package_name}{csource_file} = $module_source_csource_file;
  }
  
  return $module_source_info_h;
}

sub create_boot_csource {
  my ($self, $package_name, $module_source_info_h) = @_;

  my $builder = $self->builder;

  # Compiled package names
  my $package_names = $builder->get_package_names;

  my $boot_csource = '';
  
  $boot_csource .= <<'EOS';

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api.h"
#include "spvm_op.h"
#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_module_source.h"

EOS
  
  $boot_csource .= "// include module source get functions\n";
  for my $package_name (sort keys %$module_source_info_h) {
    my $module_source_header_file = $module_source_info_h->{$package_name}{header_file};
    $boot_csource .= qq(#include "$module_source_header_file"\n);
  }
  
  $boot_csource .= <<'EOS';

int32_t main(int32_t argc, const char *argv[]) {
  
  // Package name
  const char* package_name = "Main";
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  compiler->is_search_module_source_symtable = 1;
  
  // Set module sources
EOS
  
  for my $package_name (sort keys %$module_source_info_h) {
    my $native_package_name = $package_name;
    $native_package_name =~ s/::/__/g;
    
    $boot_csource .= "  {\n";
    $boot_csource .= "    SPVM_MODULE_SORUE* module_source = SPMODSRC__${native_package_name}__get_module_source()\n";
    $boot_csource .= qq(    SPVM_SPVM_HASH_insert(compiler->module_source_symtable, "$package_name", strlen("$package_name"), module_source);\n);
    $boot_csource .= "  {\n";
  }
  $boot_csource .= "\n";
  
  $boot_csource .= <<'EOS';
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }

  // Create env
  SPVM_ENV* env = SPVM_API_create_env(compiler);
  
  // Call begin blocks
  SPVM_API_call_begin_blocks(env);

  // Package
  int32_t sub_id = SPVM_API_get_sub_id(env, package_name, "main", "int(string[])");
  
  if (sub_id < 0) {
    return -1;
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_muldim_array(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_elem_object(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  int32_t status;
  if (exception_flag) {
    SPVM_API_print(env, env->exception_object);
    printf("\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  SPVM_API_free_env(env);

  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  return status;
}
EOS

  my $build_dir = $self->{build_dir};

  my $boot_base = $package_name;
  $boot_base =~ s|::|/|g;

  # Build source directory
  my $build_src_dir = "$build_dir/work/src";
  mkpath $build_src_dir;
  
  my $boot_csource_file = "$build_src_dir/$boot_base.boot.c";

  mkpath dirname $boot_csource_file;
  
  open my $boot_csource_fh, '>', $boot_csource_file
    or die "Can't open file $boot_csource_file:$!";

  print $boot_csource_fh $boot_csource;
}

sub compile_main {
  my ($self, $package_name) = @_;
  
  my $build_dir = $self->{build_dir};

  my $bconf = SPVM::Builder::Config->new_c99;
  $bconf->set_optimize('-O0');
  my $config = $bconf->to_hash;
  
  # Compile source files
  my $quiet = $self->{quiet};
  $quiet = 0;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_file = "$build_dir/work/object/$package_name.boot.o";
  my $src_file = "$build_dir/work/src/$package_name.boot.c";
  
  mkdir dirname $object_file;
  
  # Compile source file
  $cbuilder->compile(
    source => $src_file,
    object_file => $object_file,
    include_dirs => $bconf->get_include_dirs,
    extra_compiler_flags => $bconf->get_extra_compiler_flags,
  );
  
  return $object_file;
}


1;
