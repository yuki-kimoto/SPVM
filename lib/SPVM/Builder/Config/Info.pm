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
    confess("The \"class_name\" option must be defined.");
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

sub has_config_file {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $has_config_file = defined $config_file;
  
  return $has_config_file;
}

sub is_resource_loader {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  my $is_resource_loader = 0;
  if (defined $config_file && -f $config_file) {
    my $config = SPVM::Builder::Config->load_config($config_file, []);
    
    my $resource_names = $config->get_resource_names;
    
    if (@$resource_names) {
      $is_resource_loader = 1;
    }
  }
  
  return $is_resource_loader;
}

sub get_config_file {
  my ($self, $class_name) = @_;
  
  unless (defined $class_name) {
    confess("The class name \$class_name must be defined.");
  }
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  unless ($config_file) {
    confess("The config file for the class \"$class_name\" is not found.");
  }
  
  return $config_file;
}

sub get_config_content {
  my ($self, $class_name) = @_;
  
  my $config_file = $self->get_config_file($class_name);
  
  my $config_content = SPVM::Builder::Util::slurp_binary($config_file);
  
  return $config_content;
}

sub get_config {
  my ($self, $class_name) = @_;
  
  my $config_file = $self->get_config_file($class_name);
  
  my $config = SPVM::Builder::Config->load_config($config_file, []);
  
  return $config;
}

1;

=head1 Name

SPVM::Builder::Config::Info - Config Information

=head1 Description

The SPVM::Builder::Config::Info class has methods to manipulate config information.

=head1 Usage

  my $builder_info = SPVM::Builder::Config::Info->new(class_name => "Foo");

=head1 Class Methods

=head2 new

  my $builder_info = SPVM::Builder::Config::Info->new(%options);

Creates a L<SPVM::Builder::Config::Info> object given the class name $class_name and returns it.

The class specified by $class_name and classes loaded by the class are compiled and the runtime is generated.

The C<class_name> option must be defined.

Options:

=over 2

=item * C<class_name>

A class name.

=back

Exceptions:

The "class_name" option must be defined, otherwise an exception is thrown.

=head1 Instance Methods

=head2 get_class_names

  my $class_names = $builder_info->get_class_names;

Returns the all class names loaded by the runtime.

This method is the same as the L<get_class_names|Native::Runtime::Info/"get_class_names"> method in the C<Native::Runtime::Info>, but the return value is converted to an array reference of strings.

=head2 has_config_file

  my $has_config_file = $builder_info->has_config_file($class_name);
  
If the class given by the class name has a config file, returns 1, otherwise returns 0.

Exceptions:

The class name $class_name must be defined, otherwise an exception is thrown.

=head2 is_resource_loader

  my $is_resource_loader = $builder_info->is_resource_loader($class_name);
  
If the class given by the class name $class_name is a class that load resources, returns 1, otherwise returns 0.

Exceptions:

The class name $class_name must be defined, otherwise an exception is thrown.

=head2 get_config_file

  my $config_file = $builder_info->get_config_file($class_name);

Returns the file path of the config for the class given by the class name $class_name.

Exceptions:

The class name $class_name must be defined, otherwise an exception is thrown.

The config file for the class "%s" is not found, otherwise an exception is thrown.

=head2 get_config_content

  my $config_content = $builder_info->get_config_content($class_name);

Returns the content of the config for the class given by the class name $class_name.

Exceptions:

Exceptions thrown by the L</"get_config_file"> method could be thrown.

=head2 get_config

  my $config = $builder_info->get_config($class_name);

Returns the L<config|SPVM::Builder::Config> for the class given by the class name $class_name.

Exceptions:

Exceptions thrown by the L</"get_config_file"> method could be thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
