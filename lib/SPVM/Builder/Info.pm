package SPVM::Builder::Info;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config::Info;

use SPVM 'Native::Compiler';

# Fields
sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->builder->include_dirs($_[0]);
    return $self;
  }
  else {
    return $self->builder->include_dirs;
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

# Class Methods
sub new {
  my $class = shift;
  
  my %options = @_;
  
  my $include_dirs = delete $options{include_dirs};
  
  my $build_dir = delete $options{build_dir};
  
  my $self = bless {
    include_dirs => [],
    %options
  }, $class;
  
  my $class_name = $self->{class_name};
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  unless (defined $build_dir) {
    $build_dir = '.spvm_build';
  }
  
  my $builder = SPVM::Builder->new(
    build_dir => $build_dir,
    include_dirs => $include_dirs
  );
  
  $config->class_name($class_name);
  
  $self->{builder} = $builder;
  
  my $compiler = SPVM::Native::Compiler->new;
  $compiler->add_include_dir($_) for @{$builder->include_dirs};
  $self->{compiler} = $compiler;
  
  return $self;
}

# Instance Methods
sub get_required_resources {
  my ($self) = @_;
  
  my $config_exe = $self->config;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $required_resources = [];
  
  my $builder = $self->builder;
  
  my $build_dir = $self->builder->build_dir;
  
  my $builder_cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    quiet => $self->quiet,
    force => $self->force,
  );
  
  my $runtime = $self->runtime;
  
  my $class_names = $runtime->_get_user_defined_basic_type_names->to_strings;
  my $all_object_files = [];
  for my $class_name (@$class_names) {
    
    my $class = $runtime->get_basic_type_by_name($class_name);
    
    my $native_method_names = $class->_get_native_method_names;
    if (@$native_method_names) {
      my $class_file = $class->_get_class_file;
      
      unless (defined $class_file) {
        my $config_exe_file = SPVM::Builder::Util::search_config_file($class_name);
        if ($config_exe_file) {
          $class_file = $config_exe_file;
          $class_file =~ s/\.config$/\.spvm/;
        }
        else {
          confess("The class file \"$class_file\" is not found");
        }
      }
      
      my $config_file = SPVM::Builder::Util::search_config_file($class_name);
      
      unless ($class_name eq $self->class_name) {
        
        my $config_exe = SPVM::Builder::Config->load_config($config_file, []);
        
        my $resource_names = $config_exe->get_resource_names;
        for my $resource_name (@$resource_names) {
          my $resource = $config_exe->get_resource($resource_name);
          
          my $resource_info = {
            class_name => $class_name,
            resource => $resource
          };
          
          push @$required_resources, $resource_info;
        }
      }
    }
  }
  
  return $required_resources;
}

sub get_required_resource_json_lines {
  my ($self) = @_;
  
  my $required_resources = $self->get_required_resources;
  
  my @json_lines;
  for my $required_resource (@$required_resources) {
    my $class_name = $required_resource->{class_name};
    my $resource = $required_resource->{resource};
    my $resource_class_name = $resource->class_name;
    my $resource_mode = $resource->mode;
    my $resource_argv = $resource->argv || [];
    
    my $line = {
      resource_loader_class_name => "$class_name",
      class_name => $resource_class_name,
    };
    
    if (defined $resource_mode) {
      $line->{mode} = $resource_mode;
    }
    
    if (@$resource_argv) {
      $line->{argv} = $resource_argv;
    }
    
    my $json_line = JSON::PP->new->utf8->canonical(1)->encode($line);
    
    push @json_lines, $json_line;
  }
  
  return \@json_lines;
}

sub compile {
  my ($self) = @_;

  # Builder
  my $builder = $self->builder;
  
  my $class_name = $self->{class_name};
  
  my $compiler = $self->compiler;
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  eval { $compiler->compile($class_name) };
  
  if ($@) {
    my $error_messages = $compiler->get_error_messages;
    for my $error_message (@$error_messages) {
      print STDERR "$error_message\n";
    }
    exit(255);
  }
  my $runtime = $compiler->get_runtime;
  
  $self->runtime($runtime);
  
  $self->{finish_compile} = 1;
}

1;

=head1 Name

SPVM::Builder::Info - SPVM Class Information

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
