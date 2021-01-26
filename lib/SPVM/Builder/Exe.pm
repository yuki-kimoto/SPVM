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
use File::Spec;
use File::Find 'find';

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Scalar::Util 'weaken';

use File::Basename 'dirname', 'basename';

# SPVM runtime source files
my @SPVM_RUNTIME_SRC_BASE_NAMES = qw(
  spvm_allow.c
  spvm_api.c
  spvm_array_field_access.c
  spvm_basic_type.c
  spvm_block.c
  spvm_call_sub.c
  spvm_case_info.c
  spvm_compiler_allocator.c
  spvm_compiler.c
  spvm_constant.c
  spvm_csource_builder_precompile.c
  spvm_descriptor.c
  spvm_dumper.c
  spvm_enumeration.c
  spvm_enumeration_value.c
  spvm_field_access.c
  spvm_field.c
  spvm_hash.c
  spvm_hash_func.c
  spvm_list.c
  spvm_my.c
  spvm_op.c
  spvm_op_checker.c
  spvm_opcode_array.c
  spvm_opcode_builder.c
  spvm_opcode.c
  spvm_package.c
  spvm_package_var_access.c
  spvm_package_var.c
  spvm_string_buffer.c
  spvm_sub.c
  spvm_switch_info.c
  spvm_toke.c
  spvm_type.c
  spvm_use.c
  spvm_util_allocator.c
  spvm_var.c
  spvm_yacc.c
  spvm_yacc_util.c
);

sub builder { shift->{builder} }

sub new {
  my $class = shift;
  
  my $self = {@_};

  # Target package name
  my $target_package_name = $self->{target_package_name};
  unless (defined $target_package_name) {
    confess "Package name not specified";
  }
  
  # Excutable file name
  my $output_name = $self->{output_name};
  unless (defined $output_name) {
    $output_name = $target_package_name;
    $output_name =~ s/::/__/g;
    $self->{output_name} = $output_name;
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

  # Build directory
  my $build_dir = delete $self->{build_dir};
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(build_dir => $build_dir);
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Target package name
  my $target_package_name = $self->{target_package_name};
  
  # Excutable file name
  my $output_name = $self->{output_name};
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;
  
  # Compile SPVM
  my $file = 'internal';
  my $line = 0;
  my $compile_success = $builder->compile_spvm($target_package_name, $file, $line);
  unless ($compile_success) {
    exit(255);
  }

  # Build precompile packages
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => 0,
  );

  # Build precompile package
  my $package_names = $builder->get_package_names;
  for my $precompile_package_name (@$package_names) {
    
    my $precompile_sub_names = $builder->get_precompile_sub_names($precompile_package_name);
    if (@$precompile_sub_names) {
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      $builder_c_precompile->create_source_precompile(
        $precompile_package_name,
        [],
        {
          src_dir => $src_dir,
        }
      );
      
      my $object_dir = $self->builder->create_build_object_path;
      mkpath $object_dir;
      
      $builder_c_precompile->compile(
        $precompile_package_name,
        {
          src_dir => $src_dir,
          object_dir => $object_dir,
        }
      );
    }
  }

  # Create SPMV module C sources
  $self->create_spvm_module_csources;

  # Compile SPVM compiler and runtime C sources
  $self->compile_spvm_module_csources;

  # Compile SPVM compiler and runtime C sources
  $self->compile_spvm_compiler_and_runtime_csources;

  # Create bootstrap C source
  $self->create_bootstrap_csource($target_package_name);

  # Compile bootstrap C source
  $self->compile_bootstrap_csource($target_package_name);

  # Link and generate executable file
  $self->link($target_package_name);
}

