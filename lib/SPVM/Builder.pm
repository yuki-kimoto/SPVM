package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use File::Path 'mkpath';
use Fcntl ':flock';

use SPVM ();
use SPVM::Builder::CC;
use SPVM::Builder::Native::Compiler;
use SPVM::Builder::Util::API;
use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;
use SPVM::Builder::Accessor 'has';
use SPVM::Builder::Ninja;
use SPVM::Builder::ObjectFileInfo;
use SPVM::Builder::Config::Util;
use SPVM::Builder::Config::DLL;
use SPVM::Builder::LinkInfo;

use Carp 'confess';
use Config;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';
use Time::HiRes ();
use POSIX ":sys_wait_h";
use Time::HiRes;
use MIME::Base64 qw(encode_base64);
use Digest::SHA 'sha1_hex';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;
use SPVM::Builder::CompileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Native::BasicType;
use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  build_dir
  jobs
  
  quiet
  work_dir
  include_dirs
  runtime
  global_lock_fh
  ninja
  is_jit
  output_dir
  config_global_file
)];

sub import {
  my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
  unless (defined $build_dir) {
    my $build_tmp_dir = File::Temp->newdir(CLEANUP => 0);
    $SPVM::Global::BUILD_TMP_DIR = $build_tmp_dir;
    $ENV{SPVM_BUILD_DIR} = $build_tmp_dir->dirname;
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    build_dir => $ENV{SPVM_BUILD_DIR},
    jobs => SPVM::Builder::Util::API::get_cpu_count() + 2,
    include_dirs => \@INC,
    work_dir => 'work',
    @_
  };
  
  bless $self, ref $class || $class;
  
  my $build_dir = $self->build_dir;
  
  mkpath $build_dir;
  
  # Ensure the global lock file is opened once
  my $global_lock_file = $self->get_global_lock_file;
  
  # Open with append mode to avoid truncating existing data
  open my $global_lock_fh, '>>', $global_lock_file 
    or die "Can't open global lock file '$global_lock_file': $!";
  
  $self->{global_lock_fh} = $global_lock_fh;
  
  unless (exists $self->{ninja}) {
    $self->{ninja} = SPVM::Builder::Ninja->new(builder => $self);
  }
  
  return $self;
}

# Instance Methods
sub build_parallel {
  my ($self, $options) = @_;
  
  $options ||= {};
  
  # Allowed options (White list)
  my $option_names = [qw(
    native_classes
    precompile_classes
  )];
  
  SPVM::Builder::Util::check_option_names($options, $option_names);
  
  my $cc_options = {builder => $self};
  
  my $cc = SPVM::Builder::CC->new(%$cc_options);
  
  my $link_targets = [];
  
  my $config_global;
  if (defined (my $config_global_file = $self->config_global_file)) {
    $config_global = SPVM::Builder::Config::Util::load_config_global($config_global_file);
  }
  
  # Prepare all compile information
  my @categories = ('native', 'precompile');
  for my $category (@categories) {
    my $class_names = $options->{"${category}_classes"};
    next unless defined $class_names;
    
    for my $class_name (@$class_names) {
      my $config;
      if ($category eq 'native') {
        my $config_file = SPVM::Builder::Util::search_config_file($class_name);
        confess("A config file is not found for $class_name") unless defined $config_file;
        $config = SPVM::Builder::Config::Util::load_config($config_file);
      }
      elsif ($category eq 'precompile') {
        $config = SPVM::Builder::Util::API::create_default_config();
      }
      
      $config->class_name($class_name);
      $config->category($category);
      
      # Prepare compile information for each class
      my $compile_infos = $cc->prepare_compile_class($class_name, $config);
      for my $compile_info (@$compile_infos) {
        if ($config_global) {
          $compile_info->config->global($config_global);
        }
        
        my $env_spvm_force_build_type = SPVM::Builder::Util::get_normalized_env('SPVM_FORCE_BUILD_TYPE');
        if (length $env_spvm_force_build_type) {
          $compile_info->config->global->build_type($env_spvm_force_build_type);
        }
        
        $config->global->apply_build_rules($compile_info->config);
      }
      for my $compile_info (@$compile_infos) {
        $self->finalize_compile_info($compile_info);
      }
      
      push @$link_targets, {config => $config, compile_infos => $compile_infos};
    }
  }
  
  my @all_compile_infos = map { @{$_->{compile_infos}} } @$link_targets;
  
  # Execute all compilations in parallel
  $self->command_parallel(\@all_compile_infos);
  
  # Prepare all link information
  my @all_link_infos;
  for my $link_target (@$link_targets) {
    my $config = $link_target->{config};
    my $class_name = $config->class_name;
    my $compile_infos = $link_target->{compile_infos};
    
    my $object_file_infos = [map { SPVM::Builder::ObjectFileInfo->new(compile_info => $_, file => $_->output_file) } @$compile_infos];
    unless (@$object_file_infos) {
      confess("[Unexpected Error]\$object_file_infos must have object files for $class_name.");
    }
    
    my $link_info = $cc->prepare_link($class_name, $object_file_infos, $config);
    if ($config_global) {
      $config_global->apply_build_rules($link_info->config);
    }
    
    push @all_link_infos, $link_info;
  }
  
  # Execute all links in parallel
  $self->command_parallel(\@all_link_infos);
  
  # Execute after_link_cbs
  for my $link_info (@all_link_infos) {
    my $config = $link_info->config;
    my $after_link_cbs = $config->global->after_link_cbs;
    for my $after_link_cb (@$after_link_cbs) {
      $after_link_cb->($link_info);
    }
  }
  
  # Store result in the return hash
  my $output_files_h = {};
  for my $link_info (@all_link_infos) {
    my $config = $link_info->config;
    my $class_name = $config->class_name;
    my $category = $config->category;
    $output_files_h->{$category}{$class_name} = $link_info->output_file;
  }
  
  return $output_files_h;
}

