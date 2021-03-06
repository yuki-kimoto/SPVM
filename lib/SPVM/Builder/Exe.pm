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

# Accessors
sub builder { shift->{builder} }
sub build_dir { shift->builder->build_dir }
sub target_package_name { shift->{target_package_name} }
sub output_file { shift->{output_file} }
sub quiet { shift->{quiet} }
sub module_dirs { shift->{module_dirs} }
sub optimize { shift->{optimize} }
sub extra_compiler_flags { shift->{extra_compiler_flags} }
sub extra_linker_flags { shift->{extra_linker_flags} }
sub force { shift->{force} }

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  # Include directries
  my $module_dirs = $self->{module_dirs};
  unless (exists $self->{module_dirs}) {
    $self->{module_dirs} = [];
  }

  # Target package name
  my $target_package_name = $self->{target_package_name};
  unless (defined $target_package_name) {
    confess "Package name not specified";
  }
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    $output_file = $target_package_name;
    $output_file =~ s/::/__/g;
    $self->{output_file} = $output_file;
  }
  
  # Quiet output
  unless (exists $self->{quiet}) {
    $self->{quiet} = 0;
  }
  
  # Build directory
  my $build_dir = delete $self->{build_dir};
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
    module_dirs => $module_dirs
  );
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Target package name
  my $target_package_name = $self->{target_package_name};
  
  # Excutable file name
  my $output_file = $self->{output_file};
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;
  
  # Compile SPVM
  my $compile_success = $builder->compile_spvm($target_package_name, __FILE__, __LINE__);
  unless ($compile_success) {
    exit(255);
  }

  # Create precompile C sources
  $self->create_precompile_csources;
  
  # Compile precompile C sources
  $self->compile_precompile_csources;

  # Compile precompile C sources
  my ($native_object_files, $all_libs) = $self->compile_native_csources;

  # Create SPMV module C sources
  $self->create_spvm_module_csources;

  # Compile SPVM compiler and runtime C sources
  $self->compile_spvm_module_csources;

  # Compile SPVM compiler and runtime C sources
  $self->compile_spvm_compiler_and_runtime_csources;

  # Create bootstrap C source
  $self->create_bootstrap_csource;

  # Compile bootstrap C source
  $self->compile_bootstrap_csource;

  # Link and generate executable file
  $self->link($native_object_files, $all_libs);
}

sub create_precompile_csources {
  my ($self) = @_;

  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Build precompile packages
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => $self->quiet,
    force => $self->force,
  );

  my $package_names = $builder->get_package_names;
  for my $package_name (@$package_names) {
    next if $package_name =~ /::anon/;
    
    my $precompile_sub_names = $builder->get_sub_names($package_name, 'precompile');
    if (@$precompile_sub_names) {
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      $builder_c_precompile->create_precompile_csource(
        $package_name,
        {
          src_dir => $src_dir,
        }
      );
    }
  }
}

sub compile_precompile_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Build precompile packages
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => $self->quiet,
    optimize => $self->optimize,
    extra_compiler_flags => $self->extra_compiler_flags,
    force => $self->force,
  );
  
  my $package_names = $builder->get_package_names;
  for my $package_name (@$package_names) {
    next if $package_name =~ /::anon/;
    
    my $precompile_sub_names = $builder->get_sub_names($package_name, 'precompile');
    if (@$precompile_sub_names) {
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      
      my $object_dir = $self->builder->create_build_object_path;
      mkpath $object_dir;
      
      $builder_c_precompile->compile(
        $package_name,
        {
          src_dir => $src_dir,
          object_dir => $object_dir,
        }
      );
    }
  }
}

