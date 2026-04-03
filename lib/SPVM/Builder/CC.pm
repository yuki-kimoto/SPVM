package SPVM::Builder::CC;

use strict;
use warnings;

use Carp 'confess';
use Config;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';
use Time::HiRes ();
use POSIX ":sys_wait_h";
use Time::HiRes;

use SPVM::Builder::Util;
use SPVM::Builder::CompileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Native::BasicType;
use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  builder
  force
  quiet
  debug
  runtime
)];

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  return $self;
}

# Instance Methods
sub detect_force {
  my ($self, $config) = @_;
  
  unless ($config) {
    confess("The config \$config must be define.");
  }
  
  my $force;
  
  if (defined $self->force) {
    $force = $self->force;
  }
  elsif (defined $config->force) {
    $force = $config->force;
  }
  else {
    $force = 0;
  }
  
  return $force;
}

sub detect_quiet {
  my ($self, $config) = @_;
  
  my $quiet;
  
  if (defined $self->debug) {
    $quiet = 0;
  }
  elsif (defined $self->quiet) {
    $quiet = $self->quiet;
  }
  elsif (defined $config && defined $config->quiet) {
    $quiet = $config->quiet;
  }
  elsif (defined $config && $config->is_jit) {
    $quiet = 1;
  }
  else {
    $quiet = 0;
  }
  
  return $quiet;
}

sub prepare_compile_class {
  my ($self, $class_name, $config) = @_;
  
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  if (ref $class_name) {
    confess("[Unexpected Error]A class name must be non-reference.");
  }
  
  my $build_dir = $self->builder->build_dir;
  
  unless (defined $build_dir) {
    confess("[Unexpected Error]A build directory must be defined.");
  }
  
  unless (-d $build_dir) {
    confess("[Unexpected Error]A build directory must exists.");
  }
  
  $config->class_name($class_name);
  
  my $compile_infos = [];
  
  my $resource_compile_infos = $self->prepare_compile_resources($class_name, $config);
  push @$compile_infos, @$resource_compile_infos;
  
  my $native_compile_infos = $self->prepare_compile_native_class($class_name, $config);
  push @$compile_infos, @$native_compile_infos;
  
  return $compile_infos;
}

sub prepare_compile_resources {
  my ($self, $class_name, $config) = @_;
  
  my $runtime = $self->runtime;
  
  my $compile_infos = [];
  
  # Add resource include directories
  my $resource_names = $config->get_resource_names;
  my $resource_include_dirs = [];
  for my $resource_name (@$resource_names) {
    my $resource = $config->get_resource($resource_name);
    my $resource_config = $resource->config;
    
    my $resource_include_dir = $resource_config->native_include_dir;
    if (defined $resource_include_dir) {
      push @$resource_include_dirs, $resource_include_dir;
    }
  }
  
  my $need_compile_resources;
  if ($config->config_global) {
    if ($class_name eq $config->config_global->class_name) {
      $need_compile_resources = 1;
    }
    else {
      $need_compile_resources = 0;
    }
  }
  else {
    if ($config->is_resource) {
      $need_compile_resources = 0;
    }
    else {
      $need_compile_resources = 1;
    }
  }
  
  if ($need_compile_resources) {
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      
      my $resource_class_name = $resource->class_name;
      my $resource_config = $resource->config;
      
      $resource_config->add_include_dir(@$resource_include_dirs);
      
      my $builder_cc_resource = SPVM::Builder::CC->new(
        builder => $self->builder,
        quiet => $self->detect_quiet($config),
        force => $self->detect_force($config),
        runtime => $self->runtime,
      );
      
      my $resource_compile_infos = $builder_cc_resource->prepare_compile_class($resource_class_name, $resource_config);
      push @$compile_infos, @$resource_compile_infos;
    }
  }
  
  return $compile_infos;
}

