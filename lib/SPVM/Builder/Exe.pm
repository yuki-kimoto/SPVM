package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config::Exe;

use SPVM::Builder::Native::Compiler;
use SPVM::Builder::Native::Runtime;
use SPVM::Builder::Native::BasicType;
use SPVM::Builder::Native::ClassFile;
use SPVM::Builder::ScriptInfo;

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

sub script_name {
  my $self = shift;
  if (@_) {
    $self->{script_name} = $_[0];
    return $self;
  }
  else {
    return $self->{script_name};
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

sub compiler {
  my $self = shift;
  if (@_) {
    $self->{compiler} = $_[0];
    return $self;
  }
  else {
    return $self->{compiler};
  }
}

sub runtime {
  my $self = shift;
  if (@_) {
    $self->{runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{runtime};
  }
}

sub allow_no_config_file {
  my $self = shift;
  if (@_) {
    $self->{allow_no_config_file} = $_[0];
    return $self;
  }
  else {
    return $self->{allow_no_config_file};
  }
}

sub mode {
  my $self = shift;
  if (@_) {
    $self->{mode} = $_[0];
    return $self;
  }
  else {
    return $self->{mode};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my %options = @_;
  
  my $build_dir = delete $options{build_dir};
  
  my $self = bless {
    ccflags_global => [],
    ccflags_spvm => [],
    ccflags_native => [],
    ccflags_native_class => {},
    ccflags_precompile => [],
    defines_global => [],
    defines_spvm => [],
    defines_native => [],
    defines_native_class => {},
    defines_precompile => [],
    optimize_native_class => {},
    %options
  }, $class;
  
  my $script_name = $self->{script_name};
  
  unless (defined $script_name) {
    confess("A script name must be defined.");
  }
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    confess("A output file must be defined.");
  }
  
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
  );
  
  # Config file
  my $allow_no_config_file = $self->{allow_no_config_file};
  
  my $config_mode = $self->{mode};
  
  # Config
  my $config_file = $script_name;
  $config_file =~ s/\..*$//;
  $config_file .= '.config';
  
  my $config;
  if (-f $config_file) {
    $config = SPVM::Builder::Config::Exe->load_mode_config($config_file, $config_mode);
  }
  else {
    if ($allow_no_config_file) {
      $config = SPVM::Builder::Config::Exe->new(file_optional => 1);
    }
    else {
      confess("The config file \"$config_file\" is not found.");
    }
  }
  
  unless ($config->isa('SPVM::Builder::Config::Exe')) {
    confess("The class of a config object for creating an executable file must be SPVM::Builder::Config::Exe or its child class.");
  }
  
  unless ($config->output_type eq 'exe') {
    confess("output_type field in the config file \"$config_file\" for creating an executable file must be \"exe\".");
  }
  
  $self->{config} = $config;
  
  $self->{builder} = $builder;
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  for my $include_dir (@{$builder->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $self->{compiler} = $compiler;
  
  $config->ccflags_global($self->{ccflags_global});
  $config->ccflags_spvm($self->{ccflags_spvm});
  $config->ccflags_native($self->{ccflags_native});
  $config->{ccflags_native_class} = $self->{ccflags_native_class};
  $config->ccflags_precompile($self->{ccflags_precompile});
  $config->defines_global($self->{defines_global});
  $config->defines_spvm($self->{defines_spvm});
  $config->defines_native($self->{defines_native});
  $config->{defines_native_class} = $self->{defines_native_class};
  $config->defines_precompile($self->{defines_precompile});
  $config->optimize_global($self->{optimize_global});
  $config->optimize_spvm($self->{optimize_spvm});
  $config->optimize_native($self->{optimize_native});
  $config->{optimize_native_class} = $self->{optimize_native_class};
  $config->optimize_precompile($self->{optimize_precompile});
  
  $self->compile;
  
  return $self;
}

# Instance Methods
sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  my $class_name = $self->{class_name};
  
  my $class = $self->runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $class->get_class_file;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Object files
  my $object_files = [];
  
  # Create bootstrap C source
  $self->create_bootstrap_source;
  
  # Compile bootstrap C source
  my $bootstrap_object_file = $self->compile_bootstrap_source_file;
  push @$object_files, $bootstrap_object_file;
  
  # Compile SPVM core source files
  my $spvm_object_files = $self->compile_spvm_core_source_files;
  push @$object_files, @$spvm_object_files;
  
  my $classes_object_files = $self->compile_classes;
  push @$object_files, @$classes_object_files;
  
  # Link and generate executable file
  my $config_linker = $self->config->clone;
  my $cc_linker = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  $config_linker->output_file($self->{output_file});
  
  $cc_linker->link($class_name, $object_files, {config => $config_linker});
}

sub compile {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $script_name = $self->{script_name};
  
  my $compiler = $self->compiler;
  
  open my $script_fh, '<', $script_name
    or die "Can't open file \"$script_name\":$!";
    
  my $source = do { local $/; <$script_fh> };
  
  $source = "#file \"$script_name\"\x{A}$source";
  
  my $class_name = $compiler->compile_anon_class_with_exit($source, __FILE__, __LINE__);
  
  $self->class_name($class_name);
  
  $self->config->class_name($class_name);
  
  my $runtime = $compiler->get_runtime;
  
  $self->runtime($runtime);
  
}

sub compile_classes {
  my ($self) = @_;
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $object_files = [];
  for my $class_name (@$class_names) {
    
    my $precompile_object_files = $self->compile_precompile_class($class_name);
    push @$object_files, @$precompile_object_files;
    
    my $native_object_files = $self->compile_native_class($class_name);
    push @$object_files, @$native_object_files;
  }
  
  return $object_files;
}

sub compile_source_file {
  my ($self, $options) = @_;
  
  my $source_file = $options->{source_file};
  my $output_file = $options->{output_file};
  my $config = $options->{config};
  my $config_exe = $self->config;
  
  $config->config_exe($config_exe);
  
  my $config_exe_loaded_config_files = $config_exe->get_loaded_config_files;
  my $config_loaded_config_files = $config->get_loaded_config_files;
  my $need_generate_input_files = [$source_file, @$config_loaded_config_files, @$config_exe_loaded_config_files];
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config->force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });
  
  my $builder = $self->builder;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Compile command
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $compile_info = SPVM::Builder::CompileInfo->new(
    output_file => $output_file,
    source_file => $source_file,
    config => $config,
    category => $options->{category},
  );
  
  if ($need_generate) {
    $builder_cc->compile_source_file($compile_info);
  }
  
  my $object_file_name = $compile_info->output_file;
  my $object_file = SPVM::Builder::ObjectFileInfo->new(
    file => $object_file_name,
    compile_info => $compile_info,
  );
  
  return $object_file;
}

sub create_bootstrap_header_source {
  my ($self) = @_;

  # Config
  my $config_exe = $self->config;

  # Builder
  my $builder = $self->builder;

  my $class_name = $self->class_name;

  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $source = '';
  
  $source .= <<'EOS';

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <assert.h>

#include "spvm_native.h"

EOS
  
  $source .= "// precompile functions declaration\n";
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    my $precompile_method_names = $class->get_precompile_method_names;
    for my $method_name (@$precompile_method_names) {
      my $class_cname = $class_name;
      $class_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVMPRECOMPILE__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
    
    my $basic_type = $self->runtime->get_basic_type_by_name($class_name);
    my $anon_basic_type_names = $basic_type->get_anon_basic_type_names;
    for my $anon_basic_type_name (@$anon_basic_type_names) {
      my $anon_basic_type_cname = $anon_basic_type_name;
      $anon_basic_type_cname =~ s/::/__/g;
      
      my $anon_basic_type = $self->runtime->get_basic_type_by_name($anon_basic_type_name);
      my $anon_method = $anon_basic_type->get_method_by_name("");
      if ($anon_method->is_precompile) {
        $source .= <<"EOS";
int32_t SPVMPRECOMPILE__${anon_basic_type_cname}__(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
      }
    }
  }

  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env);\n";

  $source .= <<"EOS";
static void SPVM_BOOTSTRAP_set_precompile_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* precompile_address) {
void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, method_name);
env->api->method->set_precompile_address(env->runtime, method, precompile_address);
}
EOS
  
  $source .= "// native functions declaration\n";
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    my $native_method_names = $class->get_native_method_names;
    for my $method_name (@$native_method_names) {
      my $class_name = $class_name;
      $class_name =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVM__${class_name}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env);\n\n";

  $source .= "static void* SPVM_BOOTSTRAP_get_runtime(SPVM_ENV* env, void* compiler);\n\n";

  $source .= <<"EOS";
