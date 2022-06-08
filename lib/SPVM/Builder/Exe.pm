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
use SPVM::Builder::LinkInfo;

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
  unless (defined $self->{quiet}) {
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
    $config = SPVM::Builder::Config::Exe->load_config($config_file);
    unless ($config->is_exe) {
      confess "Config file \"$config_file\" is not the config to create the executable file";
    }
  }
  else {
    $config = SPVM::Builder::Config::Exe->new_gnu99;
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
    $builder->print_error_messages(*STDERR);
    exit(255);
  }
  
  # Build runtime
  $builder->build_runtime;
  
  # Config file
  my $module_file = $builder->get_module_file($class_name);
  
  # Object files
  my $object_files = [];

  # Compile SPVM core source files
  my $spvm_core_objects = $self->compile_spvm_core_sources;
  push @$object_files, @$spvm_core_objects;
  
  my $no_precompile = $config->no_precompile;

  unless ($no_precompile) {
    # Create precompile C source_files
    $self->create_precompile_sources;
    
    # Compile precompile C source_files
    my $precompile_object_files = $self->compile_precompile_sources;
    push @$object_files, @$precompile_object_files;
  }

  # Compile native source files
  my $native_object_files = $self->compile_native_sources;
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
  
  my $config_dependent_files = $config->dependent_files;
  my $need_generate_input_files = [@$input_files, @$config_dependent_files];
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config->force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });
  
  if ($need_generate) {
    $create_cb->();
  }
}

sub compile_source_file {
  my ($self, $opt) = @_;

  # Config
  my $config = $self->config;
  
  my $opt_ccflags = $opt->{ccflags};
  $opt_ccflags = [] unless defined $opt_ccflags;
  
  if (@$opt_ccflags) {
    $config->add_ccflags(@$opt_ccflags);
  }

  my $source_file = $opt->{source_file};
  my $output_file = $opt->{output_file};
  my $depend_files = $opt->{depend_files};
  unless ($depend_files) {
    $depend_files = [];
  }
  
  my $config_dependent_files = $config->dependent_files;
  my $need_generate_input_files = [$source_file, @$depend_files, @$config_dependent_files];
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config->force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });

  # Compile command
  my $builder_cc = SPVM::Builder::CC->new;

  my $compile_info = $builder_cc->create_compile_command_info({config => $config, output_file => $output_file, source_file => $source_file});
  my $cc_cmd = $builder_cc->create_compile_command($compile_info);

  my $compile_info_cc = $compile_info->{cc};
  my $compile_info_ccflags = $compile_info->{ccflags};

  if ($need_generate) {
    # Execute compile command
    my $cbuilder = ExtUtils::CBuilder->new;
    $cbuilder->do_system(@$cc_cmd)
      or confess "Can't compile $source_file: @$cc_cmd";
  }
  
  my $object_file_info = SPVM::Builder::ObjectFileInfo->new(
    object_file => $output_file,
    source_file => $source_file,
    cc => $compile_info_cc,
    ccflags => $compile_info_ccflags,
    is_exe_config => $config->is_exe,
  );
  
  return $object_file_info;
}

sub create_bootstrap_header_source {
  my ($self) = @_;

  # Config
  my $config = $self->config;

  # Builder
  my $builder = $self->builder;

  # Class name
  my $class_name = $self->class_name;

  # Class names
  my $class_names = $self->builder->get_class_names;
  
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];

  my $source = '';

  $source .= <<'EOS';

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_native.h"

EOS
  
  my $no_precompile = $config->no_precompile;
  
  unless ($no_precompile) {
    $source .= "// precompile functions declaration\n";
    for my $class_name (@$class_names) {
      my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
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
    my $native_method_names = $builder->get_method_names($class_cname, 'native');
    for my $method_name (@$native_method_names) {
      my $class_cname = $class_cname;
      $class_cname =~ s/::/__/g;
      $source .= <<"EOS";
int32_t SPVM__${class_cname}__$method_name(SPVM_ENV* env, SPVM_VALUE* stack);
EOS
    }
  }

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env);\n";

  $source .= "static int32_t* SPVM_BOOTSTRAP_get_spvm_32bit_codes();\n";

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
  my $class_names = $self->builder->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];

  my $source = '';

  $source .= <<"EOS";

