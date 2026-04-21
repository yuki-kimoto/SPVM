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

# Fields
has [qw(
  build_dir
  work_dir
  include_dirs
  ninja
  global_lock_fh
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
    include_dirs => \@INC,
    work_dir => 'work',
    @_
  };
  
  bless $self, ref $class || $class;
  
  my $build_dir = $self->build_dir;
  
  mkpath $build_dir;
  
  unless (exists $self->{ninja}) {
    $self->{ninja} = SPVM::Builder::Ninja->new(log_dir => $self->build_dir);
  }
  
  # Ensure the global lock file is opened once
  my $global_lock_file = $self->get_global_lock_file;
  
  # Open with append mode to avoid truncating existing data
  open my $global_lock_fh, '>>', $global_lock_file 
    or die "Can't open global lock file '$global_lock_file': $!";
  
  $self->{global_lock_fh} = $global_lock_fh;
  
  return $self;
}

# Instance Methods
sub build_dynamic_lib_dist_precompile {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  $options = {%$options, category => 'precompile'};
  
  $self->build_dynamic_lib_dist($class_name, $options);
}

sub build_dynamic_lib_dist_native {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  $options = {%$options, category => 'native'};
  
  $self->build_dynamic_lib_dist($class_name, $options);
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  $options = {%$options};
  
  # Ensure the category is set
  my $category = $options->{category};
  unless (defined $category) {
    confess("The category must be defined.");
  }

  # Wrap single class into the correct parallel key
  if ($category eq 'native') {
    $options->{native_classes} = [$class_name];
  }
  elsif ($category eq 'precompile') {
    $options->{precompile_classes} = [$class_name];
  }
  
  # Re-use the parallel version!
  $self->build_parallel_dynamic_lib_dist($options);
}

sub build_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  $options = {%$options};
  
  # Ensure the category is set
  my $category = $options->{category};
  unless (defined $category) {
    confess("The category must be defined.");
  }

  # Wrap single class into the correct parallel key
  if ($category eq 'native') {
    $options->{native_classes} = [$class_name];
  }
  elsif ($category eq 'precompile') {
    $options->{precompile_classes} = [$class_name];
  }
  
  # Re-use the parallel version!
  $self->build_parallel_dist($options);
}

sub build_jit {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  $options = {%$options};
  
  my $build_dir = $self->build_dir;
  
  $options->{is_jit} = 1;
  
  return $self->build($class_name, $options);
}

use JSON::PP ();

sub build {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $category = $options->{category};
  unless (defined $category) {
    confess("The category must be defined.");
  }
  
  # Create a copy and set the specific class key
  my $parallel_options = {%$options};
  if ($category eq 'native') {
    $parallel_options->{native_classes} = [$class_name];
  }
  elsif ($category eq 'precompile') {
    $parallel_options->{precompile_classes} = [$class_name];
  }
  
  # Call build_parallel
  my $output_files_h = $self->build_parallel($parallel_options);
  
  # Extract the output file path
  my $output_file = $output_files_h->{$category}{$class_name};
  
  return $output_file;
}