sub prepare_compile_native_class {
  my ($self, $class_name, $config) = @_;
  
  my $is_cc_config = $config->isa('SPVM::Builder::Config') ? 1 : 0;
  unless ($is_cc_config) {
    return [];
  }
  
  my $runtime = $self->runtime;
  my $native_class_ext = $config->ext;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  # Check if a config file and an loaded SPVM class file are in the same directory.
  my $class_file = $basic_type->get_class_file;
  if (defined $config->file) {
    my $config_file_abs = File::Spec->rel2abs($config->file);
    my $class_file_abs  = File::Spec->rel2abs($class_file);
    
    my $config_dir  = dirname($config_file_abs);
    my $config_base = basename($config_file_abs);
    $config_base =~ s/\..*$//;
    
    my $class_dir  = dirname($class_file_abs);
    my $class_base = basename($class_file_abs);
    $class_base =~ s/\..*$//;
    
    unless ($config_dir eq $class_dir && $config_base eq $class_base) {
      confess("The config file \"$config_file_abs\" is not compatible with the SPVM file \"$class_file_abs\".");
    }
  }
  
  my $category = $config->category;
  
  if ($category eq 'precompile') {
    my $precompile_method_names = $basic_type->get_method_names_by_category($category);
    
    unless (@$precompile_method_names) {
      return [];
    }
  }
  
  my $compile_infos = [];
  
  my $cc_input_dir;
  if ($category eq 'precompile') {
    
    $cc_input_dir = $self->builder->create_build_src_path;
    
    my $config_precompile_class_source = $config->clone;
    
    $config_precompile_class_source->cc_input_dir($cc_input_dir);
    
    $self->generate_precompile_class_source_file($class_name, $config_precompile_class_source);
  }
  elsif ($category eq 'native') {
    if ($is_cc_config) {
      $cc_input_dir = SPVM::Builder::Util::get_class_base_dir($class_file, $class_name);
    }
  }
  $config->cc_input_dir($cc_input_dir);
  
  # Native class source file
  my $native_class_source_file;
  my $native_class_rel_file;
  if (defined $cc_input_dir && defined $native_class_ext) {
    $native_class_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_class_ext);
    $native_class_source_file = "$cc_input_dir/$native_class_rel_file";
  }
  
  my $need_native_class_file;
  if ($native_class_source_file) {
    if (defined $config->is_resource) {
      if ($config->is_resource) {
        $need_native_class_file = 0;
      }
      else {
        if ($config->config_global && $class_name eq $config->config_global->class_name) {
          $need_native_class_file = 0;
        }
        else {
          $need_native_class_file = 1;
        }
      }
    }
    else {
      $need_native_class_file = 1;
    }
  }
  else {
    $need_native_class_file = 0;
  }
  
  if ($need_native_class_file) {
    unless (-f $native_class_source_file) {
      Carp::cluck("[Warning]Can't find native class source file $native_class_source_file. If this class is a resource class, set is_resource field to 1 to suppress this warning.");
    }
  }
  
  my $is_resource;
  if (defined $config->is_resource) {
    $is_resource = $config->is_resource;
  }
  else {
    $is_resource = !(defined $native_class_source_file && -f $native_class_source_file);
  }
  
  # For executable files, the resources are compiled in the executable's configuration file, so we don't compile them here.
  my $is_compile_native_source_files;
  if ($is_resource) {
    if ($config->config_global) {
      if ($class_name eq $config->config_global->class_name) {
        $is_compile_native_source_files = 1;
      }
      else {
        $is_compile_native_source_files = 0;
      }
    }
    else {
      $is_compile_native_source_files = 1;
    }
  }
  else {
    $is_compile_native_source_files = 1;
  }
  
  # Native source files
  my $native_source_rel_dir = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
  $native_source_rel_dir .= '/src';

  my $native_src_dir = $config->native_src_dir;
  my $native_source_files = [];
    my $native_source_files_base = $config->source_files;
  if ($is_compile_native_source_files) {
    $native_source_files = [map { "$native_src_dir/$_" } @$native_source_files_base ];
  }
  
  # Compile source files
  my $is_native_class_source_file = 1;
  my @source_file_infos;
  if ($native_class_source_file) {
    push @source_file_infos, {is_native_class_source_file => 1, source_rel_file => $native_class_rel_file};
  }
  if ($is_compile_native_source_files) {
    push @source_file_infos, map { {source_rel_file => SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, "native/src/$_")} } @$native_source_files_base;
  }
  
  for my $source_file_info (@source_file_infos) {
    
    my $current_is_native_class_source_file = $source_file_info->{is_native_class_source_file};
    my $source_rel_file = $source_file_info->{source_rel_file};
    my $source_file = "$cc_input_dir/$source_rel_file";
    
    next unless defined $source_file && -f $source_file;
    
    # Check if object file need to be generated
    my $native_include_dir = $config->native_include_dir;
    
    # Resource include directories
    my @resource_naitve_include_dirs;
    my $resource_names = $config->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      my $resource_config = $resource->config;
      
      my $resource_native_include_dir = $resource_config->native_include_dir;
      push @resource_naitve_include_dirs, $resource_native_include_dir;
    }
    
    my $compile_info_category;
    if ($category eq 'precompile') {
      $compile_info_category = 'precompile_class';
    }
    elsif ($category eq 'native') {
      if ($current_is_native_class_source_file) {
        $compile_info_category = 'native_class';
      }
      else {
        $compile_info_category = 'native_source';
      }
    }
    
    my $builder_dir = SPVM::Builder::Util::get_builder_dir;
    my $builder_include_dir = "$builder_dir/include";
    
    unless (-d $builder_include_dir) {
      confess("[Unexpected Error]$builder_include_dir must exist");
    }
    
    my $compile_info = SPVM::Builder::CompileInfo->new(
      source_file => $source_file,
      source_rel_file => $source_rel_file,
      config => $config,
      category => $compile_info_category,
      dependent_files => [$source_file, $native_include_dir, @resource_naitve_include_dirs, $builder_include_dir],
    );
    
    # Object file information
    my $compile_info_cc = $compile_info->{cc};
    my $compile_info_ccflags = $compile_info->{ccflags};
    
    # Add object file information
    push @$compile_infos, $compile_info;
  }
  
  return $compile_infos;
}