static void SPVM_BOOTSTRAP_set_native_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* native_address) {
  void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
  void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, method_name);
  env->api->method->set_native_address(env->runtime, method, native_address);
}
EOS

  return $source;
}

sub create_bootstrap_main_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  my $class_name = $self->class_name;

  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $warning = $^W ? 1 : 0;
  
  my $source = '';

  $source .= <<"EOS";

int32_t main(int32_t command_args_length, const char *command_args[]) {
  
  int32_t error_id = 0;
  
  SPVM_ENV* boot_env = SPVM_NATIVE_new_env();
  
  void* compiler = boot_env->api->compiler->new_instance();
  
  void* runtime = SPVM_BOOTSTRAP_get_runtime(boot_env, compiler);
  
  SPVM_ENV* env = boot_env->new_env();
  
  env->runtime = runtime;
  
  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(env->runtime);
  
  SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(env);
  
  SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(env);
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  // Set the program name and the command line arguments
  {
    int32_t mortal_stack_top = env->enter_scope(env, stack);
    
    void* obj_program_name = env->new_string(env, stack, command_args[0], strlen(command_args[0]));
    
    // ARGV - string[]
    void* obj_argv = env->new_string_array(env, stack, command_args_length - 1);
    for (int32_t arg_index = 1; arg_index < command_args_length; arg_index++) {
      void* obj_arg = env->new_string(env, stack, command_args[arg_index], strlen(command_args[arg_index]));
      env->set_elem_object(env, stack, obj_argv, arg_index - 1, obj_arg);
    }
    
    int64_t base_time = time(NULL);
    
    // Set command line info
    {
      error_id = env->set_command_info_program_name(env, stack, obj_program_name);
      
      if (error_id) {
        env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        goto END_OF_FUNC;
      }
      
      error_id = env->set_command_info_argv(env, stack, obj_argv);
      
      if (error_id) {
        env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        goto END_OF_FUNC;
      }
      
      error_id = env->set_command_info_basetime(env, stack, base_time);
      if (error_id) {
        env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        goto END_OF_FUNC;
      }
      
      error_id = env->set_command_info_warning(env, stack, $warning);
      if (error_id) {
        env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        goto END_OF_FUNC;
      }
    }
    
    env->leave_scope(env, stack, mortal_stack_top);
  }
  
  const char* class_name = "$class_name";
  
  error_id = env->check_bootstrap_method(env, stack, class_name);
  
  if (error_id) {
    env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
    goto END_OF_FUNC;
  }
  
  error_id = env->call_init_methods(env, stack);
  if (error_id) {
    goto END_OF_FUNC;
  }
  
  void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
  void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, "main");
  
  int32_t args_width = 0;
  error_id = env->call_method(env, stack, method, args_width);
  if (error_id) {
    error_id = env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (error_id) {
    env->print_stderr(env, stack, env->get_exception(env, stack));
    fprintf(spvm_stderr, "\\n");
  }
  
  env->destroy_class_vars(env, stack);
  
  env->free_stack(env, stack);
  
  env->free_env(env);
  
  boot_env->api->compiler->free_instance(compiler);
  
  boot_env->free_env(boot_env);
  
  return error_id;
}
EOS

  return $source;
}

