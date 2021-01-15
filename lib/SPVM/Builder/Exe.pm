package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp 'confess';
use Pod::Usage 'pod2usage';
use Config;

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
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
  $self->create_module_source_csources;

  # Create boot csource
  $self->create_boot_csource($package_name);
  
}

sub create_module_source_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;

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
    
    # Build source directory
    my $build_src_dir = "$build_dir/work/src";
    mkpath $build_src_dir;
    
    my $module_source_csource_file = "$build_src_dir/$module_source_base.modsrc.c";

    mkpath dirname $module_source_csource_file;
    
    open my $module_source_csource_fh, '>', $module_source_csource_file
      or die "Can't open file $module_source_csource_file:$!";

    print $module_source_csource_fh $get_module_source_csource;
  }
}

sub create_boot_csource {
  my ($self, $package_name) = @_;
  
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

int32_t main(int32_t argc, const char *argv[]) {
  
  // Package name
  const char* package_name = "Main";
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, package_name, package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Get script directory
  const char* cur_script_name = argv[0];
  int32_t cur_script_name_length = (int32_t)strlen(argv[0]);
  char* cur_script_dir = malloc(cur_script_name_length + 1);
  memcpy(cur_script_dir, cur_script_name, cur_script_name_length);
  cur_script_dir[cur_script_name_length] = '\0';
  int32_t found_sep = 0;
  for (int32_t i = cur_script_name_length - 1; i >= 0; i--) {
    if (cur_script_dir[i] == '/' || cur_script_dir[i] == '\\') {
      cur_script_dir[i] = '\0';
      found_sep = 1;
      break;
    }
  }
  if (!found_sep) {
    cur_script_dir[0] = '.';
    cur_script_dir[1] = '\0';
  }
  
  // Add include path
  SPVM_LIST_push(compiler->module_include_dirs, cur_script_dir);
  
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
    void* cmd_arg_obj = env->new_string_len(env, argv[arg_index], strlen(argv[arg_index]));
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

sub compile_spvm_csources {
  my ($self, $package_name, $sub_names, $opt) = @_;
}

sub compile_main {
  my ($self) = @_;
}

sub link_executable {
  my ($self, $package_name, $all_libs) = @_;
}

1;
