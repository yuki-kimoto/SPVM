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
    $config = SPVM::Builder::Config::Exe->load_config($config_file);
    unless ($config->output_type eq 'exe') {
      confess "Config file \"$config_file\" is not the config to create the executable file";
    }
  }
  else {
    $config = SPVM::Builder::Config::Exe->new_c99(file_optional => 1);
  }
  $self->{config} = $config;
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Class name
  my $class_name = $self->{class_name};
  
  # Build runtime
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  # Config file
  my $module_file = $self->runtime->get_module_file($class_name);

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

  $cc_linker->link($class_name, $object_files, $options);
}

sub get_dependent_resources {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $dependent_resources = [];
  
  my $builder = $self->builder;

  my $build_dir = $self->builder->build_dir;
  
  # Compiler for native module
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $class_names = $self->runtime->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  my $all_object_files = [];
  for my $class_name (@$class_names_without_anon) {

    my $perl_class_name = "SPVM::$class_name";
    
    my $native_method_names = $self->runtime->get_method_names($class_name, 'native');
    if (@$native_method_names) {
      my $native_module_file = $self->runtime->get_module_file($class_name);
      my $native_dir = $native_module_file;
      
      $native_dir =~ s/\.spvm$//;
      $native_dir .= 'native';
      my $input_dir = SPVM::Builder::Util::remove_class_part_from_file($native_module_file, $perl_class_name);
      my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
      mkpath $build_object_dir;

      # Module file
      my $module_file = $self->runtime->get_module_file($class_name);
      unless (defined $module_file) {
        my $config_exe_file = SPVM::Builder::Util::get_config_file_from_class_name($class_name);
        if ($config_exe_file) {
          $module_file = $config_exe_file;
          $module_file =~ s/\.config$/\.spvm/;
        }
        else {
          confess "\"$module_file\" module is not loaded";
        }
      }
      my $config_exe = $builder_cc->create_native_config_from_module_file($module_file);
      
      my $resource_names = $config_exe->get_resource_names;
      for my $resource_name (@$resource_names) {
        my $resource = $config_exe->get_resource($resource_name);
        
        my $resource_info = {
          class_name => $class_name,
          resource => $resource
        };
        
        push @$dependent_resources, $resource_info;
      }
    }
  }
  
  return $dependent_resources;
}