sub create_bootstrap_get_runtime_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $source = '';
  
  $source .= <<"EOS";
static void* SPVM_BOOTSTRAP_get_runtime(SPVM_ENV* env, void* compiler) {
  
EOS
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $compiler = $self->compiler;
  
  for my $class_name (@$class_names) {
    
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    my $class_file = $compiler->get_class_file($class_name);
    my $class_file_rel_file = $class_file->get_rel_file;
    my $class_file_content = $class_file->get_content;
    my $class_file_content_length = $class_file->get_content_length;
    my $source_class_file = '';
    
    $source_class_file .= qq|  {\n|;
    
    $source_class_file .= qq|    env->api->compiler->add_class_file(compiler, "$class_name");\n|;
    
    $source_class_file .= qq|    void* class_file = env->api->compiler->get_class_file(compiler, "$class_name");\n|;
    
    if (defined $class_file_rel_file) {
      $source_class_file .= qq|    env->api->class_file->set_rel_file(compiler, class_file, "$class_file_rel_file");\n|;
    }
    
    if (defined $class_file_content) {
      my $content_espcaped = $class_file_content;
      
      {
        use bytes;
        $content_espcaped =~ s/\\/\\\\/g;
        $content_espcaped =~ s/"/\\"/g;
        $content_espcaped =~ s/([^[:print:]])/sprintf("\\%03o", ord($1))/ge;
      }
      
      $source_class_file .= qq|    env->api->class_file->set_content(compiler, class_file, "$content_espcaped");\n|;
    }
    
    $source_class_file .= qq|    env->api->class_file->set_content_length(compiler, class_file, $class_file_content_length);\n|;
      
    $source_class_file .= qq|  }\n|;
    
    $source .= $source_class_file;
  }
  
  $source .= qq|  env->api->compiler->set_start_file(compiler, __FILE__);\n|;
  
  $source .= qq|  env->api->compiler->set_start_line(compiler, __LINE__ + 1);\n|;
  
  my $start_class_name = $self->{class_name};
  
  $source .= qq|  int32_t error_id = env->api->compiler->compile(compiler, \"$start_class_name\");\n|;
  
  $source .= qq|  void* runtime = env->api->compiler->get_runtime(compiler);\n|;
  
  $source .= qq|  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(runtime);\n|;
  $source .= qq|  if (error_id != 0) {\n|;
  $source .= qq|    fprintf(spvm_stderr, "[Unexpected Compile Error]%s.", env->api->compiler->get_error_message(compiler, 0));\n|;
  $source .= qq|    exit(255);\n|;
  $source .= qq|  }\n|;
  
  $source .= qq|  return runtime;\n|;
  
  $source .= <<"EOS";
}
EOS
  
  return $source;
}