sub generate_precompile_class_source_file {
  my ($self, $class_name, $config) = @_;
  
  my $runtime = $self->runtime;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $basic_type->get_class_file;
  
  my $precompile_source = $basic_type->build_precompile_class_source($basic_type);
  
  # Force
  my $force = $self->detect_force($config);
  
  # Output - Precompile C source file
  my $cc_input_dir = $config->cc_input_dir;
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$cc_input_dir/$source_rel_file";
  
  # Generate precompile C source file
  mkpath dirname $source_file;
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  
  binmode $fh;
  print $fh $precompile_source;
  close $fh;
}

sub prepare_compile_source_file {
  my ($self, $compile_info) = @_;
  
  my $config = $compile_info->config;
  
  my $source_rel_file = $compile_info->source_rel_file;
  
  unless (defined $source_rel_file) {
    confess("\$source_rel_file must be defined.");
  }
  
  my $cc_input_dir = $config->cc_input_dir // $config->get_base_dir;
  
  my $source_file = $compile_info->source_file;
  
  my $before_compile_cbs = $config->before_compile_cbs;
  for my $before_compile_cb (@$before_compile_cbs) {
    $before_compile_cb->($compile_info->config, $compile_info);
  }
  
  my $config_global = $config->config_global;
  
  if ($config_global) {
    for my $before_compile_cb (@{$config_global->before_compile_cbs}) {
      $before_compile_cb->($compile_info->config, $compile_info);
    }
  }
  
  my $cc_version = $config->cc_version;
  
  my $cc_cmd_no_output_option = $compile_info->create_command({no_output_option => 1});
  my $cc_cmd_string_no_output_option = "@$cc_cmd_no_output_option";
  
  my $dependent_files = $compile_info->dependent_files;
  my $ninja = $self->builder->ninja;
  unless (defined $source_file && -f $source_file) {
    confess("source_file \"$source_file\" must be defined and exist.");
  }
  my $create_command_hash_options = {
    command => $cc_cmd_string_no_output_option,
    command_version => $cc_version,
    dependent_files => [$source_file, @$dependent_files],
  };
  
  # Get command hash
  my $command_hash = $ninja->create_command_hash($create_command_hash_options);
  
  # Split hash into directory and filename (e.g., abcdef... -> ab/cdef...)
  my $hash_dir = $command_hash;
  $hash_dir =~ s/^(..)/$1\//;

  # Build output file path
  my $object_rel_file = $source_rel_file;
  $object_rel_file =~ s/\.[^\.]+$/.o/;
  my $cc_output_dir = $self->builder->create_build_object_path;

  # Final output path: [build_dir]/[ab/hash_rest]/[source].o
  my $output_file = "$cc_output_dir/$hash_dir/$object_rel_file";

  # Set output file
  $compile_info->output_file($output_file);
  
  $compile_info->command_hash($command_hash);
  
  return $compile_info;
}

