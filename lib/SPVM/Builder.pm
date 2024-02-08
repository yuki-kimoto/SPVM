package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use SPVM ();

use SPVM::Builder::CC;
use SPVM::Builder::Compiler;
use SPVM::Builder::Runtime;
use SPVM::Builder::Env;
use SPVM::Builder::Stack;

# Fields
sub build_dir {
  my $self = shift;
  if (@_) {
    $self->{build_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{build_dir};
  }
}

sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->{include_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs};
  }
}

sub new {
  my $class = shift;
  
  my $self = {
    include_dirs => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub build_dynamic_lib_dist_precompile {
  my ($self, $class_name) = @_;
  
  $self->build_dynamic_lib_dist($class_name, 'precompile');
}

sub build_dynamic_lib_dist_native {
  my ($self, $class_name) = @_;
  
  $self->build_dynamic_lib_dist($class_name, 'native');
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    include_dirs => $self->include_dirs
  );
  
  my $success = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->get_runtime;
  
  $self->build_dist($class_name, {runtime => $runtime, category => $category});
}

sub get_method_names {
  my ($runtime, $class_name, $category) = @_;
  
  my $method_names;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $method_names = $runtime->get_method_names($class_name, $category);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    if ($category eq 'native') {
      $method_names = $basic_type->_get_native_method_names;
    }
    elsif ($category eq 'precompile') {
      $method_names = $basic_type->_get_precompile_method_names;
    }
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $method_names;
}

sub build_precompile_class_source {
  my ($runtime, $class_name, $category) = @_;
  
  my $precompile_source;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $precompile_source = $runtime->build_precompile_class_source($class_name);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    $precompile_source = $runtime->build_precompile_class_source($basic_type)->to_string;
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $precompile_source;
}

sub build_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $runtime = $options->{runtime};
  
  my $category = $options->{category};
  
  my $class_file = $runtime->get_class_file($class_name);
  my $method_names = &get_method_names($runtime, $class_name, $category);
  my $precompile_source = &build_precompile_class_source($runtime, $class_name);
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, {category => $category});
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $cc = SPVM::Builder::CC->new(
      build_dir => $build_dir,
    );
    
    $cc->build_precompile_class_source_file(
      $class_name,
      {
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        class_file => $class_file,
      }
    );
  }
  elsif ($category eq 'native') {
    $build_src_dir = 'lib';
  }
  
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  my $build_lib_dir = 'blib/lib';
  
  my $compile_input_dir = $build_src_dir;
  my $compile_output_dir = $build_object_dir;
  my $link_output_dir = $build_lib_dir;
  
  $self->build(
    $class_name,
    {
      runtime => $runtime,
      compile_input_dir => $compile_input_dir,
      compile_output_dir => $compile_output_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      class_file => $class_file,
      dl_func_list => $dl_func_list,
    }
  );
}

sub build_at_runtime {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $category = $options->{category};
  
  my $build_dir = $self->build_dir;
  
  my $runtime = $options->{runtime};
  my $class_file = $options->{class_file};
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $method_names = &get_method_names($runtime, $class_name, $category);
  
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list(
    $class_name,
    $method_names,
    {category => $category}
  );
  
  my $precompile_source = &build_precompile_class_source($runtime, $class_name);
  
  # Build directory
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "The \"build_dir\" field must be defined to build a $category method at runtime. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
  }
  
  # Source directory
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $cc = SPVM::Builder::CC->new(
      build_dir => $build_dir,
      at_runtime => 1,
    );
    
    $cc->build_precompile_class_source_file(
      $class_name,
      {
        runtime => $runtime,
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        class_file => $class_file,
      }
    );
  }
  elsif ($category eq 'native') {
    my $class_file = $options->{class_file};
    $build_src_dir = SPVM::Builder::Util::remove_class_name_part_from_file($class_file, $class_name);
  }
  
  # Object directory
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  # Lib directory
  my $build_lib_dir = SPVM::Builder::Util::create_build_lib_path($build_dir);
  mkpath $build_lib_dir;
  
  my $build_file = $self->build(
    $class_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      class_file => $class_file,
      dl_func_list => $dl_func_list,
      at_runtime => 1,
    }
  );
  
  return $build_file;
}

sub build {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $at_runtime = $options->{at_runtime};
  my $cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    at_runtime => $at_runtime,
  );
  
  my $dl_func_list = $options->{dl_func_list};
  
  my $category = $options->{category};
  
  my $runtime = $options->{runtime};
  
  # Class file
  my $class_file = $options->{class_file};
  unless (defined $class_file) {
    my $config_file = SPVM::Builder::Util::get_config_file_from_class_name($class_name);
    if ($config_file) {
      $class_file = $config_file;
      $class_file =~ s/\.config$/\.spvm/;
    }
    else {
      confess "The class file \"$class_file\" is not found";
    }
  }
  
  my $config;
  if ($category eq 'native') {
    $config = $self->create_native_config_from_class_file($class_file);
  }
  elsif ($category eq 'precompile') {
    $config = SPVM::Builder::Util::API::create_default_config();
  }
  
  $config->class_name($class_name);
  
  $config->category($category);
  
  # Compile source file and create object files
  my $compile_options = {
    runtime => $runtime,
    input_dir => $options->{compile_input_dir},
    output_dir => $options->{compile_output_dir},
    config => $config,
  };
  
  my $object_files = $cc->compile_native_class($class_name, $compile_options);
  
  # Link object files and create dynamic library
  my $link_options = {
    runtime => $runtime,
    output_dir => $options->{link_output_dir},
    config => $config,
    dl_func_list => $dl_func_list,
  };
  
  my $output_file = $cc->link(
    $class_name,
    $object_files,
    $link_options
  );
  
  return $output_file;
}

sub create_native_config_from_class_file {
  my ($self, $class_file) = @_;
  
  my $config;
  my $config_file = $class_file;
  $config_file =~ s/\.spvm$/.config/;

  # Config file
  if (-f $config_file) {
    $config = SPVM::Builder::Config->load_config($config_file);
  }
  else {
    my $error = $self->_error_message_find_config($config_file);
    confess $error;
  }
  
  return $config;
}

sub _error_message_find_config {
  my ($self, $config_file) = @_;
  
  my $error = <<"EOS";
Can't find the native config file \"$config_file\".

The config file must contain at least the following code.
----------------------------------------------
use strict;
use warnings;

use SPVM::Builder::Config;
my \$config = SPVM::Builder::Config->new_gnu99(file => __FILE__);

\$config;
----------------------------------------------
EOS
  
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build Dynamic Libraries for SPVM Distribution

=head1 Description

The SPVM::Builder class has methods to build dynamic librares for a SPVM distribution.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
