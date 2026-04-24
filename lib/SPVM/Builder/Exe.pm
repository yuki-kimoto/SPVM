package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp ();
use JSON::PP;
use File::Basename 'basename', 'dirname', 'fileparse';
use File::Path 'mkpath', 'rmtree';
use File::Find 'find';
use Archive::Tar;
use File::Copy 'copy';
use Time::HiRes;
use Digest::SHA 'sha1_hex';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config::Global;
use SPVM::Builder::Config::Exe;
use SPVM::Builder::Config::DLL;

use SPVM::Builder::Native::Compiler;
use SPVM::Builder::Native::Runtime;
use SPVM::Builder::Native::BasicType;
use SPVM::Builder::Native::ClassFile;
use SPVM::Builder::ScriptInfo;
use SPVM::Builder::ObjectFileInfo;
use SPVM::Builder::Config::Util;

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

sub config_global {
  my $self = shift;
  if (@_) {
    $self->{config_global} = $_[0];
    return $self;
  }
  else {
    return $self->{config_global};
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
  
  my $self = bless {
    external_object_files => [],
    %options
  }, $class;
  
  my $script_name = $self->{script_name};
  
  $self->check_script_name;
  
  # Excutable file name
  my $output_file = $self->{output_file};
  unless (defined $output_file) {
    Carp::confess("A output file must be defined.");
  }
  
  my $app_name = $self->app_name;
  
  # Config mode
  my $config_mode = $self->{mode};
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(
    exists $self->{build_dir} ? (build_dir => $self->{build_dir}) : (),
  );
  
  # Config file settings
  my $allow_no_config_file = $self->{allow_no_config_file};
  
  # Config
  my $config_file = $script_name;
  $config_file =~ s/\..*$//;
  $config_file .= '.config';
  
  my $config_global;
  if (-f $config_file) {
    $config_global = SPVM::Builder::Config::Util::load_mode_config($config_file, $config_mode);
  }
  else {
    if ($allow_no_config_file) {
      $config_global = SPVM::Builder::Config::Exe->new;
    }
    else {
      Carp::confess("The config file '$config_file' is not found.");
    }
  }
  
  unless ($config_global->isa('SPVM::Builder::Config::Global')) {
    Carp::confess("The class of a config object for creating an executable file must be SPVM::Builder::Config::Global or its child class.");
  }
  
  $self->{config_global} = $config_global;
  
  $self->{builder} = $builder;
  
  # Override config settings with command line options if defined
  {
    if (defined $self->{external_object_files}) {
      $config_global->external_object_files($self->{external_object_files});
    }
  }
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  
  for my $include_dir (@{$builder->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $self->{compiler} = $compiler;
  
  $self->prepare_compile;
  
  return $self;
}

# Instance Methods
sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  my $config_global = $self->config_global;
  
  my $class_name = $self->{class_name};
  
  my $class = $self->runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $class->get_class_file;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  # Object files
  my $compile_infos = [];
  
  # Compile bootstrap C source
  my $bootstrap_compile_info = $self->prepare_compile_bootstrap_source_file;
  push @$compile_infos, $bootstrap_compile_info;
  
  # Compile SPVM core source files
  my $spvm_compile_infos = $self->prepare_compile_spvm_core_source_files;
  push @$compile_infos, @$spvm_compile_infos;
  
  my $classes_compile_infos = $self->prepare_compile_classes;
  push @$compile_infos, @$classes_compile_infos;
  
  my $output_file = $self->{output_file};
  $config_global = $self->config_global->clone;
  my $runtime = $self->runtime;
  
  my $cc = SPVM::Builder::CC->new(
    builder => $self->builder,
    quiet => $self->quiet,
    runtime => $runtime,
  );
  $config_global->output_file($output_file);
  
  for my $compile_info (@$compile_infos) {
    $cc->finalize_compile_info($compile_info);
  }
  
  $cc->command_parallel($compile_infos);
  
  my $object_file_infos = [map { SPVM::Builder::ObjectFileInfo->new(compile_info => $_, file => $_->output_file) } @$compile_infos];
  
  # Add external object files
  for my $external_object_file (@{$config_global->external_object_files}) {
    push @$object_file_infos, SPVM::Builder::ObjectFileInfo->new(file => $external_object_file);
  }
  
  unless (@$object_file_infos) {
    confess("[Unexpected Error]\$object_file_infos must have object files.");
  }
  
  # Link object files and generate a dynamic library
  my $link_info = $cc->prepare_link($class_name, $object_file_infos, $config_global);
  
  $cc->command_parallel([$link_info]);
  
  # after_link_cbs
  my $after_link_cbs = $config_global->after_link_cbs;
  for my $after_link_cb (@$after_link_cbs) {
    $after_link_cb->($link_info->config, $link_info);
  }
}

sub prepare_compile {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  my $script_name = $self->{script_name};
  
  my $compiler = $self->compiler;
  
  open my $script_fh, '<', $script_name
    or die "Can't open file '$script_name':$!";
    
  my $source = do { local $/; <$script_fh> };
  
  $source = "#file \"$script_name\"\x{A}$source";
  
  my $class_name = $compiler->compile_anon_class_with_exit($source, __FILE__, __LINE__);
  
  $self->class_name($class_name);
  
  $self->config_global->class_name($class_name);
  
  my $runtime = $compiler->get_runtime;
  
  $self->runtime($runtime);
}

sub prepare_compile_classes {
  my ($self) = @_;
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $compile_infos = [];
  for my $class_name (@$class_names) {
    my $precompile_compile_infos = $self->prepare_compile_precompile_class($class_name);
    push @$compile_infos, @$precompile_compile_infos;
  }
  
  for my $class_name (@$class_names) {
    my $native_compile_infos = $self->prepare_compile_native_class($class_name);
    push @$compile_infos, @$native_compile_infos;
  }
  
  return $compile_infos;
}

sub prepare_compile_source_file {
  my ($self, $options) = @_;
  
  my $config = $options->{config};
  my $config_global = $self->config_global;
  my $include_dir = $self->{include_dir};
  my $source_rel_file = $options->{source_rel_file};
  
  $config->config_global($config_global);
  
  my $builder = $self->builder;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  
  my $runtime = $self->runtime;
  
  # Compile command
  my $builder_cc = SPVM::Builder::CC->new(
    builder => $self->builder,
    quiet => $self->quiet,
    runtime => $runtime,
  );
  
  my $compile_info = SPVM::Builder::CompileInfo->new(
    source_rel_file => $source_rel_file,
    config => $config,
    category => $options->{category},
  );
  
  $compile_info->dependent_files([$include_dir]);
  
  return $compile_info;
}

sub create_bootstrap_header_source {
  my ($self) = @_;

  # Config
  my $config_global = $self->config_global;

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
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  $source .= "void ${boostrap_name_space}build_runtime(SPVM_ENV* env);\n\n";
  
  $source .= "static void set_precompile_method_addresses(SPVM_ENV* env);\n";
  
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
  
  $source .= "static void set_native_method_addresses(SPVM_ENV* env);\n\n";
  
  $source .= "static void compile_all_classes(SPVM_ENV* env);\n\n";
  
  $source .= <<"EOS";
static void set_precompile_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* precompile_address);

EOS

  $source .= <<"EOS";
static void set_native_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* native_address);

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
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  $source .= <<"EOS";
int main(int argc, char* argv[]);
int SPVMCC__main(int argc, char* argv[]);

int SPVMCC__main(int argc, char* argv[]) {
  
  int32_t error_id = 0;
  
  SPVM_ENV* boot_env = SPVM_NATIVE_new_env();
  
  void* compiler = boot_env->api->compiler->new_instance();
  
  SPVM_ENV* env = boot_env->new_env();
  
  error_id = env->api->compiler->compile(compiler, NULL);
  assert(error_id == 0);
  
  env->runtime = env->api->compiler->get_runtime(compiler);
  
  ${boostrap_name_space}build_runtime(env);
  
  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(env->runtime);
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  // Set the program name and the command line arguments
  {
    int32_t mortal_stack_top = env->enter_scope(env, stack);
    
    void* obj_program_name = env->new_string(env, stack, argv[0], strlen(argv[0]));
    
    // ARGV - string[]
    void* obj_argv = env->new_string_array(env, stack, argc - 1);
    for (int32_t arg_index = 1; arg_index < argc; arg_index++) {
      void* obj_arg = env->new_string(env, stack, argv[arg_index], strlen(argv[arg_index]));
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
  error_id = env->call_method(env, stack, method, args_width, __func__, __FILE__, __LINE__);
  if (error_id) {
    error_id = env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, __FILE__, __LINE__);
    goto END_OF_FUNC;
  }
  
  END_OF_FUNC:
  
  if (error_id) {
    /* Enter a new scope to handle the exception message object safely */
    int32_t scope_id = env->enter_scope(env, stack);
    
    /* Reconstruct the exception message including the SPVM stack trace */
    void* obj_exception_with_stack_trace = env->build_exception_message(env, stack, 0);
    
    /* Print the full exception message to stderr */
    env->print_stderr(env, stack, obj_exception_with_stack_trace);
    fprintf(spvm_stderr, "\\n");
    
    /* Leave the scope to free the exception message object */
    env->leave_scope(env, stack, scope_id);
  }
  
  env->call_end_methods(env, stack);
  
  env->destroy_class_vars(env, stack);
  
  env->free_stack(env, stack);
  
  env->free_env(env);
  
  boot_env->api->compiler->free_instance(compiler);
  
  boot_env->free_env(boot_env);
  
  return error_id;
}

int main(int argc, char* argv[]) {
  return SPVMCC__main(argc, argv);
}

EOS

  return $source;
}

sub create_bootstrap_build_runtime_source {
  my ($self) = @_;
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  $source .= <<"EOS";

void ${boostrap_name_space}build_runtime(SPVM_ENV* env) {
  
  compile_all_classes(env);
  
  set_precompile_method_addresses(env);
  
  set_native_method_addresses(env);
}

EOS
  
  return $source;
}

sub create_bootstrap_compile_source {
  my ($self) = @_;
  
  # Builder
  my $builder = $self->builder;
  
  # Namespace
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  # Start function
  $source .= <<"EOS";
static void compile_all_classes(SPVM_ENV* env) {
  
  /* Get compiler */
  void* compiler = env->api->runtime->get_compiler(env->runtime);
  
EOS
  
  # User defined classes
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
    
    # Add class file
    $source_class_file .= qq|    env->api->compiler->add_class_file(compiler, "$class_name");\n|;
    
    $source_class_file .= qq|    void* class_file = env->api->compiler->get_class_file(compiler, "$class_name");\n|;
    
    # Set relative file path
    if (defined $class_file_rel_file) {
      $source_class_file .= qq|    env->api->class_file->set_rel_file(compiler, class_file, "$class_file_rel_file");\n|;
    }
    
    # Set content as C string literal
    if (defined $class_file_content) {
      my $content_literal = $compiler->create_c_string_literal($class_file_content);
      $source_class_file .= qq|    env->api->class_file->set_content(compiler, class_file, \n$content_literal    );\n|;
    }
    
    # Set content length
    $source_class_file .= qq|    env->api->class_file->set_content_length(compiler, class_file, $class_file_content_length);\n|;
    
    $source_class_file .= qq|  }\n|;
    
    $source .= $source_class_file;
  }
  
  # Set debug info
  $source .= qq|  env->api->compiler->set_start_file(compiler, __FILE__);\n|;
  $source .= qq|  env->api->compiler->set_start_line(compiler, __LINE__ + 1);\n|;
  
  # Compile
  my $start_class_name = $self->{class_name};
  $source .= qq|  int32_t error_id = env->api->compiler->compile(compiler, \"$start_class_name\");\n|;
  
  # Error handling
  $source .= qq|  void* runtime = env->api->compiler->get_runtime(compiler);\n|;
  $source .= qq|  FILE* spvm_stderr = env->api->runtime->get_spvm_stderr(runtime);\n|;
  $source .= qq|  if (error_id != 0) {\n|;
  $source .= qq|    fprintf(spvm_stderr, "[Unexpected Compile Error]%s.", env->api->compiler->get_error_message(compiler, 0));\n|;
  $source .= qq|    exit(255);\n|;
  $source .= qq|  }\n|;
  
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
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  $source .= <<"EOS";
static void set_precompile_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* precompile_address) {
  void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
  void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, method_name);
  env->api->method->set_precompile_address(env->runtime, method, precompile_address);
}