sub spawn_compile_source_file {
  my ($self, $compile_info) = @_;
  
  my $config = $compile_info->config;
  
  my $force = $self->detect_force($config);
  
  my $quiet = $self->detect_quiet($config);
  
  my $command_hash = $compile_info->command_hash;
  
  my $output_file = $compile_info->output_file;
  
  my $ninja = $self->builder->ninja;
  
  my $need_generate_options = {
    command_hash => $compile_info->command_hash,
    output_file => $compile_info->output_file,
  };
  my $need_generate = $force || $ninja->need_generate($need_generate_options);
  
  my $process_id = 0;
  if ($need_generate) {
    mkpath dirname $output_file;
    
    my $cc_cmd_heading;
    
    my $compile_info_category = $compile_info->category;
    if ($config->is_resource) {
      my $resource_class_name = $config->class_name;
      $cc_cmd_heading = "[Compile a source file in $resource_class_name resource.";
    }
    else {
      my $config_class_name = $config->class_name;
      my $config_file = $config->file;
      
      if ($compile_info_category eq 'bootstrap') {
        $cc_cmd_heading = "[Compile Bootstrap File]";
      }
      elsif ($compile_info_category eq 'spvm_core') {
        $cc_cmd_heading = "[Compile SPVM Source File]";
      }
      elsif ($compile_info_category eq 'native_source') {
        $cc_cmd_heading = "[Compile Native Source File for $config_class_name class using the config file '$config_file']";
      }
      elsif ($compile_info_category eq 'native_class') {
        $cc_cmd_heading = "[Compile Native Class File for $config_class_name class using the config file '$config_file']";
      }
      elsif ($compile_info_category eq 'precompile_class') {
        $cc_cmd_heading = "[Compile Precompile Class File for $config_class_name class]";
      }
      else {
        confess("[Unexpected Error]Invalid compile info category '$compile_info_category'.");
      }
    }
    
    # Prepare command for intermediate Perl process
    my $command_tmp_dir = File::Temp->newdir;
    my $cc_cmd = $compile_info->create_command;
    my $cc_cmd_string = $compile_info->create_command_string;
    
    my $start_time = int(Time::HiRes::time() * 1000);
    $compile_info->start_time($start_time);
    $compile_info->tmp_dir($command_tmp_dir);
    
    $process_id = &spawn_compile($output_file, $command_tmp_dir, $cc_cmd_heading, $cc_cmd_string, @$cc_cmd);
    $compile_info->process_id($process_id);
  }
  
  return $process_id;
}

sub wait_command {
  my ($self, $command_info) = @_;
  
  my $process_id = $command_info->process_id;
  
  # Wait for completion
  my $wait_process_id = waitpid($process_id, WNOHANG);
  
  if ($wait_process_id == 0) {
    return 0;
  }
  
  if ($wait_process_id == -1) {
    confess("[Unexpected Error]Failed to wait.\n" .
      "Reason: Process not found or already reaped: $!");
  }
  
  my $exit_status = $? >> 8;
  
  my $command_string = $command_info->create_command_string;
  my $output_file = $command_info->output_file;
  my $command_tmp_dir = $command_info->tmp_dir;
  my $config = $command_info->config;
  my $quiet = $config->quiet;
  
  # Check output file
  unless (-f $output_file) {
    confess("[Unexpected Error]The output file '$output_file' does not exist.");
  }
  
  # Read output files from temp directory
  my $stdout_file = "$command_tmp_dir/stdout.log";
  unless (-f $stdout_file) {
    confess("[Unexpected Error]The stdout log file '$stdout_file' does not exist.");
  }
  
  my $stderr_file = "$command_tmp_dir/stderr.log";
  unless (-f $stderr_file) {
    confess("[Unexpected Error]The stderr log file '$stderr_file' does not exist.");
  }
  
  # Print stdout
  unless ($quiet) {
    open my $stdout_fh, '<', $stdout_file;
    my $stdout_output = do { local $/; <$stdout_fh> };
    close $stdout_fh;
    if (length $stdout_output) {
      print $stdout_output;
    }
  }
  
  # Print stderr
  open my $stderr_fh, '<', $stderr_file;
  my $stderr_output = do { local $/; <$stderr_fh> };
  close $stderr_fh;
  if (length $stderr_output) {
    print STDERR $stderr_output;
  }
  
  # Check exit status
  if ($exit_status != 0) {
    confess("Command failed.\n" .
      "Command: $command_string\n" .
      "Exit status: $exit_status\n");
  }
  
  return $wait_process_id;
}