sub build_parallel_dynamic_lib_dist {
  my ($self, $options) = @_;
  
  $options ||= {};
  $options = {%$options};
  
  $self->_resolve_options($options);
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  for my $include_dir (@{$self->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  
  my @all_classes;
  push @all_classes, @{$options->{native_classes}} if $options->{native_classes};
  push @all_classes, @{$options->{precompile_classes}} if $options->{precompile_classes};
  
  for my $class_name (@all_classes) {
    eval { $compiler->compile($class_name); };
    if ($@) {
      Carp::confess(join("\n", @{$compiler->get_formatted_error_messages}));
    }
  }
  
  my $runtime = $compiler->get_runtime;
  $self->runtime($runtime);
  
  $self->build_parallel($options);
}

sub create_build_work_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $work_dir = $self->work_dir;
  
  my $build_work_path = "$build_dir/$work_dir";
  if (defined $rel_file) {
    $build_work_path .= "/$rel_file";
  }
  
  return $build_work_path;
}

sub create_build_src_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $work_dir = $self->work_dir;
  
  my $build_src_path = "$build_dir/$work_dir/src";
  if (defined $rel_file) {
    $build_src_path .= "/$rel_file";
  }
  
  return $build_src_path;
}

sub create_build_include_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $work_dir = $self->work_dir;
  
  my $build_include_path = "$build_dir/$work_dir/include";
  if (defined $rel_file) {
    $build_include_path .= "/$rel_file";
  }
  
  return $build_include_path;
}

sub create_build_object_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $work_dir = $self->work_dir;
  
  my $build_output_path = "$build_dir/$work_dir/object";
  if (defined $rel_file) {
    $build_output_path .= "/$rel_file";
  }
  
  return $build_output_path;
}

sub create_build_lib_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $work_dir = $self->work_dir;
  
  my $build_lib_path = "$build_dir/$work_dir/lib";
  if (defined $rel_file) {
    $build_lib_path .= "/$rel_file";
  }
  
  return $build_lib_path;
}

sub _load_classes_from_file {
  my ($self, $file) = @_;

  # Open file for reading
  open my $fh, '<', $file or Carp::confess("Can't open classes file \"$file\": $!");
  
  # Read lines and remove newlines
  my @classes;
  while (my $line = <$fh>) {
    $line =~ s/[\r\n]//g;
    # Skip empty lines or comments
    next if $line =~ /^\s*$/ || $line =~ /^\s*#/;
    push @classes, $line;
  }
  close $fh;

  return \@classes;
}