EOS
  
  $source .= <<"EOS";
static void set_native_method_address(SPVM_ENV* env, const char* class_name, const char* method_name, void* native_address) {
  void* class_basic_type = env->api->runtime->get_basic_type_by_name(env->runtime, class_name);
  void* method = env->api->basic_type->get_method_by_name(env->runtime, class_basic_type, method_name);
  env->api->method->set_native_address(env->runtime, method, native_address);
}

EOS

  $source .= "static void set_precompile_method_addresses(SPVM_ENV* env){\n";
  
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $precompile_method_names = $class->get_precompile_method_names;
    
    for my $precompile_method_name (@$precompile_method_names) {
      $source .= <<"EOS";
  set_precompile_method_address(env, "$class_name", "$precompile_method_name", &SPVMPRECOMPILE__${class_cname}__$precompile_method_name);
  
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
  set_precompile_method_address(env, "$anon_basic_type_name", "", &SPVMPRECOMPILE__${anon_basic_type_cname}__);
  
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
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  $source .= "static void set_native_method_addresses(SPVM_ENV* env){\n";
  
  for my $class_name (@$class_names) {
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $native_method_names = $class->get_native_method_names;
    
    for my $native_method_name (@$native_method_names) {
      $source .= <<"EOS";
  set_native_method_address(env, "$class_name", "$native_method_name", &SPVM__${class_cname}__$native_method_name);
  
EOS
    }
  }

  $source .= "}\n";
  
  return $source;
}