sub add_ninja_log {
  my ($self, $command_info) = @_;
  
  my $output_file = $command_info->output_file;
  my $command_hash = $command_info->command_hash;
  my $start_time = $command_info->start_time;
  my $builder = $self->builder;
  my $ninja = $builder->ninja;
  
  # Set end_time to command_info
  my $end_time = int(Time::HiRes::time() * 1000);
  $command_info->end_time($end_time);
  
  # Get mtime of the output file
  my $mtime = int((Time::HiRes::stat $output_file)[9] * 1000);
  
  my $log_entry = {
    output_file  => $output_file,
    command_hash => $command_hash,
    start_time   => $start_time,
    end_time     => $end_time,
    mtime        => $mtime,
  };
  
  $ninja->add_log($log_entry);
}

sub spawn_compile {
  my ($output_file, $command_tmp_dir, $cc_cmd_heading, $cc_cmd_string, @cc_cmd) = @_;
  
  my $compile_script_path = &get_compile_script_path();
  
  my $process_id = &spawn_perl($compile_script_path, $output_file, $command_tmp_dir, $cc_cmd_heading, $cc_cmd_string, @cc_cmd);
  
  return $process_id;
}

sub spawn_perl {
  my ($perl_script_file, @args) = @_;
  
  my @cmd = ($^X, $perl_script_file, @args);
  
  my $process_id;
  if ($^O eq 'MSWin32') {
    # Windows spawn
    $process_id = system(1, @cmd);
    if (!defined $process_id || $process_id <= 0) {
      confess("Failed to spawn Windows process for executing a perl script: $!");
    }
  }
  else {
    # Linux/Unix fork
    $process_id = fork();
    if (!defined $process_id) {
      confess("Failed to fork for executing a perl script: $!");
    }
    
    # Child process
    if ($process_id == 0) {
      exec(@cmd);
      exit(1);
    }
  }
  
  return $process_id;
}

# Compile a source files
sub compile_source_files {
  my ($self, $class_name, $compile_infos) = @_;
  
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  if (ref $class_name) {
    confess("[Unexpected Error]A class name must be non-reference.");
  }
  
  unless (@$compile_infos) {
    return;
  }
  
  for my $compile_info (@$compile_infos) {
    if ($compile_info) {
      my $compile_info = $self->prepare_compile_source_file($compile_info);
      my $process_id = $self->spawn_compile_source_file($compile_info);
      if ($process_id > 0) {
        while ($self->wait_command($compile_info) == 0) {
          Time::HiRes::sleep(0.01);
        }
        
        # Record the build result after the process finished
        $self->add_ninja_log($compile_info);
      }
    }
  }
}

