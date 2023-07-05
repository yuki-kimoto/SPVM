package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp 'confess';
use Pod::Usage 'pod2usage';
use Config;

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config::Exe;
use SPVM::Builder::Runtime;
use JSON::PP;

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

sub module_name {
  my $self = shift;
  if (@_) {
    $self->{module_name} = $_[0];
    return $self;
  }
  else {
    return $self->{module_name};
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

# Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  # Target module name
  my $module_name = $self->{module_name};
  unless (defined $module_name) {
    confess "A module name not specified";
  }
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    $output_file = $module_name;
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
  my $config_file = $self->{config_file};
  
  # Config
  my $config;
  if (defined $config_file) {
    $config = SPVM::Builder::Config::Exe->load_config($config_file);
    unless ($config->output_type eq 'exe') {
      confess "Config file \"$config_file\" is not the config to create the executable file";
    }
  }
  else {
    $config = SPVM::Builder::Config::Exe->new_c99(file_optional => 1);
  }
  $config->module_name($module_name);
  
  $self->{config} = $config;
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Module name
  my $module_name = $self->{module_name};
  
  # Build runtime
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  # Config file
  my $module_file = $self->runtime->get_module_file($module_name);

  # Object files
  my $object_files = [];

  # Compile SPVM core source files
  my $spvm_core_object_files = $self->compile_spvm_core_source_files;
  push @$object_files, @$spvm_core_object_files;
  
  my $modules_object_files = $self->compile_modules;
  push @$object_files, @$modules_object_files;
  
  # Create bootstrap C source
  $self->create_bootstrap_source;

  # Compile bootstrap C source
  my $bootstrap_object_file = $self->compile_bootstrap_source_file;
  push @$object_files, $bootstrap_object_file;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Link and generate executable file
  my $config_exe = $self->config;
  my $cc_linker = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  my $options = {
    output_file => $self->{output_file},
    config => $self->config,
    category => 'native',
  };

  $cc_linker->link($module_name, $object_files, $options);
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
  
  # Compiler for native module
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $module_names = $self->get_module_names;
  my $all_object_files = [];
  for my $module_name (@$module_names) {

    my $perl_module_name = "SPVM::$module_name";
    
    my $native_method_names = $self->runtime->get_method_names($module_name, 'native');
    if (@$native_method_names) {
      my $native_module_file = $self->runtime->get_module_file($module_name);
      my $native_dir = $native_module_file;
      
      $native_dir =~ s/\.spvm$//;
      $native_dir .= 'native';
      my $input_dir = SPVM::Builder::Util::remove_module_name_part_from_file($native_module_file, $perl_module_name);
      my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
      mkpath $build_object_dir;

      # Class file
      my $module_file = $self->runtime->get_module_file($module_name);
      unless (defined $module_file) {
        my $config_exe_file = SPVM::Builder::Util::get_config_file_from_module_name($module_name);
        if ($config_exe_file) {
          $module_file = $config_exe_file;
          $module_file =~ s/\.config$/\.spvm/;
        }
        else {
          confess "The module file \"$module_file\" is not found";
        }
      }
      my $config_exe = $builder->create_native_config_from_module_file($module_file);
      
      my $resource_names = $config_exe->get_resource_names;
      for my $resource_name (@$resource_names) {
        my $resource = $config_exe->get_resource($resource_name);
        
        my $resource_info = {
          module_name => $module_name,
          resource => $resource
        };
        
        push @$required_resources, $resource_info;
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
    my $module_name = $required_resource->{module_name};
    my $resource = $required_resource->{resource};
    my $resource_module_name = $resource->module_name;
    my $resource_mode = $resource->mode;
    my $resource_argv = $resource->argv || [];
    
    my $line = {
      caller_module_name => "$module_name",
      resource => {
        module_name => $resource_module_name,
      }
    };
    if (defined $resource_mode) {
      $line->{resource}{mode} = $resource_mode;
    }
    
    if (@$resource_argv) {
      $line->{resource}{argv} = $resource_argv;
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
  
  # Module name
  my $module_name = $self->{module_name};
  
  # Compile SPVM
  my $compiler = SPVM::Builder::Compiler->new(
    include_dirs => $builder->include_dirs
  );
  my $success = $compiler->compile($module_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->build_runtime;
  $self->runtime($runtime);
  
  $self->{finish_compile} = 1;
}

sub compile_modules {
  my ($self) = @_;

  my $module_names = $self->get_module_names;
  
  my $object_files = [];
  for my $module_name (@$module_names) {
    my $precompile_object_files = $self->compile_module_precompile_source_file($module_name);
    push @$object_files, @$precompile_object_files;
    
    my $native_object_files = $self->compile_module_native_source_files($module_name);
    push @$object_files, @$native_object_files;
  }
  
  return $object_files;
}

sub create_source_file {
  my ($self, $options) = @_;
  
  # Config
  my $config_exe = $self->config;
  
  my $input_files = $options->{input_files};
  my $output_file = $options->{output_file};
  my $create_cb = $options->{create_cb};
  
  my $config_exe_loaded_config_files = $config_exe->get_loaded_config_files;
  my $need_generate_input_files = [@$input_files, @$config_exe_loaded_config_files];
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config_exe->force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });
  
  if ($need_generate) {
    $create_cb->();
  }
}

sub compile_source_file {
  my ($self, $options) = @_;
  
  my $source_file = $options->{source_file};
  my $output_file = $options->{output_file};
  my $config = $options->{config};
  my $config_exe = $self->config;
  
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
  
  my $before_each_compile_cbs = $config_exe->before_each_compile_cbs;
  $config->add_before_compile_cb(@$before_each_compile_cbs);
  
  my $compile_info = SPVM::Builder::CompileInfo->new(
    output_file => $output_file,
    source_file => $source_file,
    config => $config,
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

  # Module name
  my $module_name = $self->module_name;

  # Module names
  my $module_names = $self->get_module_names;
  
  my $source = '';
  
  $source .= <<'EOS';

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include <assert.h>

// Only used for _setmode function and _O_BINARY
#include <fcntl.h>

#include "spvm_native.h"

EOS
  
  $source .= "// precompile functions declaration\n";
  for my $module_name (@$module_names) {
    my $precompile_method_names = $self->runtime->get_method_names($module_name, 'precompile');
    for my $method_name (@$precompile_method_names) {
      my $method_cname = $module_name;
      $method_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVMPRECOMPILE__${method_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env);\n";

  $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_set_precompile_method_address(SPVM_ENV* env, const char* module_name, const char* method_name, void* precompile_address) {
void* module_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, module_name);
void* method = env->api->runtime->get_method_by_name(env->runtime, module_basic_type, method_name);
env->api->runtime->set_precompile_method_address(env->runtime, method, precompile_address);
}
EOS
  
  $source .= "// native functions declaration\n";
  for my $method_cname (@$module_names) {
    my $native_method_names = $self->runtime->get_method_names($method_cname, 'native');
    for my $method_name (@$native_method_names) {
      my $method_cname = $method_cname;
      $method_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVM__${method_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env);\n\n";

  $source .= "static int32_t* SPVM_BOOTSTRAP_get_runtime_codes();\n\n";

  $source .= "static void* SPVM_BOOTSTRAP_build_runtime(SPVM_ENV* env, void* compiler);\n\n";

  $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_set_native_method_address(SPVM_ENV* env, const char* module_name, const char* method_name, void* native_address) {
  void* module_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, module_name);
  void* method = env->api->runtime->get_method_by_name(env->runtime, module_basic_type, method_name);
  env->api->runtime->set_native_method_address(env->runtime, method, native_address);
}
EOS

  return $source;
}

sub create_bootstrap_main_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  # Module name
  my $module_name = $self->module_name;

  # Module names
  my $module_names = $self->get_module_names;

  my $source = '';

  $source .= <<"EOS";

int32_t main(int32_t command_args_length, const char *command_args[]) {

  // Binary mode in all systems
#ifdef _WIN32
  _setmode(fileno(stdout), _O_BINARY);
  _setmode(fileno(stderr), _O_BINARY);
  _setmode(fileno(stdin), _O_BINARY);
#endif
  
  SPVM_ENV* env = SPVM_NATIVE_new_env_prepared();
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  int32_t error = 0;
  
  // Set the program name and the command line arguments
  {
    // Enter scope
    int32_t scope_id = env->enter_scope(env, stack);
    
    // Program name - string
    void* obj_program_name = env->new_string(env, stack, command_args[0], strlen(command_args[0]));
    
    // ARGV - string[]
    void* obj_argv = env->new_string_array(env, stack, command_args_length - 1);
    for (int32_t arg_index = 1; arg_index < command_args_length; arg_index++) {
      void* obj_arg = env->new_string(env, stack, command_args[arg_index], strlen(command_args[arg_index]));
      env->set_elem_object(env, stack, obj_argv, arg_index - 1, obj_arg);
    }
    
    // Base time
    int64_t base_time = time(NULL);
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_program_name(env, stack, obj_program_name);
      assert(e == 0);
      e = env->set_command_info_argv(env, stack, obj_argv);
      assert(e == 0);
      e = env->set_command_info_base_time(env, stack, base_time);
      assert(e == 0);
    }
    // Leave scope
    env->leave_scope(env, stack, scope_id);
    
  }
  
  // Call INIT blocks
  
  int32_t status = 0;
  error = env->call_init_blocks(env, stack);
  if (error) {
    env->print_stderr(env, stack, env->get_exception(env, stack));
    printf("\\n");
    status = 255;
  }
  else {
    
    // Module name
    const char* module_name = "$module_name";
    
    // Class
    void* module_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, module_name);
    void* method = env->api->runtime->get_method_by_name(env->runtime, module_basic_type, "main");
    
    if (!method) {
      fprintf(stderr, "The class method %s->main is not defined\\n", module_name);
      return -1;
    }
    
    // Run
    int32_t items = 0;
    error = env->call_method(env, stack, method, items);
    
    if (error) {
      env->print_stderr(env, stack, env->get_exception(env, stack));
      printf("\\n");
      status = 255;
    }
    else {
      status = stack[0].ival;
    }
  }
  
  // Cleanup global vars
  env->cleanup_global_vars(env, stack);
  
  // Free stack
  env->free_stack(env, stack);
  
  // Free env
  env->free_env_prepared(env);
  
  return status;
}
EOS

  return $source;
}

sub create_bootstrap_get_runtime_codes_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  my $runtime_codes = SPVM::Builder::Runtime->get_runtime_codes($self->runtime);
  my $runtime_codes_length = @$runtime_codes;
  my $source = '';
  
  my $runtime_codes_str = join(",", @$runtime_codes);

  $source .= "static int32_t SPVM_BOOTSTRAP_runtime_codes[$runtime_codes_length] = {$runtime_codes_str};\n";

  $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_get_runtime_codes() {
  return SPVM_BOOTSTRAP_runtime_codes;
}
EOS
  
  return $source;
}

sub create_bootstrap_build_runtime_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $source = '';
  
  $source .= <<"EOS";
static void* SPVM_BOOTSTRAP_build_runtime(SPVM_ENV* env, void* compiler) {
  return NULL;
}
EOS
  
  return $source;
}

sub create_bootstrap_new_env_prepared_func_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Module name
  my $module_name = $self->module_name;
  
  # Module names
  my $module_names = $self->get_module_names;
  
  my $source = '';
  
  my $set_precompile_method_addresses_source = '';
  
  my $config_exe = $self->config;
  $set_precompile_method_addresses_source = "SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(env);";
  $source .= <<"EOS";
SPVM_ENV* SPVM_NATIVE_new_env_prepared() {
EOS

  $source .= <<"EOS";
  
  // Create env
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();
  
  // Compiler
  void* compiler = env->api->compiler->new_instance();
  
  void* new_runtime = SPVM_BOOTSTRAP_build_runtime(env, compiler);
  
  // New runtime
  void* runtime = env->api->runtime->new_instance();
  
  // Create SPVM 32bit codes
  int32_t* runtime_codes = SPVM_BOOTSTRAP_get_runtime_codes();
  
  // Build runtime
  env->api->runtime->build(runtime, runtime_codes);
  
  // Set runtime
  env->runtime = runtime;
  
  // Free compiler
  env->api->compiler->free_instance(compiler);
  
  // Set precompile method addresses
  $set_precompile_method_addresses_source
  
  // Set native method addresses
  SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(env);
  
  return env;
}
EOS
  
  return $source;
}

sub create_bootstrap_set_precompile_method_addresses_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  # Module names
  my $module_names = $self->get_module_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env){\n";

  for my $module_name (@$module_names) {
    my $method_cname = $module_name;
    $method_cname =~ s/::/__/g;
    
    my $precompile_method_names = $self->runtime->get_method_names($module_name, 'precompile');
    
    for my $precompile_method_name (@$precompile_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_precompile_method_address(env, "$module_name", "$precompile_method_name", &SPVMPRECOMPILE__${method_cname}__$precompile_method_name);
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

  # Module names
  my $module_names = $self->get_module_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env){\n";

  for my $module_name (@$module_names) {
    my $method_cname = $module_name;
    $method_cname =~ s/::/__/g;
    
    my $native_method_names = $self->runtime->get_method_names($module_name, 'native');
    
    for my $native_method_name (@$native_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_native_method_address(env, "$module_name", "$native_method_name", &SPVM__${method_cname}__$native_method_name);
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
  
  # Module name
  my $module_name = $self->module_name;
  
  # Module names
  my $module_names = $self->get_module_names;
  
  # Class files - Input
  my $module_files = [];
  for my $module_name (@$module_names) {
    my $module_file = $self->runtime->get_module_file($module_name);
    push @$module_files, $module_file;
  }
  
  # Source file - Output
  my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
  my $target_perl_module_name = "SPVM::$module_name";
  my $bootstrap_base = $target_perl_module_name;
  $bootstrap_base =~ s|::|/|g;
  my $bootstrap_source_file = "$build_src_dir/$bootstrap_base.boot.c";
  
  # Source creating callback
  my $create_cb = sub {
    
    my $bootstrap_source = '';
    
    # Header
    $bootstrap_source .= $self->create_bootstrap_header_source;
    
    # main function
    $bootstrap_source .= $self->create_bootstrap_main_func_source;

    # SPVM_NATIVE_new_env_prepared function
    $bootstrap_source .= $self->create_bootstrap_new_env_prepared_func_source;

    # Set precompile method addresses function
    my $config_exe = $self->config;
    $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;

    # Set native method addresses function
    $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;

    # get_runtime_codes function
    $bootstrap_source .= $self->create_bootstrap_get_runtime_codes_func_source;

    # get_runtime_codes function
    $bootstrap_source .= $self->create_bootstrap_build_runtime_source;

    # Build source directory
    my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
    mkpath $build_src_dir;
    mkpath dirname $bootstrap_source_file;
    
    open my $bootstrap_source_fh, '>', $bootstrap_source_file
      or die "Can't open file $bootstrap_source_file:$!";

    print $bootstrap_source_fh $bootstrap_source;
  };
  
  # Create source file
  $self->create_source_file({
    input_files => [@$module_files, __FILE__],
    output_file => $bootstrap_source_file,
    create_cb => $create_cb,
  });
}

sub compile_bootstrap_source_file {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  # Target module name
  my $module_name = $self->module_name;
  
  my $target_perl_module_name = "SPVM::$module_name";
  
  # Compile source files
  my $module_name_rel_file = SPVM::Builder::Util::convert_module_name_to_rel_file($target_perl_module_name);
  my $object_file_name = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir, "$module_name_rel_file.boot.o");
  my $source_file = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir, "$module_name_rel_file.boot.c");
  
  # Create directory for object file output
  mkdir dirname $object_file_name;
  
  my $config = $config_exe->config_bootstrap;
  unless ($config) {
    confess "The config_bootstrap field in the SPVM::Builder::Config class must be defined";
  }
  
  # Compile
  my $object_file = $self->compile_source_file({
    source_file => $source_file,
    output_file => $object_file_name,
    config => $config,
  });
  
  return $object_file;
}

sub compile_spvm_core_source_files {
  my ($self) = @_;
  
  # Config
  my $config_exe = $self->config;
  
  my $builder_dir = SPVM::Builder::Util::get_builder_dir_from_config_class();
  
  # SPVM src directory
  my $builder_src_dir = "$builder_dir/src";
  
  # SPVM runtime source files
  my $spvm_runtime_src_base_names;
  $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  my @spvm_core_source_files = map { "$builder_src_dir/$_" } @$spvm_runtime_src_base_names;
  
  # Object dir
  my $output_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
  mkpath $output_dir;
  
  # Config
  my $config = $config_exe->config_spvm_core;
  unless ($config) {
    confess "The config_spvm_core field in the SPVM::Builder::Config module must be defined";
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
    });
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub compile_module_precompile_source_file {
  my ($self, $module_name) = @_;

  my $config_exe = $self->config;
  
  # Builer
  my $builder = $self->builder;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Build precompile modules
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $object_files = [];
  my $precompile_method_names = $self->runtime->get_method_names($module_name, 'precompile');
  if (@$precompile_method_names) {
    my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
    mkpath $build_src_dir;
    
    my $module_file = $self->runtime->get_module_file($module_name);
    my $precompile_source = $self->runtime->build_precompile_module_source($module_name);
    
    $builder_cc->build_precompile_module_source_file(
      $module_name,
      {
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        module_file => $module_file,
      }
    );
    
    my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
    mkpath $build_object_dir;
    
    my $config = SPVM::Builder::Util::API::create_default_config();
    my $before_each_compile_cbs = $config_exe->before_each_compile_cbs;
    $config->add_before_compile_cb(@$before_each_compile_cbs);
    my $precompile_object_files = $builder_cc->compile_source_files(
      $module_name,
      {
        input_dir => $build_src_dir,
        output_dir => $build_object_dir,
        config => $config,
        category => 'precompile',
      }
    );
    push @$object_files, @$precompile_object_files;
  }
  
  return $object_files;
}

sub compile_module_native_source_files {
  my ($self, $module_name) = @_;

  my $config_exe = $self->config;
  
  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Compiler for native module
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $all_object_files = [];
  
  my $perl_module_name = "SPVM::$module_name";
  
  my $native_method_names = $self->runtime->get_method_names($module_name, 'native');
  if (@$native_method_names) {
    my $native_module_file = $self->runtime->get_module_file($module_name);
    my $native_dir = $native_module_file;
    
    $native_dir =~ s/\.spvm$//;
    $native_dir .= 'native';
    my $input_dir = SPVM::Builder::Util::remove_module_name_part_from_file($native_module_file, $perl_module_name);
    my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
    mkpath $build_object_dir;

    # Class file
    my $module_file = $self->runtime->get_module_file($module_name);
    unless (defined $module_file) {
      my $config_file = SPVM::Builder::Util::get_config_file_from_module_name($module_name);
      if ($config_file) {
        $module_file = $config_file;
        $module_file =~ s/\.config$/\.spvm/;
      }
      else {
        confess "The module file \"$module_file\" is not loaded";
      }
    }
    my $config = $builder->create_native_config_from_module_file($module_file);
    my $before_each_compile_cbs = $config_exe->before_each_compile_cbs;
    $config->add_before_compile_cb(@$before_each_compile_cbs);
    
    my $resource_include_dirs = [];
    my $config_exe = $self->config;
    my $resource_names = $config_exe->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $config_exe->get_resource($resource_name);
      my $resource_include_dir = $resource->config->native_include_dir;
      push @$resource_include_dirs, $resource_include_dir;
    }
    $config->add_include_dir(@$resource_include_dirs);
    
    $config->disable_resource(1);
    my $object_files = $builder_cc->compile_source_files(
      $module_name,
      {
        input_dir => $input_dir,
        output_dir => $build_object_dir,
        config => $config,
        category => 'native',
      }
    );
    push @$all_object_files, @$object_files;
  }
  
  return $all_object_files;
}

sub get_module_names {
  my ($self) = @_;
  
  my $basic_type_names = $self->runtime->get_basic_type_names;
  
  my $module_names = [grep { /^[A-Z]/ && $_ !~ /::anon::/ } @$basic_type_names];
  
  return $module_names;
}

1;

=head1 Name

SPVM::Builder::Exe - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
