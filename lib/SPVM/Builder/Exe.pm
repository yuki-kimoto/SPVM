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

# Fields
sub builder {
  my $self = shift;
  if (@_) {
    $self->{builder} = $_[0];
    return $self;
  }
  else {
    return $self->{builder};
  }
}

sub module_dirs {
  my $self = shift;
  if (@_) {
    $self->builder->module_dirs($_[0]);
    return $self;
  }
  else {
    return $self->builder->module_dirs;
  }
}

sub build_dir {
  my $self = shift;
  if (@_) {
    $self->builder->build_dir($_[0]);
    return $self;
  }
  else {
    return $self->builder->build_dir;
  }
}

sub class_name {
  my $self = shift;
  if (@_) {
    $self->{class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{class_name};
  }
}

sub output_file {
  my $self = shift;
  if (@_) {
    $self->{output_file} = $_[0];
    return $self;
  }
  else {
    return $self->{output_file};
  }
}

sub optimize {
  my $self = shift;
  if (@_) {
    $self->{optimize} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize};
  }
}

sub quiet {
  my $self = shift;
  if (@_) {
    $self->{quiet} = $_[0];
    return $self;
  }
  else {
    return $self->{quiet};
  }
}

sub force {
  my $self = shift;
  if (@_) {
    $self->{force} = $_[0];
    return $self;
  }
  else {
    return $self->{force};
  }
}

sub config {
  my $self = shift;
  if (@_) {
    $self->{config} = $_[0];
    return $self;
  }
  else {
    return $self->{config};
  }
}

sub config_file {
  my $self = shift;
  if (@_) {
    $self->{config_file} = $_[0];
    return $self;
  }
  else {
    return $self->{config_file};
  }
}

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  # Target class name
  my $class_name = $self->{class_name};
  unless (defined $class_name) {
    confess "Class name not specified";
  }
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    $output_file = $class_name;
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

  # Module searching directries
  my $module_dirs = delete $self->{module_dirs};
  unless (defined $module_dirs) {
    $module_dirs = [];
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
    module_dirs => $module_dirs
  );
  
  # Config file
  my $config_file = $self->{config_file};
  
  # Config
  my $config;
  if (defined $config_file) {
    $config = SPVM::Builder::Util::load_config($config_file);
  }
  else {
    $config = SPVM::Builder::Config->new_gnu99;
  }
  $self->{config} = $config;
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  my $config = $self->config;

  # Target class name
  my $class_name = $self->{class_name};
  
  # Excutable file name
  my $output_file = $self->{output_file};
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;
  
  # Compile SPVM
  my $compile_success = $builder->compile_spvm($class_name, __FILE__, __LINE__);
  unless ($compile_success) {
    $builder->printf_error_messages(*STDERR);
    exit(255);
  }
  
  # Config file
  my $module_file = $builder->get_module_file($class_name);
  
  # Object files
  my $object_files = [];

  # Compile SPVM core source files
  my $spvm_core_objects = $self->compile_spvm_core_sources;
  push @$object_files, @$spvm_core_objects;

  # Create SPMV module C source_files
  $self->create_spvm_module_sources;

  # Compile SPVM compiler and runtime C source files
  my $spvm_module_objects = $self->compile_spvm_module_sources;
  push @$object_files, @$spvm_module_objects;

  # Create precompile C source_files
  $self->create_precompile_csources;
  
  # Compile precompile C source_files
  my $precompile_object_files = $self->compile_precompile_sources;
  push @$object_files, @$precompile_object_files;

  # Compile precompile C source_files
  my $native_object_files = $self->compile_native_csources;
  push @$object_files, @$native_object_files;
  
  # Create bootstrap C source
  $self->create_bootstrap_source;

  # Compile bootstrap C source
  my $bootstrap_object_file = $self->compile_bootstrap_source;
  push @$object_files, $bootstrap_object_file;
  
  # Link and generate executable file
  $self->link($object_files);
}