sub _resolve_options {
  my ($self, $options) = @_;

  # Resolve native_classes_file (newline-separated text file)
  if (my $file = delete $options->{native_classes_file}) {
    my $classes = $self->_load_classes_from_file($file);
    push @{$options->{native_classes} ||= []}, @$classes;
  }

  # Resolve precompile_classes_file (newline-separated text file)
  if (my $file = delete $options->{precompile_classes_file}) {
    my $classes = $self->_load_classes_from_file($file);
    push @{$options->{precompile_classes} ||= []}, @$classes;
  }
}

sub global_file_lock {
  my ($self, $cb) = @_;
  
  my $lock_fh = $self->{global_lock_fh};
  
  # Wait for an exclusive lock (Blocking)
  flock($lock_fh, LOCK_EX) 
    or die "[Internal Error]Can't get exclusive lock on global lock file: $!";
  
  # Execute the callback and ensure unlock happens even on failure
  my $result;
  my $error;
  eval {
    $result = $cb->();
  };
  $error = $@;
  
  # Release the lock but keep the file handle for future reuse
  flock($lock_fh, LOCK_UN);
  
  # Rethrow if something went wrong inside the callback
  if ($error) {
    die $error;
  }
  
  return $result;
}

sub global_file_read_lock {
  my ($self, $cb) = @_;
  
  my $lock_fh = $self->{global_lock_fh};
  
  # Wait for an exclusive read lock (Blocking)
  flock($lock_fh, LOCK_SH) 
    or die "[Internal Error]Can't get exclusive lock on global lock file: $!";
  
  # Execute the callback and ensure unlock happens even on failure
  my $result;
  my $error;
  eval {
    $result = $cb->();
  };
  $error = $@;
  
  # Release the lock but keep the file handle for future reuse
  flock($lock_fh, LOCK_UN);
  
  # Rethrow if something went wrong inside the callback
  if ($error) {
    die $error;
  }
  
  return $result;
}

sub get_global_lock_file {
  my ($self) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $global_lock_file = "$build_dir/.global.lock";
  
  return $global_lock_file;
}

sub detect_quiet {
  my ($self, $config) = @_;
  
  my $quiet;
  
  if (length (my $env_spvm_force_quiet = SPVM::Builder::Util::get_normalized_env('SPVM_FORCE_QUIET'))) {
    $quiet = $env_spvm_force_quiet;
  }
  elsif (length $self->quiet) {
    $quiet = $self->quiet;
  }
  elsif (defined $config && length $config->{quiet}) {
    $quiet = $config->quiet;
  }
  elsif ($self->is_jit) {
    $quiet = 1;
  }
  else {
    $quiet = 0;
  }
  
  return $quiet;
}

sub command_parallel {
  my ($self, $command_infos) = @_;
  
  # Remove duplicate commands based on command_hash
  my @unique_command_infos;
  my %seen_command_hashes_h;
  for my $command_info (@$command_infos) {
    my $hash = $command_info->command_hash;
    unless ($seen_command_hashes_h{$hash}) {
      push @unique_command_infos, $command_info;
      $seen_command_hashes_h{$hash} = 1;
    }
  }
  
  my $max_jobs = $self->jobs;
  my @waiting_command_infos = @unique_command_infos;
  my %running_processes;
  my %errors_h;
  
  # Main loop for parallel processing
  while (@waiting_command_infos || %running_processes) {
    
    # Spawn new processes if slots are available
    while (@waiting_command_infos && keys %running_processes < $max_jobs) {
      my $command_info = shift @waiting_command_infos;
      my $spawn_method_name;
      
      if ($command_info->isa('SPVM::Builder::CompileInfo')) {
        $spawn_method_name = 'spawn_compile_source_file';
      }
      elsif ($command_info->isa('SPVM::Builder::LinkInfo')) {
        $spawn_method_name = 'spawn_link';
      }
      else {
        confess("[Unexpected Error]Invalid class")
      }
      
      my $process_id = $self->$spawn_method_name($command_info);
      
      if (defined $process_id && $process_id > 0) {
        $running_processes{$process_id} = $command_info;
      }
    }
    
    # Check status of running processes
    for my $process_id (keys %running_processes) {
      my $command_info = $running_processes{$process_id};
      
      # Check if the command has finished
      my $wait_command_status;
      eval {
        $wait_command_status = $self->wait_command($command_info);
      };
      
      my $error = $@;
      my $process_finished;
      if ($error) {
        $process_finished = 1;
        @waiting_command_infos = ();
        $max_jobs = 0;
        $errors_h{$process_id} = $error;
      }
      elsif ($wait_command_status != 0) {
        $process_finished = 1;
        $self->add_ninja_log($command_info);
      }
      
      if ($process_finished) {
        $command_info->process_id(undef);
        delete $running_processes{$process_id};
      }
    }
    
    if (!keys %running_processes && keys %errors_h) {
      my $errors_count = keys %errors_h;
      confess "$errors_count commands failed.";
    }
    
    # Sleep to reduce CPU usage if processes are still running
    if (%running_processes) {
      Time::HiRes::sleep(0.01);
    }
  }
}

