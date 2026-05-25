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
use MIME::Base64 qw(encode_base64);
use Digest::SHA 'sha1_hex';

use SPVM ();

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;
use SPVM::Builder::CompileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Native::BasicType;
use SPVM::Builder::Native::Compiler;

use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  builder
  runtime
)];

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    @_
  };
  
  bless $self, $class;
  
  return $self;
}

# Instance Methods
sub prepare_compile_class {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  
  my $config = $options->{config};
  
  my $no_compile_resources = $options->{no_compile_resources};
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
  
  unless ($no_compile_resources) {
    my $resource_link_info = $self->prepare_compile_resources($class_name, {config => $config});
    my $resource_compile_infos = $resource_link_info->compile_infos;
    push @$compile_infos, @$resource_compile_infos;
  }
  
  my $native_link_info = $self->prepare_compile_class_common($class_name, {config => $config});
  my $native_compile_infos = $native_link_info->compile_infos;
  push @$compile_infos, @$native_compile_infos;
  
  my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => $compile_infos);
  
  return $link_info;
}

sub prepare_compile_precompile_class {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  
  my $config = SPVM::Builder::Util::API::create_default_config();
  
  $config->category('precompile');
  
  my $link_info = $self->prepare_compile_class($class_name, {%$options, config  => $config});
  
  return $link_info;
}

sub prepare_compile_native_class {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  my $config_file = $options->{config_file} // SPVM::Builder::Util::search_config_file($class_name);
  
  my $link_info;
  if (defined $config_file && -f $config_file) {
    my $config = SPVM::Builder::Config::Util::load_config($config_file);
    $config->category('native');
    $link_info = $self->prepare_compile_class($class_name, {%$options, config  => $config});
  }
  
  return $link_info;
}

sub prepare_compile_resources {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  
  my $config = $options->{config};
  
  my $compile_infos = [];
  
  my $resource_names = $config->get_resource_names;
  for my $resource_name (@$resource_names) {
    my $resource = $config->get_resource($resource_name);
    
    my $resource_class_name = $resource->class_name;
    my $resource_config = $resource->config;
    
    if (exists $config->{quiet}) {
      $resource_config->quiet($config->quiet);
    }
    
    my $resource_link_info = $self->prepare_compile_class($resource_class_name, {%$options, config  => $resource_config});
    my $resource_compile_infos = $resource_link_info->compile_infos;
    push @$compile_infos, @$resource_compile_infos;
  }
  
  my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => $compile_infos);
  
  return $link_info;
}