sub create_bootstrap_set_precompile_method_addresses_func_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $source = '';
  
  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env){\n";
  
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $precompile_method_names = $class->get_precompile_method_names;
    
    for my $precompile_method_name (@$precompile_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_precompile_method_address(env, "$class_name", "$precompile_method_name", &SPVMPRECOMPILE__${class_cname}__$precompile_method_name);
EOS
    }
    
    my $basic_type = $self->runtime->get_basic_type_by_name($class_name);
    my $anon_basic_type_names = $basic_type->get_anon_basic_type_names;
    for my $anon_basic_type_name (@$anon_basic_type_names) {
      my $anon_basic_type_cname = $anon_basic_type_name;
      $anon_basic_type_cname =~ s/::/__/g;
      
      my $anon_basic_type = $self->runtime->get_basic_type_by_name($anon_basic_type_name);
      my $anon_method = $anon_basic_type->get_method_by_name("");
      if ($anon_method->is_precompile) {
        $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_precompile_method_address(env, "$anon_basic_type_name", "", &SPVMPRECOMPILE__${anon_basic_type_cname}__);
EOS
      }
    }
  }
  
  $source .= "}\n";
  
  return $source;
}

sub create_bootstrap_set_native_method_addresses_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  my $class_names = $self->get_user_defined_basic_type_names;

  my $source = '';

  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $native_method_names = $class->get_native_method_names;
    
    for my $native_method_name (@$native_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_native_method_address(env, "$class_name", "$native_method_name", &SPVM__${class_cname}__$native_method_name);
EOS
    }
  }

  $source .= "}\n";
  
  return $source;
}

