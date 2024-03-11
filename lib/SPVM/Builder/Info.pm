package SPVM::Builder::Info;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use SPVM::Builder::Config::Exe;

use SPVM 'Native::Compiler';
use SPVM 'Native::Runtime::Info';

# Fields
sub builder {
  my $self = shift;
  if (@_) {
    $self->{builder} = $_[0];
    return $self;
  }
  else {
    return $self->{builder};
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
  
  my $self = bless {@_}, $class;
  
  # Target class name
  my $class_name = $self->{class_name};
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new;
  
  $self->{builder} = $builder;
  
  my $compiler = SPVM::Native::Compiler->new;
  $compiler->add_include_dir($_) for @{$builder->include_dirs};
  $self->{compiler} = $compiler;
  
  return $self;
}

# Instance Methods
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
  
  my $runtime_info = SPVM::Native::Runtime::Info->new($runtime);
  $self->runtime_info($runtime_info);
  
  $self->{finish_compile} = 1;
}

sub get_resource_loader_class_names {
  my ($self) = @_;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $runtime = $self->runtime;
  
  my $runtime_info = SPVM::Native::Runtime::Info->new($runtime);
  
  my $class_names = $runtime_info->get_class_names->to_strings;
  
  my $resource_loader_class_names = [];
  for my $class_name (@$class_names) {
    
    my $config_file = SPVM::Builder::Util::search_config_file($class_name);
    
    my $config = SPVM::Builder::Config->load_config($config_file, []);
    
    my $resource_names = $config->get_resource_names;
    
    if (@$resource_names) {
      push @$resource_loader_class_names, $class_name;
    }
  }
  
  return $resource_loader_class_names;
}

sub get_config_content {
  my ($self, $class_name) = @_;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $runtime = $self->runtime;
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $config_content = SPVM::Builder::Util::slurp_binary($config_file);
  
  return $config_content;
}

sub get_resource_names {
  my ($self, $class_name) = @_;
  
  unless ($self->{finish_compile}) {
    $self->compile;
  }
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $config = SPVM::Builder::Config->load_config($config_file, []);
  
  my $resource_names = $config->get_resource_names;
  
  return $resource_names;
}

1;

=head1 Name

SPVM::Builder::Info - Creating Executable File

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
