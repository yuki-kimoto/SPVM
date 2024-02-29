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

use SPVM 'Native::Compiler';

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

sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->builder->include_dirs($_[0]);
    return $self;
  }
  else {
    return $self->builder->include_dirs;
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

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  # Target class name
  my $class_name = $self->{class_name};
  unless (defined $class_name) {
    confess "A class name not specified";
  }
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    $output_file = $class_name;
    $output_file =~ s/::/__/g;
    $self->{output_file} = $output_file;
  }
  
  # Build directory
  my $build_dir = delete $self->{build_dir};
  
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  # Class paths
  my $include_dirs = delete $self->{include_dirs};
  unless (defined $include_dirs) {
    $include_dirs = [];
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
    include_dirs => $include_dirs
  );
  
  # Config file
  my $allow_no_config_file = $self->{allow_no_config_file};
  
  my $mode = $self->{mode};
  
  # Config
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $config;
  if (defined $config_file) {
    $config = SPVM::Builder::Config::Exe->load_mode_config($config_file, $mode);
  }
  else {
    if ($allow_no_config_file) {
      $config = SPVM::Builder::Config::Exe->new(file_optional => 1);
    }
    else {
      unless (defined $config_file) {
        my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
        confess "A config file \"$config_rel_file\" is not found in (@INC).";
      }
    }
  }
  
  unless ($config->output_type eq 'exe') {
    confess "Config file \"$config_file\" is not the config to create the executable file";
  }
  
  $config->class_name($class_name);
  
  $self->{config} = $config;
  
  $self->{builder} = $builder;
  
  my $compiler = SPVM::Native::Compiler->new;
  $compiler->add_include_dir($_) for @{$builder->include_dirs};
  $self->{compiler} = $compiler;
  
  my $optimize = $self->{optimize};
  if (defined $optimize) {
    $config->set_global_optimize($optimize);
  }
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $class_name = $self->{class_name};
  
  # Build runtime
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $class = $self->runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $class->_get_class_file;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Object files
  my $object_files = [];
  
  # Compile SPVM core source files
  my $spvm_core_object_files = $self->compile_spvm_core_source_files;
  push @$object_files, @$spvm_core_object_files;
  
  my $classes_object_files = $self->compile_classes;
  push @$object_files, @$classes_object_files;
  
  # Create bootstrap C source
  $self->create_bootstrap_source;
  
  # Compile bootstrap C source
  my $bootstrap_object_file = $self->compile_bootstrap_source_file;
  push @$object_files, $bootstrap_object_file;
  
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

sub get_required_resources {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $required_resources = [];
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $runtime = $self->runtime;
  
  my $class_names = $runtime->_get_user_defined_basic_type_names->to_strings;
  my $all_object_files = [];
  for my $class_name (@$class_names) {
    
    my $class = $runtime->get_basic_type_by_name($class_name);
    
    my $native_method_names = $class->_get_native_method_names;
    if (@$native_method_names) {
      my $class_file = $class->_get_class_file;
      
      unless (defined $class_file) {
        my $config_exe_file = SPVM::Builder::Util::search_config_file($class_name);
        if ($config_exe_file) {
          $class_file = $config_exe_file;
          $class_file =~ s/\.config$/\.spvm/;
        }
        else {
          confess "The class file \"$class_file\" is not found";
        }
      }
      
      my $config_file = SPVM::Builder::Util::search_config_file($class_name);
      
      unless ($class_name eq $self->class_name) {
        
        my $config_exe = SPVM::Builder::Config->load_config($config_file);
        
        my $resource_names = $config_exe->get_resource_names;
        for my $resource_name (@$resource_names) {
          my $resource = $config_exe->get_resource($resource_name);
          
          my $resource_info = {
            class_name => $class_name,
            resource => $resource
          };
          
          push @$required_resources, $resource_info;
        }
      }
    }
  }
  
  return $required_resources;
}

sub get_required_resource_json_lines {
  my ($self) = @_;
  
  my $required_resources = $self->get_required_resources;
  
  my @json_lines;
  for my $required_resource (@$required_resources) {
    my $class_name = $required_resource->{class_name};
    my $resource = $required_resource->{resource};
    my $resource_class_name = $resource->class_name;
    my $resource_mode = $resource->mode;
    my $resource_argv = $resource->argv || [];
    
    my $line = {
      resource_loader_class_name => "$class_name",
      class_name => $resource_class_name,
    };
    
    if (defined $resource_mode) {
      $line->{mode} = $resource_mode;
    }
    
    if (@$resource_argv) {
      $line->{argv} = $resource_argv;
    }
    
    my $json_line = JSON::PP->new->utf8->canonical(1)->encode($line);
    
    push @json_lines, $json_line;
  }
  
  return \@json_lines;
}

sub compile {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;
  
  my $class_name = $self->{class_name};
  
  my $compiler = $self->compiler;
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  eval { $compiler->compile($class_name) };
  
  if ($@) {
    my $error_messages = $compiler->get_error_messages;
    for my $error_message (@$error_messages) {
      print STDERR "$error_message\n";
    }
    exit(255);
  }
  my $runtime = $compiler->get_runtime;
  
  $self->runtime($runtime);
  
  $self->{finish_compile} = 1;
}