sub create_bootstrap_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $class_name = $self->class_name;
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $class_files = [];
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    if ($class->get_class_dir) {
      my $class_file = $class->get_class_file;
      push @$class_files, $class_file;
    }
  }
  
  # Source file - Output
  my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
  my $perl_class_name = "SPVM::$class_name";
  my $bootstrap_base = $perl_class_name;
  $bootstrap_base =~ s|::|/|g;
  my $bootstrap_source_file = "$build_src_dir/$bootstrap_base.boot.c";
  
  # Config
  my $config_exe = $self->config;
  
  my $input_files = [@$class_files];
  my $output_file = $bootstrap_source_file;
  
  my $config_exe_loaded_config_files = $config_exe->get_loaded_config_files;
  my $need_generate_input_files = [@$input_files, @$config_exe_loaded_config_files];
  
  my $bootstrap_source = '';
  
  # Header
  $bootstrap_source .= $self->create_bootstrap_header_source;
  
  # main function
  $bootstrap_source .= $self->create_bootstrap_main_func_source;
  
  # Set precompile method addresses function
  $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;
  
  # Set native method addresses function
  $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;
  
  $bootstrap_source .= $self->create_bootstrap_get_runtime_source;
  
  $bootstrap_source .= "\n";
  
  # For detecting chaging config mode
  my $mode_string = $self->mode;
  unless (defined $mode_string) {
    $mode_string = '';
  }
  $bootstrap_source .= "// mode:$mode_string\n";
  
  my @config_field_names = qw(
    ccflags_global
    ccflags_spvm
    ccflags_native
    ccflags_native_class
    ccflags_precompile
    defines_global
    defines_spvm
    defines_native
    defines_native_class
    defines_precompile
    optimize_global
    optimize_spvm
    optimize_native
    optimize_native_class
    optimize_precompile
  );
  
  # For detecting chaging fields
  for my $config_field_name (@config_field_names) {
    $bootstrap_source .= "// $config_field_name:" . &_field_value_to_string($config_exe->{$config_field_name}) . "\n";
  }
  
  my $bootstrap_source_original;
  if (-f $bootstrap_source_file) {
    $bootstrap_source_original = SPVM::Builder::Util::slurp_binary($bootstrap_source_file);
  }
  
  my $force = $self->force || $config_exe->force;
  
  if (defined $bootstrap_source_original && $bootstrap_source ne $bootstrap_source_original) {
    $force = 1;
    $self->force($force);
  }
  
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });
  
  if ($need_generate) {
    SPVM::Builder::Util::spurt_binary($bootstrap_source_file, $bootstrap_source);
  }
  
}

sub _field_value_to_string {
  my ($field_value) = @_;
  
  my $string;
  if (ref $field_value eq 'HASH') {
    my @option_values;
    for my $key (keys %$field_value) {
      my $value = $field_value->{$key};
      if (ref $value eq 'ARRAY') {
        for my $v (@$value) {
          push @option_values, "$key\@$v";
        }
      }
      else {
        push @option_values, "$key\@$value";
      }
    }
    $string = join(',', @option_values);
  }
  elsif (ref $field_value eq 'ARRAY') {
    $string = join(',', @$field_value);
  }
  else {
    $string = $field_value;
  }
  
  unless (length $string) {
    $string = '';
  }
  
  return $string;
}

sub compile_bootstrap_source_file {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  # Target class name
  my $class_name = $self->class_name;
  
  my $perl_class_name = "SPVM::$class_name";
  
  # Compile source files
  my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  my $object_file_name = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir, "$class_name_rel_file.boot.o");
  my $source_file = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir, "$class_name_rel_file.boot.c");
  
  # Compile
  my $object_file = $self->compile_source_file({
    source_file => $source_file,
    output_file => $object_file_name,
    config => $config_exe,
    category => 'bootstrap',
  });
  
  return $object_file;
}

