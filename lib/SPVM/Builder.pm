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

# Instance Methods
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

sub build_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $at_runtime = 0;
  
  my $category = $options->{category};
  
  my $build_dir = $self->build_dir;
  
  my $runtime = $options->{runtime};
  
  my $output_dir = 'blib/lib';
  
  $self->build(
    $class_name,
    {
      runtime => $runtime,
      category => $category,
      at_runtime => $at_runtime,
      output_dir => $output_dir,
    }
  );
}

sub build_at_runtime {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $at_runtime = 1;
  
  my $category = $options->{category};
  
  my $build_dir = $self->build_dir;
  
  my $runtime = $options->{runtime};
  
  my $build_file = $self->build(
    $class_name,
    {
      runtime => $runtime,
      category => $category,
      at_runtime => $at_runtime,
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
  
  my $category = $options->{category};
  
  my $runtime = $options->{runtime};
  
  my $output_dir = $options->{output_dir};
  
  if ($at_runtime) {
    if (defined $build_dir) {
      mkpath $build_dir;
    }
    else {
      confess "The \"build_dir\" field must be defined to build a $category method at runtime. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
    }
  }
  
  my $class_file = &_runtime_get_class_file($runtime, $class_name);
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $cc = SPVM::Builder::CC->new(
      build_dir => $build_dir,
      at_runtime => $at_runtime,
    );
    
    $cc->build_precompile_class_source_file(
      $class_name,
      {
        runtime => $runtime,
        output_dir => $build_src_dir,
      }
    );
  }
  elsif ($category eq 'native') {
    $build_src_dir = SPVM::Builder::Util::remove_class_name_part_from_file($class_file, $class_name);
  }
  
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  unless (defined $output_dir) {
    if ($at_runtime) {
      $output_dir = SPVM::Builder::Util::create_build_lib_path($build_dir);
      mkpath $output_dir;
    }
    else {
      confess "The output_dir option is not defined.";
    }
  }
  
  my $input_dir = $build_src_dir;
  my $compile_output_dir = $build_object_dir;
  
  # Class file
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
    $config = _search_config($runtime, $class_name);
  }
  elsif ($category eq 'precompile') {
    $config = SPVM::Builder::Util::API::create_default_config();
  }
  
  $config->class_name($class_name);
  
  $config->category($category);
  
  # Compile source file and create object files
  my $compile_options = {
    runtime => $runtime,
    input_dir => $input_dir,
    output_dir => $compile_output_dir,
    config => $config,
  };
  
  my $object_files = $cc->compile_native_class($class_name, $compile_options);
  
  # Link object files and create dynamic library
  my $link_options = {
    runtime => $runtime,
    output_dir => $output_dir,
    config => $config,
  };
  
  my $output_file = $cc->link(
    $class_name,
    $object_files,
    $link_options
  );
  
  return $output_file;
}

sub _search_config {
  my ($runtime, $class_name) = @_;
  
  my $class_file = &_runtime_get_class_file($runtime, $class_name);
  
  my $config;
  my $config_file = $class_file;
  $config_file =~ s/\.spvm$/.config/;
  
  # Config file
  if (-f $config_file) {
    $config = SPVM::Builder::Config->load_config($config_file);
  }
  else {
    
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

    confess $error;
  }
  
  return $config;
}

sub _runtime_get_class_file {
  my ($runtime, $class_name, $category) = @_;
  
  my $class_file;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $class_file = $runtime->get_class_file($class_name, $category);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $spvm_class_dir = $basic_type->get_class_dir;
    
    my $spvm_class_rel_file = $basic_type->get_class_rel_file;
    
    $class_file = "$spvm_class_dir/$spvm_class_rel_file";
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $class_file;
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