sub create_bootstrap_source {
  my ($self) = @_;
  
  # Build bootstrap source content
  my $bootstrap_source = '';
  
  $bootstrap_source .= $self->create_bootstrap_header_source;
  
  $bootstrap_source .= $self->create_bootstrap_main_func_source;
  
  $bootstrap_source .= $self->create_bootstrap_build_runtime_source;
  
  $bootstrap_source .= $self->create_bootstrap_compile_source;
  
  $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;
  
  $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;
  
  $bootstrap_source .= "\n";
  
  return $bootstrap_source;
}

sub prepare_compile_bootstrap_source_file {
  my ($self) = @_;
  
  # Create bootstrap C source
  my $bootstrap_source = $self->create_bootstrap_source;
  
  my $source_rel_file = $self->create_bootstrap_source_rel_file_path($bootstrap_source);
  
  # Source file - Output
  my $bootstrap_source_file = $self->builder->create_build_src_path($source_rel_file);
  
  # Check if generating is needed by comparing content
  SPVM::Builder::Util::spurt_binary($bootstrap_source_file, $bootstrap_source, $self->builder->global_lock_fh);
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  my $config_global = $self->config_global;
  $config->config_global($config_global);
  $config->cc_input_dir($self->builder->create_build_src_path);
  
  # Compile
  my $compile_info = $self->prepare_compile_source_file({
    source_rel_file => $source_rel_file,
    config => $config,
    category => 'bootstrap',
  });
  
  return $compile_info;
}