sub spawn_link_command {
  my (@args) = @_;
  
  my $link_script_path = &get_link_script_path();
  
  my $process_id = &spawn_perl($link_script_path, @args);
  
  return $process_id;
}

sub spawn_link {
  my ($self, $link_info) = @_;
  
  my $config_global = $link_info->config->global;
  if ($config_global) {
    for my $before_link_cb (@{$config_global->before_link_cbs}) {
      $before_link_cb->($link_info);
    }
  }
  
  my $config = $link_info->config;
  
  my $object_file_infos = $link_info->object_file_infos;
  
  unless (@$object_file_infos) {
    confess("[Unexpected Error]Object files must be at least one.");
  }
  
  my $quiet = $self->detect_quiet($config);
  my $hint_cc = $config->hint_cc;
  my $ld = $config->ld;
  my $output_type = $config->output_type;
  my $category = $config->category;
  my $class_name = $config->class_name;
  
  my $command_hash = $link_info->command_hash;
  my $output_file = $link_info->output_file;
  my $dl_func_list = $link_info->dl_func_list;
  
  my $ld_cmd = $link_info->create_command;
  my $ld_command_string = $link_info->create_command_string;
  
  my $link_info_object_files = $link_info->object_file_infos;
  
  my $object_file_names = [map { $_->to_string; } @$link_info_object_files];
  
  my $ninja = $self->ninja;
  
  mkpath dirname $output_file;
  
  # Create a dynamic library
  my $ld_command_heading;
  my $link_method;
  my $cbuilder_output_option_name;
  if ($output_type eq 'dynamic_lib') {
    $ld_command_heading = "[Generate Dynamic Link Library for $class_name class" . ($category eq 'precompile' ? ' for precompile' : '') . "]";
    $link_method = 'link';
    $cbuilder_output_option_name = 'lib_file';
  }
  # Create an executable file
  elsif ($output_type eq 'exe') {
    $ld_command_heading = "[Generate Executable File \"$output_file\"]";
    $link_method = 'link_executable';
    $cbuilder_output_option_name = 'exe_file';
  }
  else {
    confess("Unknown output_type \"$output_type\"");
  }
  
  my $force = !!$ENV{SPVM_FORCE_BUILD};
  
  my $need_generate_options = {
    command_hash => $link_info->command_hash,
    output_file => $link_info->output_file,
  };
  my $need_generate = $self->ninja->need_generate($need_generate_options);
  
  my $process_id;
  if ($force || $need_generate) {
    mkpath dirname $output_file;
    
    # Prepare command for intermediate Perl process
    my $command_tmp_dir = File::Temp->newdir;
    
    my $start_time = int(Time::HiRes::time() * 1000);
    $link_info->start_time($start_time);
    $link_info->tmp_dir($command_tmp_dir);
    
    # Prepare arguments for link.pl
    my $dl_func_list_file = "$command_tmp_dir/dl_func_list.txt";
    if (defined $dl_func_list) {
      SPVM::Builder::Util::spurt_binary($dl_func_list_file, join("\n", @$dl_func_list), $self->global_lock_fh);
    }
    
    my $object_file_names_file = "$command_tmp_dir/object_file_names.txt";
    SPVM::Builder::Util::spurt_binary($object_file_names_file, join("\n", @$object_file_names), $self->global_lock_fh);
    
    my $ldflags_file = "$command_tmp_dir/ldflags.txt";
    my $link_info_ldflags = $link_info->create_ldflags;
    SPVM::Builder::Util::spurt_binary($ldflags_file, join("\n", @$link_info_ldflags), $self->global_lock_fh);
    
    # [Added] Generate lock file path using SHA1 of the normalized output file path
    my $build_dir = $self->build_dir;
    
    unless ($quiet) {
      $self->global_file_lock(sub {
        print STDERR "$ld_command_heading\n";
        print STDERR "$ld_command_string\n";
      });
    }
    
    # Isolate the internal DLL module name by prefixing it with a digest of the output absolute path to prevent symbol and memory collision on Windows.
    my $output_file_abs = File::Spec->rel2abs($output_file);
    my $module_name = sha1_hex($output_file_abs) . "::$class_name";
    
    # Spawn link process
    $process_id = &spawn_link_command(
      $command_tmp_dir,
      $output_file,
      $module_name,
      $hint_cc,
      $output_type,
      $ld,
      $dl_func_list_file,
      $object_file_names_file,
      $ldflags_file,
    );
    $link_info->process_id($process_id);
  }
  
  return $process_id;
}