sub create_spvm_module_csources {
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
static const char* module_source = "$module_source_c_hex";
const char* SPMODSRC__${native_package_name}__get_module_source() {
  return module_source;
}
EOS

    my $module_source_base = $package_name;
    $module_source_base =~ s|::|/|g;
    
    my $build_dir = $self->builder->build_dir;
    
    # Build header directory
    my $build_header_dir = $self->builder->create_build_include_path;
    mkpath $build_header_dir;

    my $module_source_header_file = "$build_header_dir/$module_source_base.modsrc.h";
    
    mkpath dirname $module_source_header_file;

    open my $module_source_header_fh, '>', $module_source_header_file
      or die "Can't open file $module_source_header_file:$!";
    
    print $module_source_header_fh $get_module_source_header;
    
    # Build source directory
    my $build_src_dir = $self->builder->create_build_src_path;
    mkpath $build_src_dir;
    
    my $module_source_csource_file = "$build_src_dir/$module_source_base.modsrc.c";

    mkpath dirname $module_source_csource_file;
    
    open my $module_source_csource_fh, '>', $module_source_csource_file
      or die "Can't open file $module_source_csource_file:$!";

    print $module_source_csource_fh $get_module_source_csource;
  }
}

sub compile_spvm_module_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  # Compiled package names
  my $package_names = $builder->get_package_names;

  my $bconf = SPVM::Builder::Config->new_c99;
  my $config = $bconf->to_hash;
  my $quiet = 0;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  
  for my $package_name (@$package_names) {
    
    # Build source directory
    my $build_src_dir = $self->builder->create_build_src_path;
    mkpath $build_src_dir;
    
    my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
    my $module_source_csource_file = "$build_src_dir/$package_name_rel_file.modsrc.c";
    mkpath dirname $module_source_csource_file;

    my $build_object_dir = $self->builder->create_build_object_path;
    mkpath $build_object_dir;
    my $module_source_object_file = "$build_object_dir/$package_name_rel_file.modsrc.o";
    mkpath dirname $module_source_object_file;
    
    # Compile source file
    $cbuilder->compile(
      source => $module_source_csource_file,
      object_file => $module_source_object_file,
      include_dirs => $bconf->get_include_dirs,
      extra_compiler_flags => $bconf->get_extra_compiler_flags,
    );
  }
}