sub compile_native_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Build native packages
  my $builder_c_native = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'native',
    builder => $builder,
    quiet => $self->quiet,
    optimize => $self->optimize,
    extra_compiler_flags => $self->extra_compiler_flags,
    force => $self->force,
  );
  
  my $package_names = $builder->get_package_names;
  my $all_libs = [];
  my $all_object_files = [];
  for my $package_name (@$package_names) {
    
    my $native_sub_names = $builder->get_sub_names($package_name, 'native');
    if (@$native_sub_names) {
      my $native_module_file = $builder->get_module_file($package_name);
      my $native_dir = $native_module_file;
      
      my $bconf = $builder->get_config($package_name, 'native');
      push @$all_libs, $bconf->get_libs;
      
      $native_dir =~ s/\.spvm$//;
      $native_dir .= 'native';
      my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($native_module_file, $package_name);
      my $object_dir = $self->builder->create_build_object_path;
      mkpath $object_dir;
      my $object_files = $builder_c_native->compile(
        $package_name,
        {
          src_dir => $src_dir,
          object_dir => $object_dir,
        }
      );
      push @$all_object_files, @$object_files;
    }
  }
  
  return ($all_object_files, $all_libs);
}

sub create_spvm_module_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  # Compiled package names
  my $package_names = $builder->get_package_names;
  
  for my $package_name (@$package_names) {
    # This source is UTF-8 binary
    my $module_source = $builder->get_module_source($package_name);

    my $loaded_module_file = $builder->get_loaded_module_file($package_name);

    my $build_dir = $self->builder->build_dir;
    my $build_src_dir = $self->builder->create_build_src_path;
    my $module_source_base = $package_name;
    $module_source_base =~ s|::|/|g;
    my $module_source_csource_file = "$build_src_dir/$module_source_base.modsrc.c";
    
    my $do_create;
    if ($self->force) {
      $do_create = 1;
    }
    else {
      if (!-f $module_source_csource_file) {
        $do_create = 1;
      }
      else {
        my $loaded_module_file_mtime;
        if (defined $loaded_module_file) {
          $loaded_module_file_mtime = (stat($loaded_module_file))[9];
        }
        else {
          $loaded_module_file_mtime = 0;
        }
        
        my $module_source_csource_file_mtime = (stat($module_source_csource_file))[9];
        
        if ($loaded_module_file_mtime > $module_source_csource_file_mtime) {
          $do_create = 1;
        }
      }
    }
    
    if ($do_create) {
      my $module_source_c_hex = $module_source;
      
      # Escape to Hex C launguage string literal
      $module_source_c_hex =~ s/(.)/$_ = sprintf("\\x%02X", ord($1));$_/ges;
      
      # native package name
      my $package_cname = $package_name;
      $package_cname =~ s/::/__/g;

      my $get_module_source_csource = <<"EOS";
static const char* module_source = "$module_source_c_hex";
const char* SPMODSRC__${package_cname}__get_module_source() {
  return module_source;
}
EOS

      # Build source directory
      mkpath $build_src_dir;
      
      mkpath dirname $module_source_csource_file;
      
      open my $module_source_csource_fh, '>', $module_source_csource_file
        or die "Can't open file $module_source_csource_file:$!";

      print $module_source_csource_fh $get_module_source_csource;
    }
  }
}

sub compile_spvm_module_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  # Compiled package names
  my $package_names = $builder->get_package_names;
  
  # Config
  my $bconf = SPVM::Builder::Config->new_c99;

  # Optimize
  my $optimize = $self->optimize;
  if (defined $optimize) {
    $bconf->set_optimize($optimize);
  }
  
  # ExtUtils::CBuilder config
  my $config = $bconf->to_hash;
  
  # ExtUtils::CBuilder object
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $config);
  
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
    
    my $do_compile;
    if ($self->force) {
      $do_compile = 1;
    }
    else {
      if (!-f $module_source_object_file) {
        $do_compile = 1;
      }
      else {
        my $module_source_csource_file_mtime = (stat($module_source_csource_file))[9];
        my $module_source_object_file_mtime = (stat($module_source_object_file))[9];
        if ($module_source_csource_file_mtime > $module_source_object_file_mtime) {
          $do_compile = 1;
        }
      }
    }
    
    if ($do_compile) {
      # Compile source file
      $cbuilder->compile(
        source => $module_source_csource_file,
        object_file => $module_source_object_file,
        include_dirs => $bconf->get_include_dirs,
        extra_compiler_flags => $self->extra_compiler_flags,
        force => $self->force,
      );
    }
  }
}