sub spawn_compile_source_file {
  my ($self, $compile_info) = @_;
  
  my $config_global = $compile_info->config->global;
  if ($config_global) {
    for my $before_compile_cb (@{$config_global->before_compile_cbs}) {
      $before_compile_cb->($compile_info);
    }
  }
  
  my $config = $compile_info->config;
  
  my $quiet = $self->detect_quiet($config);
  
  my $command_hash = $compile_info->command_hash;
  
  my $output_file = $compile_info->output_file;
  
  my $ninja = $self->ninja;
  
  my $need_generate_options = {
    command_hash => $compile_info->command_hash,
    output_file => $compile_info->output_file,
  };
  
  my $force = !!$ENV{SPVM_FORCE_BUILD};
  my $need_generate = $ninja->need_generate($need_generate_options);
  
  my $process_id = 0;
  if ($force || $need_generate) {
    mkpath dirname $output_file;
    
    my $cc_command_heading;
    
    my $compile_info_category = $compile_info->category;
    if ($config->is_resource) {
      my $resource_class_name = $config->class_name;
      $cc_command_heading = "[Compile a source file in $resource_class_name resource.]";
    }
    else {
      my $config_class_name = $config->class_name;
      my $config_file = $config->file;
      
      if ($compile_info_category eq 'bootstrap') {
        $cc_command_heading = "[Compile Bootstrap File]";
      }
      elsif ($compile_info_category eq 'spvm_core') {
        $cc_command_heading = "[Compile SPVM Source File]";
      }
      elsif ($compile_info_category eq 'native_source') {
        $cc_command_heading = "[Compile Native Source File for $config_class_name class using the config file '$config_file']";
      }
      elsif ($compile_info_category eq 'native_class') {
        $cc_command_heading = "[Compile Native Class File for $config_class_name class using the config file '$config_file']";
      }
      elsif ($compile_info_category eq 'precompile_class') {
        $cc_command_heading = "[Compile Precompile Class File for $config_class_name class]";
      }
      else {
        confess("[Unexpected Error]Invalid compile info category '$compile_info_category'.");
      }
    }
    
    # Prepare command for intermediate Perl process
    my $command_tmp_dir = File::Temp->newdir;
    my $cc_cmd = $compile_info->create_command;
    my $cc_command_string = $compile_info->create_command_string;
    
    my $start_time = int(Time::HiRes::time() * 1000);
    $compile_info->start_time($start_time);
    $compile_info->tmp_dir($command_tmp_dir);
    
    unless ($quiet) {
      $self->global_file_lock(sub {
        print STDERR "$cc_command_heading\n";
        print STDERR "$cc_command_string\n";
      });
    }
    
    my $cc_cmd_no_output_option = $compile_info->create_command({no_output_option => 1});
    my $output_option_without_value = $config->create_option_short($config->cc_output_option_name, '');
    
    $process_id = &spawn_compile_command($command_tmp_dir, $output_file, @$cc_cmd_no_output_option, $output_option_without_value);
    $compile_info->process_id($process_id);
  }
  
  return $process_id;
}