sub create_bootstrap_csource {
  my ($self, $target_package_name) = @_;

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

EOS
  
  $boot_csource .= "// include module source get functions\n";
  for my $package_name (@$package_names) {
    my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
    my $module_source_header_file = $self->builder->create_build_include_path("$package_name_rel_file.modsrc.h");
    my $module_source_header_file_abs = File::Spec->rel2abs($module_source_header_file);
    $boot_csource .= qq(#include "$module_source_header_file_abs"\n);
  }
  
  $boot_csource .= <<'EOS';

int32_t main(int32_t argc, const char *argv[]) {
EOS

  $boot_csource .= <<"EOS";
  // Package name
  const char* package_name = "$target_package_name";
EOS

  $boot_csource .= <<'EOS';
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  compiler->no_directry_module_search = 1;

  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, package_name, package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Set module sources
EOS
  
  for my $package_name (@$package_names) {
    my $native_package_name = $package_name;
    $native_package_name =~ s/::/__/g;
    
    $boot_csource .= "  {\n";
    $boot_csource .= "    const char* module_source = SPMODSRC__${native_package_name}__get_module_source();\n";
    $boot_csource .= qq(    SPVM_HASH_insert(compiler->module_source_symtable, "$package_name", strlen("$package_name"), (void*)module_source);\n);
    $boot_csource .= "  }\n";
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

  my $build_dir = $self->builder->build_dir;

  my $boot_base = $target_package_name;
  $boot_base =~ s|::|/|g;

  # Build source directory
  my $build_src_dir = $self->builder->create_build_src_path;
  mkpath $build_src_dir;
  
  my $boot_csource_file = "$build_src_dir/$boot_base.boot.c";

  mkpath dirname $boot_csource_file;
  
  open my $boot_csource_fh, '>', $boot_csource_file
    or die "Can't open file $boot_csource_file:$!";

  print $boot_csource_fh $boot_csource;
}

sub compile_bootstrap_csource {
  my ($self, $target_package_name) = @_;
  
  my $build_dir = $self->builder->build_dir;

  my $bconf = SPVM::Builder::Config->new_c99;
  my $config = $bconf->to_hash;
  
  # Compile source files
  my $quiet = $self->{quiet};
  $quiet = 0;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($target_package_name);
  my $object_file = $self->builder->create_build_object_path("$package_name_rel_file.boot.o");
  my $src_file = $self->builder->create_build_src_path("$package_name_rel_file.boot.c");
  
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

sub compile_spvm_compiler_and_runtime_csources {
  my ($self) = @_;

  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # Add SPVM include directory
  my $spvm_compiler_and_runtime_include_dir = $spvm_builder_dir;
  $spvm_compiler_and_runtime_include_dir .= '/include';

  # Add SPVM src directory
  my $spvm_compiler_and_runtime_src_dir = "$spvm_builder_dir/src";
  
  my @spvm_compiler_and_runtime_src_files = map { "$spvm_compiler_and_runtime_src_dir/$_" } @SPVM_RUNTIME_SRC_BASE_NAMES;
  
  # Config
  my $bconf = SPVM::Builder::Config->new_c99;;
  
  # Default include path
  $bconf->append_extra_compiler_flags("-Iblib/lib/SPVM/Builder/include");
  
  $bconf->set_quiet(0);

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Object dir
  my $object_dir = $self->builder->create_build_object_path;
  mkpath $object_dir;
  
  # Compile source files
  my $quiet = $self->{quiet};
  $quiet = 0;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_files = [];
  for my $src_file (@spvm_compiler_and_runtime_src_files) {
    # Object file
    my $object_file = "$object_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $bconf->get_include_dirs,
      extra_compiler_flags => $bconf->get_extra_compiler_flags,
    );
    push @$object_files, $object_file;
  }
}

sub link {
  my ($self, $target_package_name) = @_;
  
  my $builder = $self->builder;
  
  # Compiled package names
  my $package_names = $builder->get_package_names;
  
  my $build_dir = $self->builder->build_dir;
  
  my $build_work_object_dir = $self->builder->create_build_object_path;
  
  my $object_files = [];
  my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($target_package_name);
  push @$object_files, glob "$build_work_object_dir/$target_package_name.boot.o";
  
  my $bconf = SPVM::Builder::Config->new_c99;
  
  # CBuilder configs
  my $lddlflags = $bconf->get_lddlflags;
  
  my $output_name = $self->{output_name};

  my $lib_dirs_str = join(' ', map { "-L$_" } @{$bconf->get_lib_dirs});
  my $libs_str = join(' ', map { "-l$_" } @{$bconf->get_libs});
  my $extra_linker_flag = $bconf->get_extra_linker_flags;
  
  $extra_linker_flag = "$lib_dirs_str $libs_str $extra_linker_flag";
  
  # SPVM runtime object files
  my @spvm_compiler_and_runtime_object_files = map { my $tmp = "$build_work_object_dir/$_"; $tmp =~ s/\.c$/.o/; $tmp} @SPVM_RUNTIME_SRC_BASE_NAMES;
  push @$object_files, @spvm_compiler_and_runtime_object_files;
  
  # SPVM module source object files
  for my $package_name (@$package_names) {
    my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
    my $module_source_object_file = $self->builder->create_build_object_path("$package_name_rel_file.modsrc.o");
    push @$object_files, $module_source_object_file;
  }
  
  # SPVM precompile object files
  my $package_names = $builder->get_package_names;
  my $precompile_object_files = [];
  for my $precompile_package_name (@$package_names) {
    
    my $precompile_sub_names = $builder->get_precompile_sub_names($precompile_package_name);
    if (@$precompile_sub_names) {
      my $category = 'precompile';
      my $precompile_object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($precompile_package_name, $category, 'o');
      my $precompile_object_file = $self->builder->create_build_object_path($precompile_object_rel_file);
      push @$precompile_object_files, $precompile_object_file;
    }
  }
  push @$object_files, @$precompile_object_files;
  
  # ExeUtils::CBuilder config
  my $config = $bconf->to_hash;
  
  my $quiet = $self->{quiet};
  $quiet = 0;
  my $exe_file = $output_name;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $tmp_dll_file = $cbuilder->link_executable(
    objects => $object_files,
    module_name => $target_package_name,
    exe_file => $exe_file,
    extra_linker_flags => $extra_linker_flag,
  );
}

1;