sub create_bootstrap_csource {
  my ($self) = @_;
  
  my $target_package_name = $self->target_package_name;

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
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_basic_type.h"

EOS
  
  $boot_csource .= "// module source get functions declaration\n";
  for my $package_name (@$package_names) {
    my $package_cname = $package_name;
    $package_cname =~ s/::/__/g;
    $boot_csource .= <<"EOS";
const char* SPMODSRC__${package_cname}__get_module_source();
EOS
  }

  my $package_names_including_anon = $self->builder->get_package_names_including_anon;
  $boot_csource .= "// precompile functions declaration\n";
  for my $package_name (@$package_names_including_anon) {
    my $precompile_sub_names = $builder->get_sub_names($package_name, 'precompile');
    for my $sub_name (@$precompile_sub_names) {
      my $package_cname = $package_name;
      $package_cname =~ s/::/__/g;
      $boot_csource .= <<"EOS";
int32_t SPPRECOMPILE__${package_cname}__$sub_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $boot_csource .= "// native functions declaration\n";
  for my $package_cname (@$package_names) {
    my $native_sub_names = $builder->get_sub_names($package_cname, 'native');
    for my $sub_name (@$native_sub_names) {
      my $package_cname = $package_cname;
      $package_cname =~ s/::/__/g;
      $boot_csource .= <<"EOS";
int32_t SPNATIVE__${package_cname}__$sub_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
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
    my $package_cname = $package_name;
    $package_cname =~ s/::/__/g;
    
    $boot_csource .= "  {\n";
    $boot_csource .= "    const char* module_source = SPMODSRC__${package_cname}__get_module_source();\n";
    $boot_csource .= qq(    SPVM_HASH_insert(compiler->module_source_symtable, "$package_name", strlen("$package_name"), (void*)module_source);\n);
    $boot_csource .= "  }\n";
  }
  $boot_csource .= "\n";

  $boot_csource .= <<'EOS';

  SPVM_COMPILER_compile(compiler);

  if (compiler->error_count > 0) {
    exit(1);
  }
EOS
  
  for my $package_name (@$package_names_including_anon) {
    my $package_cname = $package_name;
    $package_cname =~ s/::/__/g;
    
    my $precompile_sub_names = $builder->get_sub_names($package_name, 'precompile');
    
    for my $precompile_sub_name (@$precompile_sub_names) {
      $boot_csource .= <<"EOS";
  { 
    const char* package_name = "$package_name";
    const char* sub_name = "$precompile_sub_name";
    SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, package_name, strlen(package_name));
    assert(basic_type);
    SPVM_PACKAGE* package = basic_type->package;
    assert(package);
    SPVM_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
    assert(sub);
    sub->precompile_address = SPPRECOMPILE__${package_cname}__$precompile_sub_name;
  }
EOS
    }
  }

  for my $package_name (@$package_names) {
    my $package_cname = $package_name;
    $package_cname =~ s/::/__/g;
    
    my $native_sub_names = $builder->get_sub_names($package_name, 'native');
    
    for my $native_sub_name (@$native_sub_names) {
      $boot_csource .= <<"EOS";
  { 
    const char* package_name = "$package_name";
    const char* sub_name = "$native_sub_name";
    SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, package_name, strlen(package_name));
    assert(basic_type);
    SPVM_PACKAGE* package = basic_type->package;
    assert(package);
    SPVM_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
    assert(sub);
    sub->native_address = SPNATIVE__${package_cname}__$native_sub_name;
  }
EOS
    }
  }

  $boot_csource .= <<'EOS';
    
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
  my ($self) = @_;
  
  # Target package name
  my $target_package_name = $self->target_package_name;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Config
  my $bconf = SPVM::Builder::Config->new_c99;
  
  # Optimize
  my $optimize = $self->optimize;
  if (defined $optimize) {
    $bconf->set_optimize($optimize);
  }
  
  # ExtUtils::CBuilder config
  my $config = $bconf->to_hash;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $config);
  my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($target_package_name);
  my $object_file = $self->builder->create_build_object_path("$package_name_rel_file.boot.o");
  my $src_file = $self->builder->create_build_src_path("$package_name_rel_file.boot.c");
  
  # Create directory for object file output
  mkdir dirname $object_file;
  
  # Compile source file
  $cbuilder->compile(
    source => $src_file,
    object_file => $object_file,
    include_dirs => $bconf->get_include_dirs,
    extra_compiler_flags => $self->extra_compiler_flags,
    force => $self->force,
  );
  
  return $object_file;
}

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
  $bconf->append_ccflags("-Iblib/lib/SPVM/Builder/include");
  
  # Optimize
  my $optimize = $self->optimize;
  if (defined $optimize) {
    $bconf->set_optimize($optimize);
  }
  
  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Object dir
  my $object_dir = $self->builder->create_build_object_path;
  mkpath $object_dir;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $config);
  my $object_files = [];
  for my $src_file (@spvm_compiler_and_runtime_src_files) {
    # Object file
    my $object_file = "$object_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Do compile
    my $do_compile;
    
    if ($self->force) {
      $do_compile = 1;
    }
    else {
      if (!-f $object_file) {
        $do_compile = 1;
      }
      else {
        my $mod_time_src_file = (stat($src_file))[9];
        my $mod_time_object_file = (stat($object_file))[9];
        if ($mod_time_src_file > $mod_time_object_file) {
          $do_compile = 1;
        }
      }
    }
      
    if ($do_compile) {
      
      # Compile source file
      $cbuilder->compile(
        source => $src_file,
        object_file => $object_file,
        include_dirs => $bconf->get_include_dirs,
        extra_compiler_flags => $self->extra_compiler_flags,
      );
      push @$object_files, $object_file;
    }
  }
}

