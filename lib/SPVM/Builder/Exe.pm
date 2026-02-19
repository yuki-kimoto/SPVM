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

sub build_spvm_archive {
  my $self = shift;
  if (@_) {
    $self->{build_spvm_archive} = $_[0];
    return $self;
  }
  else {
    return $self->{build_spvm_archive};
  }
}

sub parent_runtime {
  my $self = shift;
  if (@_) {
    $self->{parent_runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{parent_runtime};
  }
}

sub spvmcc_info {
  my $self = shift;
  if (@_) {
    $self->{spvmcc_info} = $_[0];
    return $self;
  }
  else {
    return $self->{spvmcc_info};
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
  
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  my $app_name = $self->app_name;
  
  # New SPVM::Builder object
  my $work_dir = "spvmcc/$app_name";
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
    work_dir => $work_dir,
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
      $config = SPVM::Builder::Config::Exe->new;
    }
    else {
      Carp::confess("The config file '$config_file' is not found.");
    }
  }
  
  unless ($config->isa('SPVM::Builder::Config::Exe')) {
    Carp::confess("The class of a config object for creating an executable file must be SPVM::Builder::Config::Exe or its child class.");
  }
  
  unless ($config->output_type eq 'exe') {
    Carp::confess("output_type field in the config file '$config_file' for creating an executable file must be 'exe'.");
  }
  
  $self->{config} = $config;
  
  my $spvmcc_info = {};
  
  $self->spvmcc_info($spvmcc_info);
  
  $spvmcc_info->{app_name} = $app_name;
  
  my $config_exe = $self->config;
  
  if (defined $config_exe->mode) {
    $spvmcc_info->{mode} = $config_exe->mode;
  }
  
  $spvmcc_info->{classes_h} = {};
  
  $self->{builder} = $builder;
  
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
  $config->external_object_files($self->{external_object_files});
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  
  # SPVM archive
  my $spvm_archive = $config->get_spvm_archive;
  if (defined $spvm_archive) {
    my $spvm_archive_json;
    my $spvm_archive_dir; 

    # 1. Normalize input to a directory
    if (-f $spvm_archive) {
      # Case: tar.gz
      unless ($spvm_archive =~ /\.tar\.gz$/) {
        Carp::confess("SPVM archive file '$spvm_archive' must have '.tar.gz' extension");
      }
      
      # Extract all files to a temporary directory to handle it as a normal directory
      my $spvm_archive_dir_obj = File::Temp->newdir;
      $spvm_archive_dir = $spvm_archive_dir_obj->dirname;
      
      my $tar = Archive::Tar->new;
      $tar->read($spvm_archive) or die $tar->error;
      $tar->extract_all($spvm_archive_dir) or die "Could not extract $spvm_archive to $spvm_archive_dir";
    }
    elsif (-d $spvm_archive) {
      # Case: Directory
      $spvm_archive_dir = $spvm_archive;
    }
    else {
      Carp::confess("SPVM archive '$spvm_archive' not found");
    }

    # 2. Read and decode JSON (Common)
    my $json_file = "$spvm_archive_dir/spvm-archive.json";
    unless (-f $json_file) {
      Carp::confess("SPVM archive '$spvm_archive' must contain spvm-archive.json");
    }
    $spvm_archive_json = SPVM::Builder::Util::slurp_binary($json_file);
    
    my $spvm_archive_info_data = JSON::PP->new->decode($spvm_archive_json);
    my $skip_classes_config = $config->spvm_archive_skip_classes // [];
    my %skip_classes_h = map { $_ => 1 } @$skip_classes_config;
    $self->{spvm_archive_info} = {
      # Filter classes immediately using skip_classes_h
      classes_h => { 
        map { $_->{name} => $_ } 
        grep { !$skip_classes_h{$_->{name}} } 
        @{$spvm_archive_info_data->{classes}} 
      },
    };

    # 3. Prepare the final temporary directory for the compiler
    my $spvm_archive_extract_dir_obj = File::Temp->newdir;
    $self->{spvm_archive_extract_dir_obj} = $spvm_archive_extract_dir_obj;
    my $spvm_archive_extract_dir = $spvm_archive_extract_dir_obj->dirname;
    $self->{spvm_archive_extract_dir} = $spvm_archive_extract_dir;

    # 4. Copy and filter files (Common Logic)
    File::Copy::copy($json_file, "$spvm_archive_extract_dir/spvm-archive.json");
    
    # Copy classes and other resources using filtered logic
    $self->extract_archive_files($spvm_archive_dir, $spvm_archive_extract_dir, $self->{spvm_archive_info}{classes_h});
    
    # 5. Setup paths (Common)
    $compiler->add_include_dir("$spvm_archive_extract_dir/SPVM");
    $config_exe->add_include_dir_native("$spvm_archive_extract_dir/include");
    $config_exe->add_lib_dir("$spvm_archive_extract_dir/lib");
  }
  
  for my $include_dir (@{$builder->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $self->{compiler} = $compiler;
  
  $self->compile;
  
  return $self;
}

# Instance Methods
sub build_exe_file {
  my ($self) = @_;
  
  my $builder = $self->builder;
  
  my $config_exe = $self->config;
  
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
  
  # Generate SPVM class files for archive
  $self->generate_spvm_class_files_into_work_dir;
  
  # Add external object files
  for my $external_object_file (@{$config_exe->external_object_files}) {
    push @$object_files, SPVM::Builder::ObjectFileInfo->new(file => $external_object_file);
  }
  
  # Add object files from loaded archive
  my $spvm_archive = $self->config->get_spvm_archive;
  if (defined $spvm_archive) {
    my $spvm_archive_extract_dir = $self->{spvm_archive_extract_dir};
    my $object_files_in_spvm_archive = SPVM::Builder::Exe->find_object_files("$spvm_archive_extract_dir");
    for my $object_file_in_spvm_archive (@$object_files_in_spvm_archive) {
      push @$object_files, SPVM::Builder::ObjectFileInfo->new(file => $object_file_in_spvm_archive);
    }
  }
  
  # Output file settings
  my $output_file = $self->{output_file};
  my $output_dir_tmp = File::Temp->newdir;
  my $build_spvm_archive = $self->build_spvm_archive;
  my $spvm_archive_out = $output_file;
  
  # Skip executable generation if archive mode is on
  if ($build_spvm_archive) {
    my $output_file_base = basename $output_file;
    $output_file = "$output_dir_tmp/$output_file_base";
  }
  
  # Link
  my $config_linker = $self->config->clone;
  my $cc_linker = SPVM::Builder::CC->new(
    builder => $self->builder,
    quiet => $self->quiet,
    force => $self->force,
  );
  $config_linker->output_file($output_file);
  $cc_linker->link($class_name, $object_files, {config => $config_linker});
  
  # Archive output as directory
  if ($build_spvm_archive) {
    my $build_work_dir = $self->builder->create_build_work_path;
    my $spvmcc_info = $self->spvmcc_info;
    
    # Create directory if it does not exist
    unless (-d $spvm_archive_out) {
      if (-f $spvm_archive_out) {
        Carp::confess "Cannot create directory '$spvm_archive_out': File exists";
      }
      File::Path::mkpath($spvm_archive_out)
        or Carp::confess "Cannot create directory '$spvm_archive_out': $!";
    }
    
    # Copy build files
    $self->extract_archive_files($build_work_dir, $spvm_archive_out, $spvmcc_info->{classes_h});
    
    # Copy from existing archive
    my $spvm_archive_info;
    if (defined $spvm_archive) {
      my $spvm_archive_extract_dir = $self->{spvm_archive_extract_dir};
      $spvm_archive_info = $self->{spvm_archive_info};
      $self->extract_archive_files($spvm_archive_extract_dir, $spvm_archive_out, $spvm_archive_info->{classes_h});
    }
    
    # Write spvm-archive.json
    my $merged_spvmcc_info = $self->merge_spvmcc_info($spvm_archive_info, $spvmcc_info);
    my $merged_spvm_archive_json = JSON::PP->new->pretty->canonical(1)->encode($merged_spvmcc_info);
    
    my $json_file = "$spvm_archive_out/spvm-archive.json";
    open my $fh, '>', $json_file or die "Cannot open '$json_file': $!";
    print $fh $merged_spvm_archive_json;
    close $fh;
    
    my $lib_dir = "$spvm_archive_out/lib";
    unless (-d $lib_dir) {
      mkdir "$spvm_archive_out/lib"
       or Carp::confess "Could not create the lib directory in the SPVM archive: $!";
   }
  }
  
  # Write local archive info
  {
    my $spvmcc_info = $self->spvmcc_info;
    my $classes_h = delete $spvmcc_info->{classes_h};
    my $classes = [];
    for my $class_name (keys %$classes_h) {
      next if $class_name =~ /^eval::anon_class::\d+$/a;
      my $class = $classes_h->{$class_name};
      $class->{name} = $class_name;
      push @$classes, $class;
    }
    $spvmcc_info->{classes} = $classes;
    my $spvm_archive_json = JSON::PP->new->pretty->canonical(1)->encode($spvmcc_info);
    my $build_work_dir = $self->builder->create_build_work_path;
    my $spvm_archive_json_file = "$build_work_dir/spvm-archive.json";
    open my $fh, '>', $spvm_archive_json_file or die "Cannot open '$spvm_archive_json_file': $!";
    print $fh $spvm_archive_json;
    close $fh;
  }
}

sub generate_spvm_class_files_into_work_dir {
  my ($self) = @_;
  
  my $compiler = $self->compiler;
  
  my $build_dir = $self->builder->build_dir;
  my $work_dir = $self->builder->work_dir;
  my $class_names = $self->get_user_defined_basic_type_names;
  my $spvm_class_work_dir = "$build_dir/$work_dir/SPVM";
  for my $class_name (@$class_names) {
    my $spvm_class_path_part = $class_name;
    $spvm_class_path_part =~ s/::/\//g;
    my $spvm_class_path = "$spvm_class_work_dir/$spvm_class_path_part.spvm";
    
    mkpath dirname $spvm_class_path;
    
    my $class = $self->runtime->get_basic_type_by_name($class_name);
    
    if ($class_name =~ /^eval::anon_class::0$/) {
      my $version_string = $self->runtime->get_basic_type_by_name($class_name)->get_version_string($class_name);
      if (defined $version_string) {
        $self->spvmcc_info->{version} = $version_string;
      }
    }
    
    my $class_file = $compiler->get_class_file($class_name);
    my $class_file_content = $class_file->get_content;
    my $class_file_content_length = $class_file->get_content_length;
    
    open my $fh, '>', $spvm_class_path
      or die "Cannot open the file '$spvm_class_path':$!";
    
    syswrite($fh, $class_file_content, $class_file_content_length);
  }
}

sub compile {
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
  
  $self->config->class_name($class_name);
  
  my $runtime = $compiler->get_runtime;
  
  $self->runtime($runtime);
}

sub compile_classes {
  my ($self) = @_;
  
  my $class_names = $self->get_user_defined_basic_type_names;
  
  my $spvmcc_info = $self->spvmcc_info;
  
  my $object_files = [];
  for my $class_name (@$class_names) {
    
    my $exists_in_spvm_archive_info = $self->exists_in_spvm_archive_info($class_name);
    next if $exists_in_spvm_archive_info;
    
    $spvmcc_info->{classes_h}{$class_name} = {};
    
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
    builder => $self->builder,
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
  
int32_t main(int32_t command_args_length, const char *command_args[]) {
  
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
  
  my $boostrap_name_space = $self->create_boostrap_name_space;
  
  my $source = '';
  
  $source .= <<"EOS";
static void compile_all_classes(SPVM_ENV* env) {
  
  void* compiler = env->api->runtime->get_compiler(env->runtime);
  
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
  my $bootstrap_source_file = $self->create_bootstrap_source_file_path;
  
  mkpath dirname $bootstrap_source_file;
  
  # Config
  my $config_exe = $self->config;
  
  my $input_files = [@$class_files];
  my $output_file = $bootstrap_source_file;
  
  my $config_exe_loaded_config_files = $config_exe->get_loaded_config_files;
  my $need_generate_input_files = [@$input_files, @$config_exe_loaded_config_files];
  
  my $bootstrap_source = '';
  
  $bootstrap_source .= $self->create_bootstrap_header_source;
  
  $bootstrap_source .= $self->create_bootstrap_main_func_source;
  
  $bootstrap_source .= $self->create_bootstrap_build_runtime_source;
  
  $bootstrap_source .= $self->create_bootstrap_compile_source;
  
  $bootstrap_source .= $self->create_bootstrap_set_precompile_method_addresses_func_source;
  
  $bootstrap_source .= $self->create_bootstrap_set_native_method_addresses_func_source;
  
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
  my $source_file = $self->create_bootstrap_source_file_path;
  my $object_file_name = $self->create_bootstrap_object_file_path;
  
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
  my $output_dir = $self->builder->create_build_object_path;
  
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
    builder => $self->builder,
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
  
  my $spvmcc_info = $self->spvmcc_info;
  
  if (@$precompile_object_files) {
    $spvmcc_info->{classes_h}{$class_name}{precompile} = 1;
  }
  
  return $object_files;
}

sub compile_native_class {
  my ($self, $class_name) = @_;
  
  my $config_exe = $self->config;
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  # Compiler for native class
  my $builder_cc = SPVM::Builder::CC->new(
    builder => $self->builder,
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
    
    my $config = SPVM::Builder::Config->load_config($config_file);
    
    $config->config_exe($config_exe);
    
    my $object_files = $builder_cc->compile_class(
      $class_name,
      {
        runtime => $runtime,
        config => $config,
      }
    );
    push @$all_object_files, @$object_files;
    
    if (@$object_files) {
      my $spvmcc_info = $self->spvmcc_info;
      
      $spvmcc_info->{classes_h}{$class_name}{native} = 1;
    }
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

sub create_bootstrap_source_file_path {
  my ($self) = @_;
  
  my $build_src_dir = $self->builder->create_build_src_path;
  my $script_name = $self->script_name;
  my $bootstrap_source_file_base = basename $script_name;
  $bootstrap_source_file_base =~ s/\..*$//;
  $bootstrap_source_file_base .= '.c';
  my $bootstrap_source_file = "$build_src_dir/bootstrap/$bootstrap_source_file_base";
  
  return $bootstrap_source_file;
}

sub create_bootstrap_object_file_path {
  my ($self) = @_;
  
  my $build_object_dir = $self->builder->create_build_object_path;
  my $script_name = $self->script_name;
  my $bootstrap_source_file_base = basename $script_name;
  $bootstrap_source_file_base =~ s/\..*$//;
  $bootstrap_source_file_base .= '.o';
  my $bootstrap_source_file = "$build_object_dir/bootstrap/$bootstrap_source_file_base";
  
  return $bootstrap_source_file;
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

sub find_object_files {
  
  my ($class, $dir) = @_;
  
  my @object_files;
  
  find(
    {
      wanted => sub {
        my $path = $File::Find::name;
        
        if (-f $path) {
          if ($path =~ /\.o$/) {
            push @object_files, $path;
          }
        }
      },
      no_chdir => 1,
    },
    $dir
  );
  
  return \@object_files;
}

sub copy_with_timestamps {
  my ($source_file, $dest_file) = @_;
  
  copy($source_file, $dest_file)
    or Carp::confess "Failed to copy '$source_file' to '$dest_file': $!\n";
  
  my @stats = stat($source_file);
  my $atime = $stats[8];
  my $mtime = $stats[9];
  
  utime($atime, $mtime, $dest_file)
    or Carp::confess "Failed to restore timestamp for '$dest_file': $!\n";
  
  return 1;
}

sub extract_class_name_from_tar_file {
  my ($tar_file) = @_;
  
  my $class_name = $tar_file;
  $class_name =~ s|^object/||;
  $class_name =~ s/\..+$//;
  $class_name =~ s/\//::/g;
  $class_name =~ s/^SPVM:://;
  
  return $class_name;
}

sub exists_in_spvm_archive_info {
  my ($self, $class_name) = @_;
  
  my $exists_in_spvm_archive_info;
  my $spvm_archive_info = $self->{spvm_archive_info};
  if ($spvm_archive_info) {
    
    my $classes_h = $spvm_archive_info->{classes_h};
    
    if ($classes_h->{$class_name}) {
      $exists_in_spvm_archive_info = 1;
    }
  }
  
  return $exists_in_spvm_archive_info;
}

sub extract_archive_files {
  my ($self, $src_dir, $dest_dir, $classes_h) = @_;
  
  # Normalize the base source directory to use forward slashes for robust matching
  my $normalized_src_dir = $src_dir;
  $normalized_src_dir =~ tr|\\|/|;
  $normalized_src_dir =~ s|/+$||; # Remove trailing slash for consistent substitution

  File::Find::find(
    {
      wanted => sub {
        my $src_path = $File::Find::name;
        
        # 1. Normalize the current found path to forward slashes for logic
        my $normalized_src_path = $src_path;
        $normalized_src_path =~ tr|\\|/|;
        
        # 2. Extract the relative path correctly by using normalized strings
        my $rel_path = $normalized_src_path;
        unless ($rel_path =~ s/^\Q$normalized_src_dir\E\///) {
          # Skip if the path normalization failed to match the base directory
          return if $rel_path eq $normalized_src_path;
        }

        # Skip if not a file
        return unless -f $src_path;

        my $should_copy = 0;

        # 3. Check for files based on specific rules for directories and extensions

        # 3-1. SPVM source files (.spvm) from SPVM directory
        if ($rel_path =~ m|^SPVM/| && $rel_path =~ /\.spvm$/) {
          my $class_name = &extract_class_name_from_tar_file($rel_path);
          if ($classes_h->{$class_name}) {
            $should_copy = 1;
          }
        }
        # 3-2. Object files (.o) from object directory or SPVM directory
        elsif (($rel_path =~ m|^object/| || $rel_path =~ m|^SPVM/|) && $rel_path =~ /\.o$/) {
          my $class_name = &extract_class_name_from_tar_file($rel_path);
          if ($classes_h->{$class_name}) {
            $should_copy = 1;
          }
        }
        # 3-3. Library files (.a, .lib) from lib directory
        elsif ($rel_path =~ m|^lib/| && $rel_path =~ /\.(a|lib)$/) {
          $should_copy = 1;
        }
        # 3-4. Header files from include directory (excluding hidden files)
        elsif ($rel_path =~ m|^include/|) {
          my $basename = File::Basename::basename($rel_path);
          unless ($basename =~ /^\./) {
            $should_copy = 1;
          }
        }

        return unless $should_copy;
        
        # 4. Build the destination path by joining the base and the relative part
        # We use File::Spec for cross-platform safety
        my $dest_path = File::Spec->catfile($dest_dir, split('/', $rel_path));
        
        # 5. Ensure the destination directory exists (File::Basename is safe with catfile result)
        my $dest_parent = File::Basename::dirname($dest_path);
        unless (-d $dest_parent) {
          File::Path::mkpath($dest_parent) or Carp::confess "Cannot create directory '$dest_parent': $!";
        }
        
        # 6. Copy and preserve mtime
        File::Copy::copy($src_path, $dest_path) or Carp::confess "Copy failed from '$src_path' to '$dest_path': $!";
        my $mtime = (stat $src_path)[9];
        utime $mtime, $mtime, $dest_path;
      },
      no_chdir => 1,
    },
    $src_dir
  );
}

sub merge_spvmcc_info {
  my ($self, $spvm_archive_info1, $spvm_archive_info2) = @_;
  
  my $merged_spvm_archive_info = {};
  $merged_spvm_archive_info->{app_name} = $spvm_archive_info2->{app_name};
  if (defined $spvm_archive_info2->{mode}) {
    $merged_spvm_archive_info->{mode} = $spvm_archive_info2->{mode};
  }
  if (defined $spvm_archive_info2->{version}) {
    $merged_spvm_archive_info->{version} = $spvm_archive_info2->{version};
  }
  
  $merged_spvm_archive_info->{classes_h} = {};
  
  if ($spvm_archive_info1) {
    for my $class_name (keys %{$spvm_archive_info1->{classes_h}}) {
      $merged_spvm_archive_info->{classes_h}{$class_name} = $spvm_archive_info1->{classes_h}{$class_name};
    }
  }
  
  for my $class_name (keys %{$spvm_archive_info2->{classes_h}}) {
    $merged_spvm_archive_info->{classes_h}{$class_name} = $spvm_archive_info2->{classes_h}{$class_name};
  }
  
  my $merged_spvm_archive_info_classes_h = delete $merged_spvm_archive_info->{classes_h};
  
  my $classes = [];
  for my $class_name (keys %$merged_spvm_archive_info_classes_h) {
    next if $class_name =~ /^eval::anon_class::\d+$/a;
    my $class = $merged_spvm_archive_info_classes_h->{$class_name};
    $class->{name} = $class_name;
    push @$classes, $class;
  }
  
  $classes = [sort { $a->{name} cmp $b->{name} } @$classes];
  
  $merged_spvm_archive_info->{classes} = $classes;
  
  return $merged_spvm_archive_info;
}

1;

=head1 Name

SPVM::Builder::Exe - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