sub get_dependent_resource_lines {
  my ($self) = @_;
  
  my $dependent_resources = $self->get_dependent_resources;
  
  my @lines;
  for my $dependent_resource (@$dependent_resources) {
    my $class_name = $dependent_resource->{class_name};
    my $resource = $dependent_resource->{resource};
    my $resource_class_name = $resource->class_name;
    my $resource_mode = $resource->mode;
    my $resource_args = $resource->args || [];
    
    my $line = qq({class_name:"$class_name",resource_class_name:"$resource_class_name",resource_mode:);
    if (defined $resource_mode) {
      $line .= qq("$resource_mode");
    }
    else {
      $line .= 'undefined';
    }
    $line .= ",resource_args:[";
    
    $line .= join(",", map { qq("$_") } @$resource_args);
    
    $line .= "]}";
    
    push @lines, $line;
  }
  
  return \@lines;
}

sub compile {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;
  
  # Class name
  my $class_name = $self->{class_name};
  
  # Compile SPVM
  my $compiler = SPVM::Builder::Compiler->new(
    module_dirs => $builder->module_dirs
  );
  my $success = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->build_runtime;
  $self->runtime($runtime);
  
  $self->{finish_compile} = 1;
}

sub compile_classes {
  my ($self) = @_;

  my $class_names = $self->runtime->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  
  my $object_files = [];
  for my $class_name (@$class_names_without_anon) {
    my $precompile_object_files = $self->compile_class_precompile_source_file($class_name);
    push @$object_files, @$precompile_object_files;
    
    my $native_object_files = $self->compile_class_native_source_files($class_name);
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
    before_each_compile_cbs => $config_exe->before_each_compile_cbs,
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  my $compile_info = $builder_cc->create_compile_command_info({
    config => $config,
    output_file => $output_file,
    source_file => $source_file
  });
  
  if ($need_generate) {
    $builder_cc->compile_source_file($compile_info);
  }
  
  my $object_file_info = SPVM::Builder::ObjectFileInfo->new(
    compile_info => $compile_info,
  );
  
  return $object_file_info;
}

sub create_bootstrap_header_source {
  my ($self) = @_;

  # Config
  my $config_exe = $self->config;

  # Builder
  my $builder = $self->builder;

  # Class name
  my $class_name = $self->class_name;

  # Class names
  my $class_names = $self->runtime->get_class_names;
  
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];

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
  
  my $no_precompile = $config_exe->no_precompile;
  
  unless ($no_precompile) {
    $source .= "// precompile functions declaration\n";
    for my $class_name (@$class_names) {
      my $precompile_method_names = $self->runtime->get_method_names($class_name, 'precompile');
      for my $method_name (@$precompile_method_names) {
        my $class_cname = $class_name;
        $class_cname =~ s/::/__/g;
        $source .= <<"EOS";
int32_t SPVMPRECOMPILE__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
      }
    }

    $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env);\n";

    $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_set_precompile_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* precompile_address) {
  int32_t method_id = env->api->runtime->get_method_id_by_name(env->runtime, class_name, method_name);
  env->api->runtime->set_precompile_method_address(env->runtime, method_id, precompile_address);
}
EOS
  }
  
  $source .= "// native functions declaration\n";
  for my $class_cname (@$class_names_without_anon) {
    my $native_method_names = $self->runtime->get_method_names($class_cname, 'native');
    for my $method_name (@$native_method_names) {
      my $class_cname = $class_cname;
      $class_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVM__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env);\n";

  $source .= "static int32_t* SPVM_BOOTSTRAP_get_runtime_codes();\n";

  $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_set_native_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* native_address) {
  int32_t method_id = env->api->runtime->get_method_id_by_name(env->runtime, class_name, method_name);
  env->api->runtime->set_native_method_address(env->runtime, method_id, native_address);
}
EOS

  return $source;
}

