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

sub class_paths {
  my $self = shift;
  if (@_) {
    $self->{class_paths} = $_[0];
    return $self;
  }
  else {
    return $self->{class_paths};
  }
}

sub new {
  my $class = shift;
  
  my $self = {
    class_paths => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    class_paths => $self->class_paths
  );
  
  my $success = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->build_runtime;
  my $class_file = $runtime->get_class_file($class_name);
  my $method_names = $runtime->get_method_names($class_name, $category);
  my $anon_class_names = $runtime->get_anon_class_names($class_name);
  my $precompile_source = $runtime->build_precompile_class_source($class_name);
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
  
  $self->build_dist($class_name, {category => $category, class_file => $class_file, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
}

sub build_dist {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
  );
  
  my $dl_func_list = $options->{dl_func_list};
  my $class_file = $options->{class_file};
  my $precompile_source = $options->{precompile_source};
  
  my $category = $options->{category};
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
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
  
  $cc->build(
    $class_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      class_file => $class_file,
      dl_func_list => $dl_func_list,
    }
  );
}

sub build_dynamic_lib_dist_precompile {
  my ($self, $class_name) = @_;
  
  $self->build_dynamic_lib_dist($class_name, 'precompile');
}

sub build_dynamic_lib_dist_native {
  my ($self, $class_name) = @_;
  
  $self->build_dynamic_lib_dist($class_name, 'native');
}

sub build_at_runtime {
  my ($self, $class_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    at_runtime => 1,
  );
  
  my $dl_func_list = $options->{dl_func_list};
  my $class_file = $options->{class_file};
  my $precompile_source = $options->{precompile_source};

  my $category = $options->{category};
  
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
    my $class_file = $options->{class_file};
    $build_src_dir = SPVM::Builder::Util::remove_class_part_from_file($class_file, $class_name);
  }
  
  # Object directory
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  # Lib directory
  my $build_lib_dir = SPVM::Builder::Util::create_build_lib_path($build_dir);
  mkpath $build_lib_dir;
  
  my $build_file = $cc->build(
    $class_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      class_file => $class_file,
      dl_func_list => $dl_func_list,
    }
  );
  
  return $build_file;
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
