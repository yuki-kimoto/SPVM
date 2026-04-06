package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use File::Path 'mkpath';

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

# Fields
has [qw(
  build_dir
  work_dir
  include_dirs
  ninja
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
    include_dirs => [map { "$_/SPVM" } @INC],
    work_dir => 'work',
    @_
  };
  
  bless $self, ref $class || $class;
  
  unless (exists $self->{ninja}) {
    $self->{ninja} = SPVM::Builder::Ninja->new(log_dir => $self->build_dir);
  }
  
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
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  
  for my $include_dir (@{$self->include_dirs}) {
    $compiler->add_include_dir($include_dir);
  }
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  eval { $compiler->compile($class_name); };
  if ($@) {
    Carp::confess(join("\n", @{$compiler->get_formatted_error_messages}));
  }
  my $runtime = $compiler->get_runtime;
  
  $options->{runtime} = $runtime;
  
  $self->build_dist($class_name, $options);
}

sub build_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  $options = {%$options};
  
  my $is_jit = 0;
  
  my $build_dir = $self->build_dir;
  
  my $output_dir = 'blib/lib';
  
  $options->{output_dir} = $output_dir;
  
  $self->build($class_name, $options);
}

sub build_jit {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  $options = {%$options};
  
  my $build_dir = $self->build_dir;
  
  $options->{is_jit} = 1;
  
  $self->build($class_name, $options);
}

sub build {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  # Ensure the category is defined
  my $category = $options->{category};
  unless (defined $category) {
    confess("The category must be defined.");
  }
  
  # Create a copy of options to include build_infos without modifying the original
  my $parallel_options = {%$options};
  $parallel_options->{build_infos} = {$category => [$class_name]};
  
  # Call build_parallel
  my $output_files_h = $self->build_parallel($parallel_options);
  
  # Extract the output file path
  my $output_file = $output_files_h->{$category}{$class_name};
  
  return $output_file;
}

sub build_parallel {
  my ($self, $options) = @_;
  
  $options ||= {};
  my $build_infos = $options->{build_infos};
  unless (defined $build_infos) {
    confess("The build_infos option must be defined.");
  }

  my $output_files_h = {};
  
  my $cc_options = {builder => $self};
  
  # Set force option
  if (exists $options->{force}) {
    $cc_options->{force} = $options->{force};
  }
  
  # Set jobs option
  if (exists $options->{jobs}) {
    $cc_options->{jobs} = $options->{jobs};
  }
  
  my $cc = SPVM::Builder::CC->new(%$cc_options);
  $cc->runtime($options->{runtime});

  my @all_compile_infos;
  my %class_to_context;

  # Prepare all compile information
  for my $category (keys %$build_infos) {
    my $class_names = $build_infos->{$category};
    
    for my $class_name (@$class_names) {
      my $config;
      if ($category eq 'native') {
        my $config_file = SPVM::Builder::Util::search_config_file($class_name);
        confess("A config file is not found for $class_name") unless defined $config_file;
        $config = SPVM::Builder::Config->load_config($config_file, []);
      }
      elsif ($category eq 'precompile') {
        $config = SPVM::Builder::Util::API::create_default_config();
      }
      
      $config->class_name($class_name);
      $config->category($category);
      $config->is_jit($options->{is_jit});
      $config->output_dir($options->{output_dir});
      $config->optimize($options->{optimize}) if defined $options->{optimize};
      
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
      
      my $object_files = [map { SPVM::Builder::ObjectFileInfo->new(compile_info => $_, file => $_->output_file) } @$compile_infos];
      unless (@$object_files) {
        confess("[Unexpected Error]\$object_files must have object files for $class_name.");
      }
      
      my $link_info = $cc->prepare_link($class_name, $object_files, $ctx->{config});
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

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build Dynamic Libraries for SPVM Distribution

=head1 Description

The SPVM::Builder class has methods to build dynamic librares for an SPVM distribution.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