sub create_bootstrap_main_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  # Class name
  my $class_name = $self->class_name;

  # Class names
  my $class_names = $self->runtime->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];

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
  
  // Set the program name and the command line arguments
  {
    SPVM_VALUE* my_stack = env->new_stack(env);
    
    // Enter scope
    int32_t scope_id = env->enter_scope(env, my_stack);
    
    // Program name - string
    void* obj_program_name = env->new_string(env, my_stack, command_args[0], strlen(command_args[0]));
    
    // ARGV - string[]
    void* obj_argv = env->new_object_array(env, my_stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, command_args_length - 1);
    for (int32_t arg_index = 1; arg_index < command_args_length; arg_index++) {
      void* obj_arg = env->new_string(env, my_stack, command_args[arg_index], strlen(command_args[arg_index]));
      env->set_elem_object(env, my_stack, obj_argv, arg_index - 1, obj_arg);
    }
    
    // Base time
    int64_t base_time = time(NULL);
    
    // Set command info
    {
      int32_t e;
      e = env->set_command_info_program_name(env, obj_program_name);
      assert(e == 0);
      e = env->set_command_info_argv(env, obj_argv);
      assert(e == 0);
      e = env->set_command_info_base_time(env, base_time);
      assert(e == 0);
    }
    // Leave scope
    env->leave_scope(env, my_stack, scope_id);
    
    env->free_stack(env, my_stack);
  }

  // Call INIT blocks
  env->call_init_blocks(env);
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  // Class name
  const char* class_name = "$class_name";
  
  // Class
  int32_t method_id = env->get_class_method_id(env, stack, class_name, "main");
  
  if (method_id < 0) {
    fprintf(stderr, "The class method %s->main is not defined\\n", class_name);
    return -1;
  }
  
  // Run
  int32_t args_stack_length = 0;
  int32_t error = env->call_method(env, stack, method_id, args_stack_length);
  
  int32_t status;
  if (error) {
    env->print_stderr(env, stack, env->get_exception(env, stack));
    printf("\\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }
  
  // Free stack
  env->free_stack(env, stack);
  
  // Cleanup global vars
  env->cleanup_global_vars(env);
  
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

sub create_bootstrap_new_env_prepared_func_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Class names
  my $class_names = $self->runtime->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  
  my $source = '';
  
  my $set_precompile_method_addresses_source = '';
  
  my $config_exe = $self->config;
  my $no_precompile = $config_exe->no_precompile;
  unless ($no_precompile) {
    $set_precompile_method_addresses_source = "SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(env);";
  }
  $source .= <<"EOS";
SPVM_ENV* SPVM_NATIVE_new_env_prepared() {
EOS

  $source .= <<"EOS";

  // Create env
  SPVM_ENV* env = SPVM_NATIVE_new_env_raw();

  // New runtime
  void* runtime = env->api->runtime->new_object(env);
  
  // Runtime allocator
  void* runtime_allocator = env->api->runtime->get_allocator(runtime);
  
  // Create SPVM 32bit codes
  int32_t* runtime_codes = SPVM_BOOTSTRAP_get_runtime_codes();
  
  // Build runtime
  env->api->runtime->build(runtime, runtime_codes);

  // Set runtime information
  env->runtime = runtime;

  // Initialize env
  env->init_env(env);

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

  # Class names
  my $class_names = $self->runtime->get_class_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $precompile_method_names = $self->runtime->get_method_names($class_name, 'precompile');
    
    for my $precompile_method_name (@$precompile_method_names) {
      $source .= <<"EOS";
  SPVM_BOOTSTRAP_set_precompile_method_address(env, "$class_name", "$precompile_method_name", &SPVMPRECOMPILE__${class_cname}__$precompile_method_name);
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

  # Class names
  my $class_names = $self->runtime->get_class_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $native_method_names = $self->runtime->get_method_names($class_name, 'native');
    
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
  
  # Class name
  my $class_name = $self->class_name;
  
  # Class names
  my $class_names = $self->runtime->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  
  # Module files - Input
  my $module_files = [];
  for my $class_name (@$class_names_without_anon) {
    my $module_file = $self->runtime->get_module_file($class_name);
    push @$module_files, $module_file;
  }
  
  # Source file - Output
  my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
  my $target_perl_class_name = "SPVM::$class_name";
  my $bootstrap_base = $target_perl_class_name;
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
    my $no_precompile = $config_exe->no_precompile;
    unless ($no_precompile) {
      $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;
    }

    # Set native method addresses function
    $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;

    # get_runtime_codes function
    $bootstrap_source .= $self->create_bootstrap_get_runtime_codes_func_source;

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
  
  # Target class name
  my $class_name = $self->class_name;
  
  my $target_perl_class_name = "SPVM::$class_name";
  
  # Compile source files
  my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($target_perl_class_name);
  my $object_file = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir, "$class_name_rel_file.boot.o");
  my $source_file = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir, "$class_name_rel_file.boot.c");
  
  # Create directory for object file output
  mkdir dirname $object_file;
  
  my $config = SPVM::Builder::Util::create_default_config();
  
  # Compile
  my $object_file_info = $self->compile_source_file({
    source_file => $source_file,
    output_file => $object_file,
    config => $config,
  });
  
  return $object_file_info;
}

sub compile_spvm_core_source_files {
  my ($self) = @_;
  
  # Config
  my $config_exe = $self->config;
  
  my $builder_dir = SPVM::Builder::Util::get_builder_dir_from_config_module();
  
  # SPVM src directory
  my $builder_src_dir = "$builder_dir/src";
  
  # SPVM runtime source files
  my $no_compiler_api = $config_exe->no_compiler_api;
  my $spvm_runtime_src_base_names;
  if ($no_compiler_api) {
    $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_common_source_file_names();
  }
  else {
    $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  }
  my @spvm_core_source_files = map { "$builder_src_dir/$_" } @$spvm_runtime_src_base_names;
  
  # Object dir
  my $output_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
  mkpath $output_dir;
  
  # Config
  my $config = SPVM::Builder::Util::create_default_config();
  if ($no_compiler_api) {
    $config->add_ccflag('-DSPVM_NO_COMPILER_API');
  }
  
  # Compile source files
  my $object_file_infos = [];
  for my $src_file (@spvm_core_source_files) {
    # Object file
    my $object_file = "$output_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    my $object_file_info = $self->compile_source_file({
      source_file => $src_file,
      output_file => $object_file,
      config => $config,
    });
    push @$object_file_infos, $object_file_info;
  }
  
  return $object_file_infos;
}