sub link {
  my ($self, $native_object_files) = @_;
  
  my $target_package_name = $self->target_package_name;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $build_work_object_dir = $self->builder->create_build_object_path;
  
  my $object_files = [];
  my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($target_package_name);
  push @$object_files, glob "$build_work_object_dir/$target_package_name.boot.o";
  
  my $bconf = SPVM::Builder::Config->new_c99;
  
  # CBuilder configs
  my $lddlflags = $bconf->get_lddlflags;
  
  my $output_file = $self->{output_file};

  my $lib_dirs_str = join(' ', map { "-L$_" } @{$bconf->get_lib_dirs});
  my $libs_str = join(' ', map { "-l$_" } @{$bconf->get_libs});
  $bconf->append_lddlflags("$lib_dirs_str $libs_str");
  
  # SPVM runtime object files
  my @spvm_compiler_and_runtime_object_files = map { my $tmp = "$build_work_object_dir/$_"; $tmp =~ s/\.c$/.o/; $tmp} @SPVM_RUNTIME_SRC_BASE_NAMES;
  push @$object_files, @spvm_compiler_and_runtime_object_files;

  # Compiled package names
  my $package_names = $builder->get_package_names;
  
  # SPVM module source object files
  for my $package_name (@$package_names) {
    my $package_name_rel_file = SPVM::Builder::Util::convert_package_name_to_rel_file($package_name);
    my $module_source_object_file = $self->builder->create_build_object_path("$package_name_rel_file.modsrc.o");
    push @$object_files, $module_source_object_file;
  }
  
  # SPVM precompile object files
  my $precompile_object_files = [];
  for my $package_name (@$package_names) {
    next if $package_name =~ /::anon/;
    
    my $precompile_sub_names = $builder->get_sub_names($package_name, 'precompile');
    if (@$precompile_sub_names) {
      my $category = 'precompile';
      my $precompile_object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file($package_name, $category, 'o');
      my $precompile_object_file = $self->builder->create_build_object_path($precompile_object_rel_file);
      push @$precompile_object_files, $precompile_object_file;
    }
  }
  push @$object_files, @$precompile_object_files;

  # SPVM native object files
  push @$object_files, @$native_object_files;
  
  # ExeUtils::CBuilder config
  my $config = $bconf->to_hash;
  
  my $exe_file = $output_file;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $config);
  my $tmp_shared_lib_file = $cbuilder->link_executable(
    objects => $object_files,
    module_name => $target_package_name,
    exe_file => $exe_file,
    extra_linker_flags => $self->extra_linker_flags,
  );
}

1;