sub compile_classes {
  my ($self) = @_;
  
  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;
  
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

  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;
  
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
    my $precompile_method_names = $class->_get_precompile_method_names;
    for my $method_name (@$precompile_method_names) {
      my $method_cname = $class_name;
      $method_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVMPRECOMPILE__${method_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
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
    my $native_method_names = $class->_get_native_method_names;
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

  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;

  my $source = '';

  $source .= <<"EOS";

int32_t main(int32_t command_args_length, const char *command_args[]) {
  
  SPVM_ENV* env_api = SPVM_NATIVE_new_env();
  
  void* compiler = env_api->api->compiler->new_instance();
  
  void* runtime = SPVM_BOOTSTRAP_get_runtime(env_api, compiler);
  
  SPVM_ENV* env = env_api->new_env();
  
  env->runtime = runtime;
  
  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(env->runtime);
  
  SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(env);
  
  SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(env);
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  int32_t error_id = 0;
  
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
    
    // Set command info
    {
      error_id = env->set_command_info_program_name(env, stack, obj_program_name);
      
      if (error_id) {
        env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
      }
      else {
        error_id = env->set_command_info_argv(env, stack, obj_argv);
        
        if (error_id) {
          env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        }
        else {
          error_id = env->set_command_info_base_time(env, stack, base_time);
          if (error_id) {
            env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
          }
        }
      }
    }
    
    env->leave_scope(env, stack, mortal_stack_top);
  }
  
  if (!error_id) {
    const char* class_name = "$class_name";
    
    error_id = env->check_bootstrap_method(env, stack, class_name);
    
    if (error_id) {
      env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
    }
    else {
      error_id = env->call_init_methods(env, stack);
      if (!error_id) {
        void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
        void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, "main");
        
        int32_t args_width = 0;
        error_id = env->call_method(env, stack, method, args_width);
        if (error_id) {
          env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
        }
      }
    }
  }
  
  if (error_id) {
    env->print_stderr(env, stack, env->get_exception(env, stack));
    fprintf(spvm_stderr, "\\n");
  }
  
  env->destroy_class_vars(env, stack);
  
  env->free_stack(env, stack);
  
  env->free_env(env);
  
  env_api->api->compiler->free_instance(compiler);
  
  env_api->free_env(env_api);
  
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
  
  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;
  
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

  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;

  my $source = '';

  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $method_cname = $class_name;
    $method_cname =~ s/::/__/g;
    
    my $precompile_method_names = $class->_get_precompile_method_names;
    
    for my $precompile_method_name (@$precompile_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_precompile_method_address(env, "$class_name", "$precompile_method_name", &SPVMPRECOMPILE__${method_cname}__$precompile_method_name);
EOS
    }
  }

  $source .= "}\n";
  
  return $source;
}

sub create_bootstrap_set_native_method_addresses_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;

  my $source = '';

  $source .= "static void SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $method_cname = $class_name;
    $method_cname =~ s/::/__/g;
    
    my $native_method_names = $class->_get_native_method_names;
    
    for my $native_method_name (@$native_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_native_method_address(env, "$class_name", "$native_method_name", &SPVM__${method_cname}__$native_method_name);
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
  
  my $class_names = $self->runtime->_get_user_defined_basic_type_names->to_strings;
  
  my $class_files = [];
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    if ($class->get_class_dir) {
      my $class_file = $class->_get_class_file;
      push @$class_files, $class_file;
    }
  }
  
  # Source file - Output
  my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
  my $target_perl_class_name = "SPVM::$class_name";
  my $bootstrap_base = $target_perl_class_name;
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
  
  if (defined $config_exe->file) {
    $bootstrap_source .= "\n// " . $config_exe->file;
  }
  
  my $bootstrap_source_original;
  if (-f $bootstrap_source_file) {
    $bootstrap_source_original = SPVM::Builder::Util::slurp_binary($bootstrap_source_file);
  }
  
  my $force = $self->force || $config_exe->force;
  
  if (defined $bootstrap_source_original && $bootstrap_source ne $bootstrap_source_original) {
    $force = 1;
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

sub compile_bootstrap_source_file {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  # Target class name
  my $class_name = $self->class_name;
  
  my $target_perl_class_name = "SPVM::$class_name";
  
  # Compile source files
  my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($target_perl_class_name);
  my $object_file_name = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir, "$class_name_rel_file.boot.o");
  my $source_file = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir, "$class_name_rel_file.boot.c");
  
  my $config = $config_exe->config_bootstrap;
  unless ($config) {
    confess "The config_bootstrap field in the SPVM::Builder::Config class must be defined";
  }
  
  # Compile
  my $object_file = $self->compile_source_file({
    source_file => $source_file,
    output_file => $object_file_name,
    config => $config,
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
  
  # Config
  my $config = $config_exe->config_spvm_core;
  unless ($config) {
    confess "The config_spvm_core field in the SPVM::Builder::Config class must be defined";
  }
  
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
      config => $config,
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
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  if (defined $config_file) {
    
    my $mode;
    if ($class_name eq $self->class_name) {
      $mode = $self->{mode};
    }
    
    my $config = SPVM::Builder::Config->load_mode_config($config_file, $mode);
    
    # In an executable file, only resources used in the config of the class for generate an executable file are compiled.
    unless ($class_name eq $self->class_name) {
      $config->no_compile_resource(1);
    }
    
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

1;

=head1 Name

SPVM::Builder::Exe - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