sub prepare_link {
  my ($self, $class_name, $object_files, $config) = @_;
  
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  if (ref $class_name) {
    confess("[Unexpected Error]A class name must be non-reference.");
  }
  
  unless ($config) {
    confess("[Unexpected Error]A config must be defined.");
  }
  
  unless ($object_files) {
    return;
  }
  
  my $link_info = $self->create_link_info($class_name, $object_files, $config);
  
  my $runtime = $self->runtime;
  
  my $build_dir = $self->builder->build_dir;
  
  unless (defined $build_dir) {
    confess("[Unexpected Error]A build directory must be defined.");
  }
  
  unless (-d $build_dir) {
    confess("[Unexpected Error]A build directory must exists.");
  }
  
  my $category = $config->category;
  
  my $output_file = $config->output_file;
  
  my @object_files = map { "$_" } @{$link_info->object_files};
  
  unless ($config->isa('SPVM::Builder::Config::Linker')) {
    confess("[Unexpected Error]The config must be an SPVM::Builder::Config object");
  }
  
  my $hint_cc = $config->hint_cc;
  my $ld = $config->ld;
  
  my $quiet = $self->detect_quiet($config);
  
  my $link_info_output_file = $config->output_file;
  
  my $link_info_object_files = $link_info->object_files;
  
  my $object_file_names = [map { $_->to_string; } @$link_info_object_files];
  
  my $output_type = $config->output_type;
  
  my $before_link_cbs = $config->before_link_cbs;
  for my $before_link_cb (@$before_link_cbs) {
    $before_link_cb->($link_info->config, $link_info);
  }
  
  my $ld_version = $config->ld_version;
  
  my $force = $self->detect_force($config);
  
  my $ld_cmd_no_output_option = $link_info->create_command({no_output_option => 1});
  my $ld_cmd_string_no_output_option = "@$ld_cmd_no_output_option";
  
  my $ninja = $self->builder->ninja;
  my $create_command_hash_options = {
    command => $ld_cmd_string_no_output_option,
    command_version => $ld_version,
    dependent_files => [@object_files],
  };
  my $command_hash = $ninja->create_command_hash($create_command_hash_options);
  
  $link_info->command_hash($command_hash);
  $link_info->output_file($output_file);
  $link_info->config($config);
  
  if ($output_type eq 'dynamic_lib') {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    # Get normal methods
    my $method_names = $basic_type->get_method_names_by_category($category);
    
    # Create the dynamic link function list for the class
    my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, {category => $category});
    
    # Get anon methods from anon basic types
    my $anon_basic_type_names = $basic_type->get_anon_basic_type_names;
    for my $anon_basic_type_name (@$anon_basic_type_names) {
      my $anon_basic_type = $runtime->get_basic_type_by_name($anon_basic_type_name);
      my $anon_method_names = $anon_basic_type->get_method_names_by_category($category);
      
      # Create the dynamic link function list for each anon class and merge it
      my $anon_dl_func_list = SPVM::Builder::Util::create_dl_func_list($anon_basic_type_name, $anon_method_names, {category => $category});
      push @$dl_func_list, @$anon_dl_func_list;
    }
    $link_info->dl_func_list($dl_func_list);
  }
  
  return $link_info;
}

sub link {
  my ($self, $link_info) = @_;
  
  my $object_files = $link_info->object_files;
  
  unless (@$object_files) {
    confess("[Unexpected Error]Object files must be at least one.");
  }
  
  my $config = $link_info->config;
  my $force = $self->detect_force($config);;
  my $quiet = $self->detect_quiet($config);;
  my $hint_cc = $config->hint_cc;
  my $ld = $config->ld;
  my $output_type = $config->output_type;
  my $category = $config->category;
  my $class_name = $config->class_name;
  
  my $command_hash = $link_info->command_hash;
  my $output_file = $link_info->output_file;
  my $dl_func_list = $link_info->dl_func_list;
  
  my $ld_cmd = $link_info->create_command;
  my $ld_cmd_string = $link_info->create_command_string;
  
  my $link_info_object_files = $link_info->object_files;
  
  my $object_file_names = [map { $_->to_string; } @$link_info_object_files];
  
  my $ninja = $self->builder->ninja;
  
  mkpath dirname $output_file;
  
  # Create a dynamic library
  my $ld_cmd_heading;
  my $link_method;
  my $cbuilder_output_option_name;
  if ($output_type eq 'dynamic_lib') {
    $ld_cmd_heading = "[Generate Dynamic Link Library for $class_name class" . ($category eq 'precompile' ? ' for precompile' : '') . "]";
    $link_method = 'link';
    $cbuilder_output_option_name = 'lib_file';
  }
  # Create an executable file
  elsif ($output_type eq 'exe') {
    $ld_cmd_heading = "[Generate Executable File \"$output_file\"]\n";
    $link_method = 'link_executable';
    $cbuilder_output_option_name = 'exe_file';
  }
  else {
    confess("Unknown output_type \"$output_type\"");
  }
  
  my $need_generate_options = {
    command_hash => $link_info->command_hash,
    output_file => $link_info->output_file,
  };
  my $need_generate = $force || $self->builder->ninja->need_generate($need_generate_options);
  
  if ($need_generate) {
    
    my $start_time = int(Time::HiRes::time() * 1000);
    
    unless ($quiet) {
      print "$ld_cmd_heading\n";
      print "$ld_cmd_string\n";
    }
    
    # Load ExtUtils::CBuilder only when linking is needed for performance
    require ExtUtils::CBuilder;
    my $cbuilder_config = {
      cc => $hint_cc,
      ld => $ld,
      lddlflags => '',
      shrpenv => '',
      libpth => '',
      libperl => '',
      # On Windows/gcc(MinGW) "perllibs" should be empty string, but ExtUtils::CBuiler outputs "INPUT()" into 
      # Linker Script File(.lds) when "perllibs" is empty string.
      # This is syntax error in Linker Script File(.lds)
      # For the reason, libm is linked which seems to have no effect.
      perllibs => '-lm',
    };
    
    my $cbuilder = ExtUtils::CBuilder->new(quiet => 1, config => $cbuilder_config);
    
    my @link_tmp_files;
    my $link_info_ldflags = $link_info->create_ldflags;
    
    (undef, @link_tmp_files) = $cbuilder->$link_method(
      $cbuilder_output_option_name => $output_file,
      objects => $object_file_names,
      extra_linker_flags => "@$link_info_ldflags",
      module_name => $class_name,
      dl_func_list => $dl_func_list,
    );
    
    if ($self->debug) {
      if ($^O eq 'MSWin32') {
        my $def_file;
        my $lds_file;
        for my $tmp_file (@link_tmp_files) {
          # Remove double quote
          $tmp_file =~ s/^"//;
          $tmp_file =~ s/"$//;
          
          if ($tmp_file =~ /\.def$/) {
            $def_file = $tmp_file;
            $lds_file = $def_file;
            $lds_file =~ s/\.def$/.lds/;
            last;
          }
        }
        if (defined $def_file && -f $def_file) {
          my $def_content = SPVM::Builder::Util::slurp_binary($def_file);
          print "[$def_file]\n$def_content\n";
        }
        if (defined $lds_file && -f $lds_file) {
          my $lds_content = SPVM::Builder::Util::slurp_binary($lds_file);
          print "[$lds_file]\n$lds_content\n";
        }
      }
    }
    
    my $end_time = int(Time::HiRes::time() * 1000);
    
    unless (-f $output_file) {
      confess("The output file '$output_file' does not exist.");
    }
    
    my $mtime = int((Time::HiRes::stat $output_file)[9] * 1000);
    
    my $log_entry = {
      output_file  => $output_file,
      command_hash => $command_hash,
      start_time   => $start_time,
      end_time     => $end_time,
      mtime => $mtime,
    };
    $ninja->add_log($log_entry);
  }
  
  # after_link_cbs
  my $after_link_cbs = $config->after_link_cbs;
  for my $after_link_cb (@$after_link_cbs) {
    $after_link_cb->($link_info->config, $link_info);
  }
  
  return $output_file;
}