sub prepare_compile_spvm_core_source_files {
  my ($self) = @_;
  
  # Config
  my $config = SPVM::Builder::Util::API::create_default_config();
  my $config_global = $self->config_global;
  $config->config_global($config_global);
  
  my $builder_dir = SPVM::Builder::Util::get_builder_dir();
  
  # SPVM src directory
  my $builder_src_dir = "$builder_dir/src";
  
  my $builder_include_dir = "$builder_dir/include";
  
  my $cc_input_dir = $builder_dir;
  $cc_input_dir =~ s|/SPVM/Builder$||;
  
  $config->cc_input_dir($cc_input_dir);
  
  # SPVM runtime source files
  my $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  
  # Object dir
  my $output_dir = $self->builder->create_build_object_path;
  
  # Compile source files
  my $compile_infos = [];
  for my $spvm_runtime_src_base_name (@$spvm_runtime_src_base_names) {
    my $source_rel_file = "SPVM/Builder/src/$spvm_runtime_src_base_name";
    my $compile_info = $self->prepare_compile_source_file({
      source_rel_file => $source_rel_file,
      config => $config,
      category => 'spvm_core',
      include_dir => $builder_include_dir,
    });
    push @$compile_infos, $compile_info;
  }
  
  return $compile_infos;
}

sub prepare_compile_precompile_class {
  my ($self, $class_name) = @_;
  
  my $config_global = $self->config_global;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $runtime = $self->runtime;
  
  my $builder_cc = SPVM::Builder::CC->new(
    builder => $self->builder,
    quiet => $self->quiet,
    runtime => $runtime,
  );
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  
  $config->category('precompile');
  
  $config->config_global($config_global);
  
  my $compile_infos = [];
  my $precompile_compile_infos = $builder_cc->prepare_compile_class($class_name, $config);
  push @$compile_infos, @$precompile_compile_infos;
  
  return $compile_infos;
}

