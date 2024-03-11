package SPVM::Builder::Config::Info;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;

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
  
  $self->compile;
  
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
  
}

sub get_class_names {
  my ($self) = @_;
  
  my $runtime = $self->runtime;
  
  my $runtime_info = SPVM::Native::Runtime::Info->new($runtime);
  
  my $class_names = $runtime_info->get_class_names->to_strings;
  
  return $class_names;
}

sub get_resource_loader_class_names {
  my ($self) = @_;
  
  my $runtime = $self->runtime;
  
  my $runtime_info = SPVM::Native::Runtime::Info->new($runtime);
  
  my $class_names = $runtime_info->get_class_names->to_strings;
  
  my $resource_loader_class_names = [];
  for my $class_name (@$class_names) {
    
    my $config_file = SPVM::Builder::Util::search_config_file($class_name);
    
    if (defined $config_file && -f $config_file) {
      my $config = SPVM::Builder::Config->load_config($config_file, []);
      
      my $resource_names = $config->get_resource_names;
      
      if (@$resource_names) {
        push @$resource_loader_class_names, $class_name;
      }
    }
  }
  
  return $resource_loader_class_names;
}

sub get_config_file {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $runtime = $self->runtime;
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  return $config_file;
}

sub get_config_content {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $runtime = $self->runtime;
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $config_content = SPVM::Builder::Util::slurp_binary($config_file);
  
  return $config_content;
}

sub get_config_resource_names {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $config = SPVM::Builder::Config->load_config($config_file, []);
  
  my $config_resource_names = $config->get_resource_names;
  
  return $config_resource_names;
}

1;

=head1 Name

SPVM::Builder::Config::Info - Class Information

=head1 Description

=head1 Usage

  my $builder_info = SPVM::Builder::Config::Info->new(class_name => "Foo");

=head1 Class Methods

=head2 new

  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);

Creates a L<SPVM::Builder::Config::Info> object given the class name $class_name and returns it.

=head1 Instance Methods

=head2 get_class_names

  my $class_names = $builder_info->get_class_names;

Returns the class names. This method is the same as the L<get_class_names|Native::Runtime::Info/"get_class_names"> method in the C<Native::Runtime::Info>, but the return value is converted to an array reference of strings.

=head2 get_resource_loader_class_names

  my $resource_loader_class_names = $builder_info->get_resource_loader_class_names;

Returns the class names that load resources.

=head2 get_config_file

  my $config_file = $builder_info->get_config_file($class_name);

Returns the file path of the config for the class given by the class name $class_name.

=head2 get_config_content

  my $config_content = $builder_info->get_config_content($class_name);

Returns the content of the config for the class given by the class name $class_name.

=head2 get_config_resource_names

  my $config_resource_names = $builder_info->get_config_resource_names($class_name);

Returns the resource names loaded in the config for the class given by the class name $class_name.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