sub compile_class_precompile_source_file {
  my ($self, $class_name) = @_;

  my $config_exe = $self->config;
  
  my $no_precompile = $config_exe->no_precompile;
  
  return [] if $no_precompile;

  # Builer
  my $builder = $self->builder;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Build precompile classes
  my $builder_cc = SPVM::Builder::CC->new(
    before_each_compile_cbs => $config_exe->before_each_compile_cbs,
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $object_files = [];
  my $precompile_method_names = $self->runtime->get_method_names($class_name, 'precompile');
  if (@$precompile_method_names) {
    my $build_src_dir = SPVM::Builder::Util::create_build_src_path($self->builder->build_dir);
    mkpath $build_src_dir;
    
    my $module_file = $self->runtime->get_module_file($class_name);
    my $precompile_source = $self->runtime->build_precompile_class_source($class_name);
    
    $builder_cc->build_precompile_class_source_file(
      $class_name,
      {
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        module_file => $module_file,
      }
    );
    
    my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
    mkpath $build_object_dir;
    
    my $config_class = SPVM::Builder::Util::create_default_config();
    my $precompile_object_files = $builder_cc->compile_source_files(
      $class_name,
      {
        input_dir => $build_src_dir,
        output_dir => $build_object_dir,
        config => $config_class,
        category => 'precompile',
      }
    );
    push @$object_files, @$precompile_object_files;
  }
  
  return $object_files;
}

sub compile_class_native_source_files {
  my ($self, $class_name) = @_;

  my $config_exe = $self->config;
  
  my $builder = $self->builder;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  mkpath $build_dir;

  # Compiler for native module
  my $builder_cc = SPVM::Builder::CC->new(
    before_each_compile_cbs => $config_exe->before_each_compile_cbs,
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $all_object_files = [];
  
  my $perl_class_name = "SPVM::$class_name";
  
  my $native_method_names = $self->runtime->get_method_names($class_name, 'native');
  if (@$native_method_names) {
    my $native_module_file = $self->runtime->get_module_file($class_name);
    my $native_dir = $native_module_file;
    
    $native_dir =~ s/\.spvm$//;
    $native_dir .= 'native';
    my $input_dir = SPVM::Builder::Util::remove_class_part_from_file($native_module_file, $perl_class_name);
    my $build_object_dir = SPVM::Builder::Util::create_build_object_path($self->builder->build_dir);
    mkpath $build_object_dir;

    # Module file
    my $module_file = $self->runtime->get_module_file($class_name);
    unless (defined $module_file) {
      my $config_file = SPVM::Builder::Util::get_config_file_from_class_name($class_name);
      if ($config_file) {
        $module_file = $config_file;
        $module_file =~ s/\.config$/\.spvm/;
      }
      else {
        confess "\"$module_file\" module is not loaded";
      }
    }
    my $config_class = $builder_cc->create_native_config_from_module_file($module_file);
    
    my $include_dirs = [];
    my $exe_config = $self->config;
    my $resource_names = $exe_config->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $exe_config->get_resource($resource_name);
      my $resource_include_dir = $resource->config->get_native_include_dir;
      push @$include_dirs, $resource_include_dir;
    }
    
    my $object_files = $builder_cc->compile_source_files(
      $class_name,
      {
        input_dir => $input_dir,
        output_dir => $build_object_dir,
        config => $config_class,
        category => 'native',
        no_use_resource => 1,
        include_dirs => $include_dirs,
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