int32_t main(int32_t argc, const char *argv[]) {

  SPVM_ENV* env = SPVM_NATIVE_new_env_prepared();

  // Class name
  const char* class_name = "$class_name";
  
  // Class
  int32_t method_id = env->get_class_method_id(env, class_name, "main", "int(string,string[])");
  
  if (method_id < 0) {
    fprintf(stderr, "Can't find %s->main method", class_name);
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
    env->print_stderr(env, env->exception_object);
    printf("\\n");
    status = 255;
  }
  else {
    status = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);

  env->free_env_prepared(env);

  return status;
}
EOS

  return $source;
}

sub create_bootstrap_get_spvm_32bit_codes_func_source {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;

  my $spvm_32bit_codes = $builder->get_spvm_32bit_codes;
  my $spvm_32bit_codes_length = @$spvm_32bit_codes;
  my $source = '';
  
  my $spvm_32bit_codes_str = join(",", @$spvm_32bit_codes);

  $source .= "static int32_t SPVM_BOOTSTRAP_spvm_32bit_codes[$spvm_32bit_codes_length] = {$spvm_32bit_codes_str};\n";

  $source .= <<"EOS";
static int32_t* SPVM_BOOTSTRAP_get_spvm_32bit_codes() {
  return SPVM_BOOTSTRAP_spvm_32bit_codes;
}
EOS
  
  return $source;
}

