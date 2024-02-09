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
  
  $options = {%$options};
  
  my $build_dir = $self->build_dir;
  
  my $is_jit = $options->{is_jit};
  
  my $category = $options->{category};
  
  my $output_dir = $options->{output_dir};
  
  unless (defined $output_dir) {
    if ($is_jit) {
      $output_dir = SPVM::Builder::Util::create_build_lib_path($build_dir);
      mkpath $output_dir;
    }
  }
  
  # Config
  my $config;
  if ($category eq 'native') {
    my $config_file = SPVM::Builder::Util::search_config_file($class_name);
    
    unless (defined $config_file) {
      my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
      
      confess "A config file \"$config_rel_file\" is not found in (@INC)";
    }
    
    $config = SPVM::Builder::Config->load_config($config_file);
  }
  elsif ($category eq 'precompile') {
    $config = SPVM::Builder::Util::API::create_default_config();
  }
  
  $config->class_name($class_name);
  
  $config->category($category);
  
  $config->is_jit($is_jit);
  
  $config->output_dir($output_dir);
  
  my $runtime = $options->{runtime};
  
  my $cc_options = {build_dir => $build_dir};
  
  if (exists $options->{force}) {
    $cc_options->{force} = $options->{force};
  }
  
  my $cc = SPVM::Builder::CC->new(%$cc_options);
  
  my $compile_and_link_options = {config => $config, runtime => $runtime};
  
  # Compile source files to object files
  my $object_files = $cc->compile_class($class_name, $compile_and_link_options);
  
  # Link object files and generate a dynamic library
  my $output_file = $cc->link($class_name, $object_files, $compile_and_link_options);
  
  return $output_file;
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