sub create_source_file {
  my ($self, $opt) = @_;
  
  # Config
  my $config = $self->config;
  
  my $input_files = $opt->{input_files};
  my $output_file = $opt->{output_file};
  my $create_cb = $opt->{create_cb};
  
  my $need_generate = SPVM::Builder::Util::need_generate({
    global_force => $self->force,
    config_force => $config->force,
    output_file => $output_file,
    input_files => $input_files,
  });
  
  if ($need_generate) {
    $create_cb->();
  }
}

sub compile_source_file {
  my ($self, $opt) = @_;

  # Config
  my $config = $self->config;
  
  # Optimize
  my $optimize = $self->optimize;
  if (defined $optimize) {
    $config->optimize($optimize);
  }

  my $source_file = $opt->{source_file};
  my $output_file = $opt->{output_file};
  
  my $need_generate = SPVM::Builder::Util::need_generate({
    global_force => $self->force,
    config_force => $config->force,
    output_file => $output_file,
    input_files => [$source_file],
  });

  # Compile command
  my $builder_cc = SPVM::Builder::CC->new;

  my $compile_info = $builder_cc->create_compile_command_info({config => $config, output_file => $output_file, source_file => $source_file});
  my $cc_cmd = $builder_cc->create_compile_command({compile_info => $compile_info});

  if ($need_generate) {

    # Execute compile command
    my $cbuilder = ExtUtils::CBuilder->new;
    $cbuilder->do_system(@$cc_cmd)
      or confess "Can't compile $source_file: @$cc_cmd";
  }
}