sub create_bootstrap_new_env_prepared_func_source {
  my ($self) = @_;

  # Config
  my $config = $self->config;

  # Builder
  my $builder = $self->builder;

  # Class name
  my $class_name = $self->class_name;

  # Class names
  my $class_names = $self->builder->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];

  my $source = '';
  
  my $no_precompile = $config->no_precompile;
  
  my $set_precompile_method_addresses_source = '';
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
  void* runtime = env->api->runtime->new_runtime(env);
  
  // Runtime allocator
  void* runtime_allocator = env->api->runtime->get_allocator(runtime);
  
  // Create SPVM 32bit codes
  int32_t* spvm_32bit_codes = SPVM_BOOTSTRAP_get_spvm_32bit_codes();
  
  // Build runtime
  env->api->runtime->build(runtime, spvm_32bit_codes);

  // Prepare runtime
  env->api->runtime->prepare(runtime);

  // Set runtime information
  env->runtime = runtime;

  // Initialize env
  env->init_env(env);

  // Set precompile method addresses
  $set_precompile_method_addresses_source
  
  // Set native method addresses
  SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(env);
  
  env->call_init_blocks(env);
  
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
  my $class_names = $self->builder->get_class_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_precompile_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
    
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
  my $class_names = $self->builder->get_class_names;

  my $source = '';

  $source .= "static int32_t* SPVM_BOOTSTRAP_create_bootstrap_set_native_method_addresses(SPVM_ENV* env){\n";

  for my $class_name (@$class_names) {
    my $class_cname = $class_name;
    $class_cname =~ s/::/__/g;
    
    my $native_method_names = $builder->get_method_names($class_name, 'native');
    
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
  
  # Config
  my $config = $self->config;

  # Builder
  my $builder = $self->builder;
  
  # Class name
  my $class_name = $self->class_name;
  
  # Class names
  my $class_names = $builder->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  
  # Module files - Input
  my $module_files = [];
  for my $class_name (@$class_names_without_anon) {
    my $module_file = $builder->get_module_file($class_name);
    push @$module_files, $module_file;
  }
  
  # Source file - Output
  my $build_src_dir = $self->builder->create_build_src_path;
  my $target_perl_class_name = "SPVM::$class_name";
  my $bootstrap_base = $target_perl_class_name;
  $bootstrap_base =~ s|::|/|g;
  my $bootstrap_source_file = "$build_src_dir/$bootstrap_base.boot.c";
  
  my $no_precompile = $config->no_precompile;

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
    unless ($no_precompile) {
      $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;
    }

    # Set native method addresses function
    $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;

    # get_spvm_32bit_codes function
    $bootstrap_source .= $self->create_bootstrap_get_spvm_32bit_codes_func_source;

    # Build source directory
    my $build_src_dir = $self->builder->create_build_src_path;
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

sub compile_bootstrap_source {
  my ($self) = @_;
  
  # Target class name
  my $class_name = $self->class_name;
  
  my $target_perl_class_name = "SPVM::$class_name";
  
  # Compile source files
  my $class_name_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($target_perl_class_name);
  my $object_file = $self->builder->create_build_output_path("$class_name_rel_file.boot.o");
  my $source_file = $self->builder->create_build_src_path("$class_name_rel_file.boot.c");
  
  # Create directory for object file output
  mkdir dirname $object_file;
  
  # Compile
  my $object_file_info = $self->compile_source_file({source_file => $source_file, output_file => $object_file});
  
  return $object_file_info;
}

sub compile_spvm_core_sources {
  my ($self) = @_;

  # Config
  my $config = $self->config;

  # SPVM::Builder::Config directory
  my $spvm_builder_config_dir = $INC{"SPVM/Builder/Config.pm"};

  # SPVM::Builder directory
  my $spvm_builder_dir = $spvm_builder_config_dir;
  $spvm_builder_dir =~ s/\/Config\.pm$//;

  # SPVM src directory
  my $spvm_core_source_dir = "$spvm_builder_dir/src";

  # SPVM header directory
  my $spvm_core_header_dir = "$spvm_builder_dir/include";
  
  # SPVM runtime source files
  my $no_compiler_api = $config->no_compiler_api;
  my $spvm_runtime_src_base_names;
  if ($no_compiler_api) {
    $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_common_source_file_names();
  }
  else {
    $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  }
  my @spvm_core_source_files = map { "$spvm_core_source_dir/$_" } @$spvm_runtime_src_base_names;

  # Object dir
  my $output_dir = $self->builder->create_build_output_path;
  mkpath $output_dir;
  
  # Compile source files
  my $object_file_infos = [];
  for my $src_file (@spvm_core_source_files) {
    # Object file
    my $object_file = "$output_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';

    my $no_compiler_api = $config->no_compiler_api;
    my $ccflags = [];
    if ($no_compiler_api) {
      push @$ccflags, '-DSPVM_NO_COMPILER_API';
    }
    
    my $object_file_info = $self->compile_source_file({
      ccflags => $ccflags,
      source_file => $src_file,
      output_file => $object_file,
    });
    push @$object_file_infos, $object_file_info;
  }
  
  return $object_file_infos;
}

sub create_precompile_sources {
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
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  for my $class_name (@$class_names_without_anon) {
    my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
    if (@$precompile_method_names) {
      
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      $builder_c_precompile->create_precompile_source_file(
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
    force => $self->force,
  );
  
  my $class_names = $builder->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  my $object_files = [];
  for my $class_name (@$class_names_without_anon) {
    my $precompile_method_names = $builder->get_method_names($class_name, 'precompile');
    if (@$precompile_method_names) {
      my $src_dir = $self->builder->create_build_src_path;
      mkpath $src_dir;
      
      my $output_dir = $self->builder->create_build_output_path;
      mkpath $output_dir;
      
      my $precompile_object_files = $builder_c_precompile->compile(
        $class_name,
        {
          src_dir => $src_dir,
          output_dir => $output_dir,
        }
      );
      push @$object_files, @$precompile_object_files;
    }
  }
  
  return $object_files;
}

sub compile_native_sources {
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
    force => $self->force,
  );
  
  my $class_names = $builder->get_class_names;
  my $class_names_without_anon = [grep { $_ !~ /::anon::/ } @$class_names];
  my $all_object_files = [];
  for my $class_name (@$class_names_without_anon) {

    my $perl_class_name = "SPVM::$class_name";
    
    my $native_method_names = $builder->get_method_names($class_name, 'native');
    if (@$native_method_names) {
      my $native_module_file = $builder->get_module_file($class_name);
      my $native_dir = $native_module_file;
      
      $native_dir =~ s/\.spvm$//;
      $native_dir .= 'native';
      my $src_dir = SPVM::Builder::Util::remove_class_part_from_file($native_module_file, $perl_class_name);
      my $output_dir = $self->builder->create_build_output_path;
      mkpath $output_dir;
      
      my $object_files = $builder_c_native->compile(
        $class_name,
        {
          src_dir => $src_dir,
          output_dir => $output_dir,
        }
      );
      push @$all_object_files, @$object_files;
    }
  }
  
  return $all_object_files;
}

sub link {
  my ($self, $object_file_infos) = @_;

  my $class_name = $self->class_name;
  
  my $config = $self->config;

  # CBuilder configs
  my $output_file = $self->{output_file};
  
  # Add output file extension
  my $output_file_base = basename $output_file;
  unless ($output_file_base =~ /\./) {
    my $exe_ext = $Config{exe_ext};
    $output_file .= $exe_ext;
  }

  # Linker
  my $ld = $config->ld;
  
  # All linker flags
  my @all_ldflags;
  
  # Linker flags
  my $ldflags = $config->ldflags;
  push @all_ldflags, @{$config->ldflags};
  
  # Linker optimize
  my $ld_optimize = $config->ld_optimize;
  push @all_ldflags, $ld_optimize;
  
  # Library directory
  my $lib_dirs = $config->lib_dirs;
  for my $lib_dir (@$lib_dirs) {
    if (-d $lib_dir) {
      push @all_ldflags, "-L$lib_dir";
    }
  }
  
  # Libraries
  my $libs = $config->libs;
  push @all_ldflags, map { "-l$_" } @$libs;
  
  # ExeUtils::CBuilder config
  my $cbuilder_config = {
    ld => $ld,
    ldflags => '',
    shrpenv => '',
    perllibs => '',
    libpth => '',
  };
  
  my $config_dependent_files = $config->dependent_files;
  my $need_generate_input_files = [@$object_file_infos, @$config_dependent_files];
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config->force,
    output_file => $output_file,
    input_files => $need_generate_input_files,
  });

  my $link_info = SPVM::Builder::LinkInfo->new(
    class_name => $class_name,
    object_file_infos => $object_file_infos,
    ld => $ld,
    ldflags => \@all_ldflags,
    is_exe => 1,
    output_file => $output_file,
  );

  my $before_link = $config->before_link;
  if ($before_link) {
    $before_link->($config, $link_info);
  }
  
  if ($need_generate) {
    my $link_info_ld = $link_info->ld;
    my $link_info_ldflags = $link_info->ldflags;
    my $link_info_class_name = $link_info->class_name;
    my $link_info_output_file = $link_info->output_file;
    my $link_info_object_file_infos = $link_info->object_file_infos;
    my $link_info_object_files = [map { $_->to_string } @$link_info_object_file_infos];
    my $link_info_ldflags_str = join(' ', @$link_info_ldflags);
    
    my $dynamic_lib = $config->dynamic_lib;
    my $static_lib = $config->static_lib;
    
    # CBuilder
    my $cbuilder = ExtUtils::CBuilder->new(quiet => $self->quiet, config => $cbuilder_config);

    # Create a dynamic library
    if ($dynamic_lib) {
      my $link_info_output_dir = dirname $link_info_output_file;
      my $link_info_output_file_base = basename $link_info_output_file;
      my $lib_file = $link_info_output_file;
      unless ($link_info_output_file_base =~ /\./) {
        $lib_file .= ".$Config{dlext}";
      }
      
      $cbuilder->link(
        objects => $link_info_object_files,
        module_name => $link_info_class_name,
        lib_file => $lib_file,
        extra_linker_flags => $link_info_ldflags_str,
      );
    }
    # Create a static library
    elsif ($static_lib) {
      my $link_info_output_dir = dirname $link_info_output_file;
      my $link_info_output_file_base = basename $link_info_output_file;
      my $lib_file = $link_info_output_file;
      unless ($link_info_output_file_base =~ /\./) {
        $lib_file .= ".a";
      }
    
      my @object_files = map { "$_" } @$link_info_object_files;
      my @ar_cmd = ('ar', 'rc', $lib_file, @object_files);
      $cbuilder->do_system(@ar_cmd);
    }
    # Create an executable file
    else {
      $cbuilder->link_executable(
        objects => $link_info_object_files,
        module_name => $link_info_class_name,
        exe_file => $link_info_output_file,
        extra_linker_flags => $link_info_ldflags_str,
      );
    }
  }
  
  return $output_file;
}

1;

=head1 NAME

SPVM::Builder::Exe - Create a Executable File