sub spawn_link {
  my (@args) = @_;
  
  my $link_script_path = &get_link_script_path();
  
  my $process_id = &spawn_perl($link_script_path, @args);
  
  return $process_id;
}

sub create_link_info {
  my ($self, $class_name, $object_files, $config) = @_;
  
  my $category = $config->category;
  
  my $output_file = $config->output_file;
  
  my $output_dir = $config->output_dir;
  
  my $build_dir = $self->builder->build_dir;
  
  my $ld = $config->ld;
  
  my $output_type = $config->output_type;
  
  # Output file
  unless (defined $output_file) {
    unless (defined $output_dir) {
      my $is_jit = $config->is_jit;
      if ($is_jit) {
        $output_dir = $self->builder->create_build_lib_path;
      }
      else {
        confess("[Unexpected Error]A output directory must exists.");
      }
    }
    
    my $output_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category);
    $output_file = "$output_dir/$output_rel_file";
  }
  
  # Output file extension
  my $output_file_base = basename $output_file;
  if ($output_file_base =~ /\.precompile$/ || $output_file_base !~ /\./) {
    my $exe_ext;
    
    if ($output_type eq 'dynamic_lib') {
      $exe_ext = ".$Config{dlext}"
    }
    elsif ($output_type eq 'exe') {
      $exe_ext = $Config{exe_ext};
    }
    
    $output_file .= $exe_ext;
  }
  
  $config->output_file($output_file);
  
  my $link_info = SPVM::Builder::LinkInfo->new(
    class_name => $class_name,
    config => $config,
    object_files => $object_files,
  );
  
  return $link_info;
}

sub get_compile_script_path {
  
  my $compile_script_path = dirname(__FILE__) . "/compile.pl";
  
  return $compile_script_path;
}

sub get_link_script_path {
  
  my $link_script_path = dirname(__FILE__) . "/link.pl";
  
  return $link_script_path;
}

1;

=head1 Name

SPVM::Builder::CC - Compilation and Link of Native Class

=head1 Description

The SPVM::Builder::CC class has methods to compile and link an SPVM native class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