sub compile_spvm_core_source_files {
  my ($self) = @_;
  
  # Config
  my $config_exe = $self->config;
  
  my $builder_dir = SPVM::Builder::Util::get_builder_dir();
  
  # SPVM src directory
  my $builder_src_dir = "$builder_dir/src";
  
  # SPVM runtime source files
  my $spvm_runtime_src_base_names;
  $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  my @spvm_core_source_files = map { "$builder_src_dir/$_" } @$spvm_runtime_src_base_names;
  
  # Object dir
  my $output_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
  
  # Compile source files
  my $object_files = [];
  for my $src_file (@spvm_core_source_files) {
    # Object file
    my $object_file_name = "$output_dir/" . basename($src_file);
    $object_file_name =~ s/\.c$//;
    $object_file_name .= '.o';
    
    my $object_file = $self->compile_source_file({
      source_file => $src_file,
      output_file => $object_file_name,
      config => $config_exe,
      category => 'spvm_core',
    });
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub compile_precompile_class {
  my ($self, $class_name) = @_;
  
  my $config_exe = $self->config;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  
  $config->category('precompile');
  
  $config->config_exe($config_exe);
  
  my $runtime = $self->runtime;
  
  my $object_files = [];
  my $precompile_object_files = $builder_cc->compile_class(
    $class_name,
    {
      runtime => $runtime,
      config => $config,
    }
  );
  push @$object_files, @$precompile_object_files;
  
  return $object_files;
}

sub compile_native_class {
  my ($self, $class_name) = @_;
  
  my $config_exe = $self->config;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  # Compiler for native class
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $all_object_files = [];
  
  my $runtime = $self->runtime;
  
  my $script_name = $self->script_name;
  my $config_file;
  if ($class_name eq $self->class_name) {
    $config_file = $script_name;
    $config_file =~ s/\..*$//;
    $config_file .= '.config';
  }
  else {
    $config_file = SPVM::Builder::Util::search_config_file($class_name);
  }
  
  if (defined $config_file && -f $config_file) {
    
    my $mode;
    if ($class_name eq $self->class_name) {
      $mode = $self->{mode};
    }
    
    my $config = SPVM::Builder::Config->load_mode_config($config_file, $mode, []);
    
    $config->config_exe($config_exe);
    
    my $object_files = $builder_cc->compile_class(
      $class_name,
      {
        runtime => $runtime,
        config => $config,
      }
    );
    push @$all_object_files, @$object_files;
  }
  
  return $all_object_files;
}

sub get_user_defined_basic_type_names {
  my ($self) = @_;
  
  my $runtime = $self->runtime;
  
  my $category = [
    4, # SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM
    6, # SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS,
    7, # SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE,
  ];
  
  # Classes for anon methods are contained in another class.
  my $basic_types = [grep { $_->get_name !~ /::anon_method::/ } @{$runtime->get_basic_types({category => $category})}];
  
  my $class_names = [map { $_->get_name } @$basic_types];
  
  return $class_names;
}

sub parse_option_values_native_class {
  my ($class, $option_name, $option_values, $value_is_array) = @_;
  
  my $hash = {};
  for my $option_value (@$option_values) {
    
    if ($option_value =~ /^([\w:]+)\@(.+)/) {
      my $class_name = $1;
      
      my $value = $2;
      
      if ($value_is_array) {
       # warn $class_name;
       
       $hash->{$class_name} //= [];
        push @{$hash->{$class_name}}, $value;
      }
      else {
        $hash->{$class_name} = $value;
      }
    }
    else {
      confess "Invalid option value \"$option_value\" for $option_name option.";
    }
  }
  
  return $hash;
}

1;

=head1 Name

SPVM::Builder::Exe - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