sub prepare_compile_class_common {
  my ($self, $class_name, $options) = @_;
  
  $options //= {};
  
  my $config = $options->{config};
  
  if ($config->is_resource && !$config->resource_loader_config) {
    my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => []);
    return $link_info;
  }
  
  my $is_cc_config = $config->isa('SPVM::Builder::Config') ? 1 : 0;
  unless ($is_cc_config) {
    my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => []);
    return $link_info;
  }
  
  my $runtime = $self->runtime;
  unless ($runtime) {
    confess("'runtime' field must be defined.");
  }
  
  my $native_class_ext = $config->ext;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  unless ($basic_type) {
    confess("Cannot find the basic type for '$class_name' class. Did you forgot to load the class?");
  }
  
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
      my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => []);
      return $link_info;
    }
  }
  
  my $compile_infos = [];
  
  my $source_dir;
  if ($category eq 'precompile') {
    my $class_file = $basic_type->get_class_file;
    
    my $precompile_source = $basic_type->build_precompile_class_source($basic_type);
    my $precompile_source_sha1 = sha1_hex $precompile_source;
    my $precompile_source_sha1_dir = $precompile_source_sha1 =~ s|^(..)|$1/|r;
    
    $source_dir = $self->builder->create_build_src_path($precompile_source_sha1_dir);
    
    # Output - Precompile C source file
    my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
    my $source_file = "$source_dir/$source_rel_file";
    
    # Generate precompile C source file
    SPVM::Builder::Util::spurt_binary($source_file, $precompile_source, $self->builder->global_lock_fh);
  }
  elsif ($category eq 'native') {
    if ($is_cc_config) {
      $source_dir = SPVM::Builder::Util::get_class_base_dir($class_file, $class_name);
    }
  }
  
  # Native class source file
  my $native_class_source_file;
  my $native_class_rel_file;
  if (defined $source_dir && defined $native_class_ext) {
    $native_class_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_class_ext);
    $native_class_source_file = "$source_dir/$native_class_rel_file";
  }
  
  my $need_native_class_file;
  my $is_resource = $config->is_resource;
  if ($native_class_source_file) {
    if ($is_resource) {
      $need_native_class_file = 0;
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
  
  # Native source files
  my $native_source_rel_dir = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
  $native_source_rel_dir .= '/src';

  my $native_src_dir = $config->native_src_dir;
  my $native_source_files = [];
  my $native_source_files_base = $config->source_files;
  $native_source_files = [map { "$native_src_dir/$_" } @$native_source_files_base ];
  
  # Compile source files
  my $is_native_class_source_file = 1;
  my @source_file_infos;
  if ($native_class_source_file) {
    push @source_file_infos, {is_native_class_source_file => 1, source_rel_file => $native_class_rel_file};
  }
  push @source_file_infos, map { {source_rel_file => SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, "native/src/$_")} } @$native_source_files_base;
  
  for my $source_file_info (@source_file_infos) {
    
    my $current_is_native_class_source_file = $source_file_info->{is_native_class_source_file};
    my $source_rel_file = $source_file_info->{source_rel_file};
    my $source_file = "$source_dir/$source_rel_file";
    
    next unless defined $source_file && -f $source_file;
    
    my @resource_include_dirs;
    my @resources;
    if ($config->is_resource) {
      my $resource_loader_config = $config->resource_loader_config;
      if ($resource_loader_config) {
        my $resource_names = $resource_loader_config->get_resource_names;
        for my $resource_name (@$resource_names) {
          my $resource = $resource_loader_config->get_resource($resource_name);
          push @resources, $resource;
        }
      }
    }
    else {
      my $resource_names = $config->get_resource_names;
      for my $resource_name (@$resource_names) {
        my $resource = $config->get_resource($resource_name);
        push @resources, $resource;
      }
    }
    for my $resource (@resources) {
      my $resource_config = $resource->config;
      
      my $resource_native_include_dir = $resource_config->native_include_dir;
      push @resource_include_dirs, $resource_native_include_dir;
    }
    
    $config->resource_include_dirs(\@resource_include_dirs);
    
    # Check if object file need to be generated
    my $native_include_dir = $config->native_include_dir;
    
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
      source_dir => $source_dir,
      source_rel_file => $source_rel_file,
      config => $config,
      category => $compile_info_category,
      dependent_files => [$source_file, $native_include_dir, @resource_include_dirs, $builder_include_dir],
    );
    
    # Object file information
    my $compile_info_cc = $compile_info->{cc};
    my $compile_info_ccflags = $compile_info->{ccflags};
    
    # Add object file information
    push @$compile_infos, $compile_info;
  }
  
  my $link_info = SPVM::Builder::LinkInfo->new(config => $config, compile_infos => $compile_infos);
  
  return $link_info;
}

sub resolve_dl_func_list {
  my ($self, $link_info) = @_;
  
  my $config = $link_info->config;
  
  my $class_name = $config->class_name;
  
  my $category = $config->category;
  
  if ($category eq 'native' || $category eq 'precompile') {
    my $runtime = $self->runtime;
    unless ($runtime) {
      confess("'runtime' field must be defined.");
    }
    
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
}

sub build_parallel {
  my ($self, $options) = @_;
  
  $options ||= {};
  
  # Allowed options (White list)
  my $option_names = [qw(
    native_classes
    precompile_classes
    config_global_file
  )];
  
  SPVM::Builder::Util::check_option_names($options, $option_names);
  
  my $link_infos = [];
  
  my $native_class_names = $options->{native_classes} // [];
  for my $class_name (@$native_class_names) {
    my $native_link_info = $self->prepare_compile_native_class($class_name);
    my $category = $native_link_info->config->category;
    my $diagnostic_message = "[Generate Dynamic Link Library:\$class_name='$class_name', \$category='$category']";
    $native_link_info->diagnostic_message($diagnostic_message);
    push @$link_infos, $native_link_info;
  }
  
  my $precompile_class_names = $options->{precompile_classes} // [];
  for my $class_name (@$precompile_class_names) {
    my $precompile_link_info = $self->prepare_compile_precompile_class($class_name);
    my $category = $precompile_link_info->config->category;
    my $diagnostic_message = "[Generate Dynamic Link Library:\$class_name='$class_name', \$category='$category']";
    $precompile_link_info->diagnostic_message($diagnostic_message);
    push @$link_infos, $precompile_link_info;
  }
  
  for my $link_info (@$link_infos) {
    $self->resolve_dl_func_list($link_info);
  }
  
  my $output_files_h = $self->builder->build_parallel_with_link_infos($link_infos, $options);
  
  return $output_files_h;
}

sub build_parallel_dynamic_lib_dist {
  my ($self, $options) = @_;
  
  my $builder = $self->builder;
  
  $options ||= {};
  $options = {%$options};
  
  $self->_resolve_options($options);
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
  for my $include_dir (@{$builder->include_dirs}) {
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

1;

=head1 Name

SPVM::Builder::CC - Compilation and Link of Native Class

=head1 Description

The SPVM::Builder::CC class has methods to compile and link an SPVM native class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