sub add_ninja_log {
  my ($self, $command_info) = @_;
  
  my $output_file = $command_info->output_file;
  my $command_hash = $command_info->command_hash;
  my $start_time = $command_info->start_time;
  my $ninja = $self->ninja;
  
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

sub spawn_compile_command {
  my ($output_file, $command_tmp_dir, @cc_cmd) = @_;
  
  my $compile_script_path = &get_compile_script_path();
  
  my $process_id = &spawn_perl($compile_script_path, $output_file, $command_tmp_dir, @cc_cmd);
  
  return $process_id;
}

sub spawn_perl {
  my ($perl_script_file, @args) = @_;
  
  my $args_base64 = encode_base64(join("\0", @args), "");
  
  my @cmd = ($^X, $perl_script_file, $args_base64);
  
  my $process_id;
  if (SPVM::Builder::Util::is_windows()) {
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

sub get_compile_script_path {
  
  my $compile_script_path = dirname(__FILE__) . "/Builder/compile.pl";
  
  return $compile_script_path;
}

sub get_link_script_path {
  
  my $link_script_path = dirname(__FILE__) . "/Builder/link.pl";
  
  return $link_script_path;
}

sub wait_command {
  my ($self, $command_info) = @_;
  
  my $process_id = $command_info->process_id;
  
  # Wait for completion
  my $wait_process_id = waitpid($process_id, WNOHANG);
  
  my $exit_status = $? >> 8;
  
  my $command_string = $command_info->create_command_string;
  
  # Alive
  if ($wait_process_id == 0) {
    return 0;
  }
  # Error
  elsif ($wait_process_id == -1) {
    confess("The waited command failed. Process not found or already reaped: \$!=$!, , \$command_string='$command_string'");
  }
  
  my $command_tmp_dir = $command_info->tmp_dir;
  
  # Read output files from temp directory
  my $stdout_file = "$command_tmp_dir/stdout.log";
  my $stdout_output = SPVM::Builder::Util::slurp_binary($stdout_file);
  if (length $stdout_output) {
    $self->global_file_lock(sub {
      print $stdout_output;
    });
  }
  
  my $stderr_file = "$command_tmp_dir/stderr.log";
  my $stderr_output = SPVM::Builder::Util::slurp_binary($stderr_file);
  if (length $stderr_output) {
    $self->global_file_lock(sub {
      print STDERR $stderr_output;
    });
  }
  
  if ($ENV{SPVM_CC_DEBUG}) {
    opendir(my $command_tmp_dh, $command_tmp_dir)
      or confess("Can't open directory '$command_tmp_dir': $!");
    
    while (my $tmp_file = readdir($command_tmp_dh)) {
      next if $tmp_file eq 'stdout.log' || $tmp_file eq 'stderr.log';
      
      my $tmp_file_path = "$command_tmp_dir/$tmp_file";
      
      if (-f $tmp_file_path && -T $tmp_file_path) {
        my $tmp_content = SPVM::Builder::Util::slurp_binary($tmp_file_path);
        $self->global_file_lock(sub {
          print STDERR "[SPVM_CC_DEBUG]Content of '$tmp_file_path':\n$tmp_content\n";
        });
      }
    }
  }
  
  if ($exit_status != 0) {
    confess("The waited command failed. The command returned an error status code. \$exit_status=$exit_status, \$command_string='$command_string'");
  }
  
  # Check output file
  my $output_file = $command_info->output_file;
  unless (-f $output_file) {
    confess("[Unexpected Error]The output file '$output_file' does not exist.");
  }
  
  return $wait_process_id;
}

sub finalize_compile_info {
  my ($self, $compile_info) = @_;
  
  my $config = $compile_info->config;
  
  my $source_rel_file = $compile_info->source_rel_file;
  
  unless (defined $source_rel_file) {
    confess("\$source_rel_file must be defined.");
  }
  
  my $source_file = $compile_info->source_file;
  
  my $cc_version = $config->cc_version;
  
  my $cc_command_no_output_option = $compile_info->create_command({no_output_option => 1});
  my $cc_command_string_no_output_option = "@$cc_command_no_output_option";
  
  my $dependent_files = $compile_info->dependent_files;
  my $ninja = $self->ninja;
  unless (defined $source_file && -f $source_file) {
    confess("source_file \"$source_file\" must be defined and exist.");
  }
  my $create_command_hash_options = {
    command => $cc_command_string_no_output_option,
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
  my $cc_output_dir = $self->create_build_object_path;

  # Final output path: [build_dir]/[ab/hash_rest]/[source].o
  my $output_file = "$cc_output_dir/$hash_dir/$object_rel_file";

  # Set output file
  $compile_info->output_file($output_file);
  
  $compile_info->command_hash($command_hash);
}

sub prepare_compile_spvm_core_source_files {
  my ($self) = @_;
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  
  my $builder_dir = SPVM::Builder::Util::get_builder_dir();
  
  my $builder_src_dir = "$builder_dir/src";
  
  my $builder_include_dir = "$builder_dir/include";
  
  my $source_dir = $builder_dir;
  $source_dir =~ s|/SPVM/Builder$||;
  
  my $spvm_runtime_src_base_names = SPVM::Builder::Util::get_spvm_core_source_file_names();
  
  # Compile source files
  my $compile_infos = [];
  for my $spvm_runtime_src_base_name (@$spvm_runtime_src_base_names) {
    my $source_rel_file = "SPVM/Builder/src/$spvm_runtime_src_base_name";
    
    my $compile_info = SPVM::Builder::CompileInfo->new(
      source_dir => $source_dir,
      source_rel_file => $source_rel_file,
      config => $config,
      category => 'spvm_core',
      dependent_files => [$builder_include_dir],
    );
    
    push @$compile_infos, $compile_info;
  }
  
  return $compile_infos;
}

sub prepare_compile_precompile_class {
  my ($self, $class_name) = @_;
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  
  $config->category('precompile');
  
  my $builder_cc = SPVM::Builder::CC->new(
    builder => $self,
  );
  my $compile_infos = [];
  my $precompile_compile_infos = $builder_cc->prepare_compile_class($class_name, $config);
  push @$compile_infos, @$precompile_compile_infos;
  
  return $compile_infos;
}

sub prepare_compile_native_class {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  my $no_compile_resources = $options->{no_compile_resources};
  my $config_file = $options->{config_file} // SPVM::Builder::Util::search_config_file($class_name);
  
  my $all_compile_infos = [];
  
  if (defined $config_file && -f $config_file) {
    my $config = SPVM::Builder::Config::Util::load_config($config_file);
    my $builder_cc = SPVM::Builder::CC->new(
      builder => $self,
    );
    $builder_cc->no_compile_resources($no_compile_resources);
    my $compile_infos = $builder_cc->prepare_compile_class($class_name, $config);
    push @$all_compile_infos, @$compile_infos;
  }
  
  return $all_compile_infos;
}

sub prepare_compile_precompile_classes {
  my ($self, $class_names, $options) = @_;
  
  my $compile_infos = [];
  for my $class_name (@$class_names) {
    my $precompile_compile_infos = $self->prepare_compile_precompile_class($class_name, $options);
    push @$compile_infos, @$precompile_compile_infos;
  }
  
  return $compile_infos;
}

sub prepare_compile_native_classes {
  my ($self, $class_names, $options) = @_;
  
  my $compile_infos = [];
  for my $class_name (@$class_names) {
    my $native_compile_infos = $self->prepare_compile_native_class($class_name, $options);
    push @$compile_infos, @$native_compile_infos;
  }
  
  return $compile_infos;
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build Dynamic Libraries for SPVM Distribution

=head1 Description

The SPVM::Builder class has methods to build dynamic librares for an SPVM distribution.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