sub build_parallel {
  my ($self, $options) = @_;
  
  $options ||= {};
  
  # Allowed options (White list)
  my %allowed_options = map { $_ => 1 } qw(
    build_file
    native_classes
    precompile_classes
    jobs
    runtime
    is_jit
    output_dir
    category
    class_name
    class_file
    quiet
    optimize
  );

  # Check for invalid options
  for my $key (keys %$options) {
    unless ($allowed_options{$key}) {
      confess("Invalid option \"$key\" passed to build_parallel method.");
    }
  }
  
  my $output_files_h = {};
  
  my $cc_options = {builder => $self};
  
  if (exists $options->{jobs}) {
    $cc_options->{jobs} = $options->{jobs};
  }
  
  my $cc = SPVM::Builder::CC->new(%$cc_options);
  $cc->runtime($options->{runtime});

  my @all_compile_infos;
  my %class_to_context;

  # Define categories and their corresponding keys in $options
  my %category_to_key = (
    native     => 'native_classes',
    precompile => 'precompile_classes',
  );

  # Prepare all compile information
  for my $category (keys %category_to_key) {
    my $key = $category_to_key{$category};
    my $class_names = $options->{$key};
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
      $config->is_jit($options->{is_jit});
      $config->output_dir($options->{output_dir});
      
      my $force_optimize;
      if (length $options->{optimize}) {
        $force_optimize = $options->{optimize};
      }
      else {
        my $env_spvm_force_optimize = SPVM::Builder::Util::get_normalized_env('SPVM_FORCE_OPTIMIZE');
        if (length $env_spvm_force_optimize) {
          $force_optimize = $env_spvm_force_optimize;
        }
      }
      if (length $force_optimize) {
        $config->optimize($force_optimize);
      }
      
      # Prepare compile information for each class
      my $compile_infos = $cc->prepare_compile_class($class_name, $config);
      for my $compile_info (@$compile_infos) {
        $cc->finalize_compile_info($compile_info);
      }
      
      # Store information for the next steps
      push @all_compile_infos, @$compile_infos;
      $class_to_context{$category}{$class_name} = {
        config => $config,
        compile_infos => $compile_infos,
      };
    }
  }
  
  # Execute all compilations in parallel
  $cc->command_parallel(\@all_compile_infos);
  
  # Prepare all link information
  my @all_link_infos;
  for my $category (keys %class_to_context) {
    for my $class_name (keys %{$class_to_context{$category}}) {
      my $ctx = $class_to_context{$category}{$class_name};
      my $compile_infos = $ctx->{compile_infos};
      
      my $object_file_infos = [map { SPVM::Builder::ObjectFileInfo->new(compile_info => $_, file => $_->output_file) } @$compile_infos];
      unless (@$object_file_infos) {
        confess("[Unexpected Error]\$object_file_infos must have object files for $class_name.");
      }
      
      my $link_info = $cc->prepare_link($class_name, $object_file_infos, $ctx->{config});
      $ctx->{link_info} = $link_info;
      push @all_link_infos, $link_info;
    }
  }
  
  # Execute all links in parallel
  $cc->command_parallel(\@all_link_infos);
  
  # Finalize and collect output file paths
  for my $category (keys %class_to_context) {
    for my $class_name (keys %{$class_to_context{$category}}) {
      my $ctx = $class_to_context{$category}{$class_name};
      my $link_info = $ctx->{link_info};
      my $config = $ctx->{config};
      
      # Execute after_link_cbs
      my $after_link_cbs = $config->after_link_cbs;
      for my $after_link_cb (@$after_link_cbs) {
        $after_link_cb->($link_info->config, $link_info);
      }
      
      # Store result in the return hash
      $output_files_h->{$category}{$class_name} = $link_info->output_file;
    }
  }
  
  return $output_files_h;
}

sub build_parallel_dynamic_lib_dist {
  my ($self, $options) = @_;
  
  $options ||= {};
  $options = {%$options};
  
  $self->_resolve_options($options);
  
  # 1. Prepare runtime for all classes
  my $compiler = SPVM::Builder::Native::Compiler->new;
  for my $include_dir (@{$self->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  
  # Compile both native and precompile classes
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
  $options->{runtime} = $runtime;
  
  # 2. Call the parallel distribution build
  $self->build_parallel_dist($options);
}

sub build_parallel_dist {
  my ($self, $options) = @_;
  
  $options ||= {};
  $options = {%$options};
  
  # Distribution build settings (similar to build_dist)
  my $output_dir = 'blib/lib';
  $options->{output_dir} = $output_dir;
  
  # Execute parallel build
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

sub get_global_lock_file {
  my ($self) = @_;
  
  my $build_dir = $self->build_dir;
  
  my $global_lock_file = "$build_dir/.global.lock";
  
  return $global_lock_file;
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