sub create_bootstrap_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Class names
  my $class_names = $builder->get_class_names;
  
  # Module files - Input
  my $module_files = [];
  for my $class_name (@$class_names) {
    my $module_file = $builder->get_module_file($class_name);
    push @$module_files, $module_file;
  }
  
  # Source file - Output
  my $build_src_dir = $self->builder->create_build_src_path;
  my $target_perl_class_name = "SPVM::$class_name";
  my $boot_base = $target_perl_class_name;
  $boot_base =~ s|::|/|g;
  my $boot_source_file = "$build_src_dir/$boot_base.boot.c";

  # Source creating callback
  my $create_cb = sub {
    
    my $boot_source = '';
    
    $boot_source .= <<'EOS';

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
#include "spvm_class.h"
#include "spvm_method.h"
#include "spvm_basic_type.h"

EOS
    
    $boot_source .= "// module source get functions declaration\n";
    for my $class_name (@$class_names) {
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;
      $boot_source .= <<"EOS";
const char* SPMODSRC__${class_cname}__get_module_source();
EOS
    }

    my $class_names_including_anon = $self->builder->get_class_names_including_anon;
    $boot_source .= "// precompile functions declaration\n";
    for my $class_name (@$class_names_including_anon) {
      my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
      for my $method_name (@$precompile_method_names) {
        my $class_cname = $class_name;
        $class_cname =~ s/::/__/g;
        $boot_source .= <<"EOS";
int32_t SPVMPRECOMPILE__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
      }
    }

    $boot_source .= "// native functions declaration\n";
    for my $class_cname (@$class_names) {
      my $native_method_names = $builder->get_method_names($class_cname, 'native');
      for my $method_name (@$native_method_names) {
        my $class_cname = $class_cname;
        $class_cname =~ s/::/__/g;
        $boot_source .= <<"EOS";
int32_t SPVM__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
      }
    }
    
    $boot_source .= <<'EOS';

int32_t main(int32_t argc, const char *argv[]) {
EOS

    $boot_source .= <<"EOS";
  // Class name
  const char* class_name = "$class_name";
EOS

    $boot_source .= <<'EOS';
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();

  // Create use op for entry point class
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, class_name, class_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, class_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Set module source_files
EOS
    
    for my $class_name (@$class_names) {
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;
      
      $boot_source .= "  {\n";
      $boot_source .= "    const char* module_source = SPMODSRC__${class_cname}__get_module_source();\n";
      $boot_source .= qq(    SPVM_HASH_insert(compiler->module_source_symtable, "$class_name", strlen("$class_name"), (void*)module_source);\n);
      $boot_source .= "  }\n";
    }
    $boot_source .= "\n";

    $boot_source .= <<'EOS';

  SPVM_COMPILER_compile(compiler);

  if (SPVM_COMPILER_get_error_count(compiler) > 0) {
    SPVM_COMPILER_print_error_messages(compiler, stderr);
    exit(1);
  }
EOS
    
    for my $class_name (@$class_names_including_anon) {
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;
      
      my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
      
      for my $precompile_method_name (@$precompile_method_names) {
        $boot_source .= <<"EOS";
  { 
    const char* class_name = "$class_name";
    const char* method_name = "$precompile_method_name";
    SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, class_name, strlen(class_name));
    assert(basic_type);
    SPVM_CLASS* class = basic_type->class;
    assert(class);
    SPVM_METHOD* method = SPVM_HASH_fetch(class->method_symtable, method_name, strlen(method_name));
    assert(method);
    method->precompile_address = SPVMPRECOMPILE__${class_cname}__$precompile_method_name;
  }
EOS
      }
    }

    for my $class_name (@$class_names) {
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;
      
      my $native_method_names = $builder->get_method_names($class_name, 'native');
      
      for my $native_method_name (@$native_method_names) {
        $boot_source .= <<"EOS";
  { 
    const char* class_name = "$class_name";
    const char* method_name = "$native_method_name";
    SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, class_name, strlen(class_name));
    assert(basic_type);
    SPVM_CLASS* class = basic_type->class;
    assert(class);
    SPVM_METHOD* method = SPVM_HASH_fetch(class->method_symtable, method_name, strlen(method_name));
    assert(method);
    method->native_address = SPVM__${class_cname}__$native_method_name;
  }
EOS
      }
    }

    $boot_source .= <<'EOS';
    
  // Create env
  SPVM_ENV* env = SPVM_API_create_env(compiler);
  
  // Class
  int32_t method_id = SPVM_API_get_class_method_id(env, class_name, "main", "int(string,string[])");
  
  if (method_id < 0) {
    fprintf(stderr, "Can't find the definition of valid %s->main method:.\n    static method main : int ($start_file : string, $args : string[]) { ... } \n", class_name);
    return -1;
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // Starting file name
  void* cmd_start_file_obj = env->new_string(env, argv[0], strlen(argv[0]));
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_muldim_array(env, arg_type_basic_id, 1, argc - 1);
  
  // Set command line arguments
  for (int32_t arg_index = 1; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_elem_object(env, cmd_args_obj, arg_index - 1, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_start_file_obj;
  stack[1].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_spvm_method(env, method_id, stack);
  
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

    # Build source directory
    my $build_src_dir = $self->builder->create_build_src_path;
    mkpath $build_src_dir;
    mkpath dirname $boot_source_file;
    
    open my $boot_source_fh, '>', $boot_source_file
      or die "Can't open file $boot_source_file:$!";

    print $boot_source_fh $boot_source;
  };
  
  # Create source file
  $self->create_source_file({
    input_files => $module_files,
    output_file => $boot_source_file,
    create_cb => $create_cb,
  });
}

sub compile_bootstrap_source {
  my ($self) = @_;
  
  # Target class name
  my $class_name = $self->class_name;
  
  my $target_perl_class_name = "SPVM::$class_name";
  
  # Compile source files
  my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($target_perl_class_name);
  my $object_file = $self->builder->create_build_object_path("$class_name_rel_file.boot.o");
  my $source_file = $self->builder->create_build_src_path("$class_name_rel_file.boot.c");
  
  # Create directory for object file output
  mkdir dirname $object_file;
  
  # Compile
  $self->compile_source_file({source_file => $source_file, output_file => $object_file});
  
  return $object_file;
}

sub compile_spvm_core_sources {
  my ($self) = @_;

  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # Add SPVM src directory
  my $spvm_core_source_dir = "$spvm_builder_dir/src";
  
  # SPVM runtime source files
  my @spvm_runtime_src_base_names = qw(
    spvm_allow.c
    spvm_api.c
    spvm_array_field_access.c
    spvm_basic_type.c
    spvm_block.c
    spvm_call_method.c
    spvm_case_info.c
    spvm_allocator.c
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
    spvm_list.c
    spvm_my.c
    spvm_op.c
    spvm_op_checker.c
    spvm_opcode_array.c
    spvm_opcode_builder.c
    spvm_opcode.c
    spvm_class.c
    spvm_class_var_access.c
    spvm_class_var.c
    spvm_string_buffer.c
    spvm_method.c
    spvm_switch_info.c
    spvm_toke.c
    spvm_type.c
    spvm_use.c
    spvm_var.c
    spvm_yacc.c
    spvm_yacc_util.c
  );

  my @spvm_core_source_files = map { "$spvm_core_source_dir/$_" } @spvm_runtime_src_base_names;
  
  # Object dir
  my $object_dir = $self->builder->create_build_object_path;
  mkpath $object_dir;
  
  # Compile source files
  my $object_files = [];
  for my $src_file (@spvm_core_source_files) {
    # Object file
    my $object_file = "$object_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    $self->compile_source_file({source_file => $src_file, output_file => $object_file});
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub create_spvm_module_sources {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Compiled class names
  my $class_names = $builder->get_class_names;
  
  for my $class_name (@$class_names) {
    
    # Moudle file - Input
    my $module_file = $builder->get_module_file($class_name);
    
    # Source file - Output
    my $build_dir = $self->builder->build_dir;
    my $build_src_dir = $self->builder->create_build_src_path;
    my $perl_class_name = "SPVM::$class_name";
    my $module_source_base = $perl_class_name;
    $module_source_base =~ s|::|/|g;
    my $module_source_csource_file = "$build_src_dir/$module_source_base.modsrc.c";
    
    # Source creating callback
    my $create_cb = sub {
      # This source is UTF-8 binary
      my $module_source = $builder->get_module_source($class_name);
      my $module_source_c_hex = $module_source;
      
      # Escape to Hex C launguage string literal
      $module_source_c_hex =~ s/(.)/$_ = sprintf("\\x%02X", ord($1));$_/ges;
      
      # native class name
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;

      my $get_module_source_csource = <<"EOS";
static const char* module_source = "$module_source_c_hex";
const char* SPMODSRC__${class_cname}__get_module_source() {
return module_source;
}
EOS
      mkpath dirname $module_source_csource_file;
      
      open my $module_source_csource_fh, '>', $module_source_csource_file
        or die "Can't open file $module_source_csource_file:$!";

      print $module_source_csource_fh $get_module_source_csource;
    };
    
    # Create source file
    $self->create_source_file({
      input_files => [$module_file],
      output_file => $module_source_csource_file,
      create_cb => $create_cb,
    });
  }
}

sub compile_spvm_module_sources {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  # Compile module source files
  my $class_names = $builder->get_class_names;
  my $object_files = [];
  for my $class_name (@$class_names) {
    my $perl_class_name = "SPVM::$class_name";
    
    # Build source directory
    my $build_src_dir = $self->builder->create_build_src_path;
    
    # Create source directory
    my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($perl_class_name);
    my $source_file = "$build_src_dir/$class_name_rel_file.modsrc.c";
    mkpath dirname $source_file;
    
    # Create object directory
    my $build_object_dir = $self->builder->create_build_object_path;
    mkpath $build_object_dir;
    my $object_file = "$build_object_dir/$class_name_rel_file.modsrc.o";
    mkpath dirname $object_file;
    
    # Compile
    $self->compile_source_file({source_file => $source_file, output_file => $object_file});
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub create_precompile_csources {
  my ($self) = @_;

  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Build precompile classes
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => $self->quiet,
    force => $self->force,
  );

  my $class_names = $builder->get_class_names;
  for my $class_name (@$class_names) {
    my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
    if (@$precompile_method_names) {
      
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      $builder_c_precompile->create_precompile_csource(
        $class_name,
        {
          src_dir => $src_dir,
        }
      );
    }
  }
}

sub compile_precompile_sources {
  my ($self) = @_;
  
  # Builer
  my $builder = $self->builder;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Build precompile classes
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => $self->quiet,
    optimize => $self->optimize,
    force => $self->force,
  );
  
  my $class_names = $builder->get_class_names;
  my $object_files = [];
  for my $class_name (@$class_names) {
    my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
    if (@$precompile_method_names) {
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      
      my $object_dir = $self->builder->create_build_object_path;
      mkpath $object_dir;
      
      my $precompile_object_files = $builder_c_precompile->compile(
        $class_name,
        {
          src_dir => $src_dir,
          object_dir => $object_dir,
        }
      );
      push @$object_files, @$precompile_object_files;
    }
  }
  
  return $object_files;
}

sub compile_native_csources {
  my ($self) = @_;
  
  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Build native classes
  my $builder_c_native = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'native',
    builder => $builder,
    quiet => $self->quiet,
    optimize => $self->optimize,
    force => $self->force,
  );
  
  my $class_names = $builder->get_class_names;
  my $all_object_files = [];
  for my $class_name (@$class_names) {

    my $perl_class_name = "SPVM::$class_name";
    
    my $native_method_names = $builder->get_method_names($class_name, 'native');
    if (@$native_method_names) {
      my $native_module_file = $builder->get_module_file($class_name);
      my $native_dir = $native_module_file;
      
      $native_dir =~ s/\.spvm$//;
      $native_dir .= 'native';
      my $src_dir = SPVM::Builder::Util::remove_class_part_from_file($native_module_file, $perl_class_name);
      my $object_dir = $self->builder->create_build_object_path;
      mkpath $object_dir;
      
      my $object_files = $builder_c_native->compile(
        $class_name,
        {
          src_dir => $src_dir,
          object_dir => $object_dir,
        }
      );
      push @$all_object_files, @$object_files;
    }
  }
  
  return $all_object_files;
}

sub link {
  my ($self, $object_files) = @_;
  
  my $class_name = $self->class_name;
  
  my $config = $self->config;
  
  # CBuilder configs
  my $output_file = $self->{output_file};

  my $lib_dirs_str = join(' ', map { "-L$_" } @{$config->lib_dirs});
  $config->add_ldflags("$lib_dirs_str");
  
  # Linker
  my $ld = $config->ld;
  
  # Linker flags
  my $ldflags = $config->ldflags;
  my $ldflags_str = join(' ', @{$config->ldflags});
  $ldflags_str = "$ldflags_str";
  
  # Linker optimize
  my $ld_optimize = $config->ld_optimize;
  $ldflags_str .= " $ld_optimize";
  
  # ExeUtils::CBuilder config
  my $cbuilder_config = {
    ld => $ld,
    lddlflags => $ldflags_str,
    shrpenv => '',
    perllibs => '',
    libpth => '',
  };
  
  my $need_generate = SPVM::Builder::Util::need_generate({
    global_force => $self->force,
    config_force => $config->force,
    output_file => $output_file,
    input_files => $object_files,
  });
  
  if ($need_generate) {
    # Create the executable file
    my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $cbuilder_config);
    $cbuilder->link_executable(
      objects => $object_files,
      module_name => $class_name,
      exe_file => $output_file,
    );
  }
  
  return $output_file;
}

1;

=head1 NAME

SPVM::Builder::Exe - Create a Executable File