sub prepare_compile_native_class {
  my ($self, $class_name) = @_;
  
  my $config_global = $self->config_global;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $runtime = $self->runtime;
  
  # Compiler for native class
  my $builder_cc = SPVM::Builder::CC->new(
    builder => $self->builder,
    quiet => $self->quiet,
    runtime => $runtime,
  );
  
  my $all_compile_infos = [];
  
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
    
    my $config = SPVM::Builder::Config::Util::load_config($config_file);
    
    $config->config_global($config_global);
    
    my $compile_resources = $self->class_name eq $class_name ? 1 : 0;
    
    $builder_cc->no_compile_resources(!$compile_resources);
    
    my $compile_infos = $builder_cc->prepare_compile_class($class_name, $config);
    push @$all_compile_infos, @$compile_infos;
  }
  
  return $all_compile_infos;
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
       $hash->{$class_name} //= [];
        push @{$hash->{$class_name}}, $value;
      }
      else {
        $hash->{$class_name} = $value;
      }
    }
    else {
      Carp::confess "Invalid option value '$option_value' for $option_name option.";
    }
  }
  
  return $hash;
}

sub create_bootstrap_source_rel_file_path {
  my ($self, $bootstrap_source) = @_;
  
  unless (defined $bootstrap_source) {
    confess("A bootstrap source must be defined.");
  }
  
  # Create a SHA-1 hex digest from the bootstrap source content
  my $digest = sha1_hex($bootstrap_source);
  my $dir_1 = substr($digest, 0, 2);
  my $dir_2 = substr($digest, 2);
  
  # Get the base filename without extension
  my $script_name = $self->script_name;
  my $file_base = basename $script_name;
  $file_base =~ s/\..*$//;
  
  # Final relative path: bootstrap/[xx]/[xxxx...]/[script_name].c
  my $bootstrap_source_rel_file = "bootstrap/$dir_1/$dir_2/$file_base.c";
  
  return $bootstrap_source_rel_file;
}

sub check_script_name {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  unless (defined $script_name) {
    Carp::confess("A script name must be defined.");
  }
  
  my ($script_name_base) = fileparse $script_name;
  
  unless ($script_name_base =~ /^[a-zA-Z_][a-zA-Z_0-9\-]*\.spvm$/) {
    Carp::confess "The script base name must match the regex qr/^[a-zA-Z_][a-zA-Z_0-9\\-]*\\.spvm\$/. SCRIPT_NAME='$script_name'.";
  }
  
  if ($script_name_base =~ /--/) {
    Carp::confess "The script base name cannnot contain '--'. SCRIPT_NAME=$script_name.";
  }
  
  if ($script_name_base =~ /__/) {
    Carp::confess "The script base name cannot contain '__'. SCRIPT_NAME=$script_name.";
  }
  
}

sub app_name {
  my ($self) = @_;
  
  my $script_name = $self->script_name;
  
  my $app_name = basename $script_name;
  $app_name =~ s/\.spvm$//;
  
  return $app_name;
}

sub create_boostrap_name_space {
  my ($self, $app_name) = @_;
  
  unless (defined $app_name) {
    $app_name = $self->app_name;
  }
  
  $app_name =~ s/-/____/g;
  
  my $name_space = "SPVM_BOOTSTRAP_${app_name}______";
  
  return $name_space;
}

1;

=head1 Name

SPVM::Builder::Exe - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
