package SPVM::Builder::Config::Info;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;

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

sub script_name {
  my $self = shift;
  if (@_) {
    $self->{script_name} = $_[0];
    return $self;
  }
  else {
    return $self->{script_name};
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
  
  my $class_name = $self->{class_name};
  
  my $script_name = $self->{script_name};
  
  unless (defined $script_name || defined $class_name) {
    confess("The \"script_name\" option or the \"class_name\" option must be defined.");
  }
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new;
  
  $self->{builder} = $builder;
  
  my $compiler = SPVM::Builder::Native::Compiler->new;
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
  
  my $script_name = $self->{script_name};
  
  my $source;
  if (defined $script_name) {
    open my $fh, '<', $script_name
      or confess "Can't open file \"$script_name\":$!";
    
    $source = do { undef $/; <$fh> };
  }
  
  my $compiler = $self->compiler;
  
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  my $anon_class_name;
  
  eval { $class_name ? $compiler->compile($class_name) : $compiler->compile_anon_class($source) };
  
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
  
  my $category = [
    6, # SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS,
    7, # SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE,
  ];
  
  my $basic_types = [grep { $_->get_name !~ /::anon_class::/ && $_->get_name !~ /::anon_method::/ } @{$runtime->get_basic_types({category => $category})}];
  
  my $class_names = [map { $_->get_name } @$basic_types];
  
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

  my $config_info = SPVM::Builder::Config::Info->new(class_name => "Foo");

=head1 Class Methods

=head2 new

  my $config_info = SPVM::Builder::Config::Info->new(%options);

Creates an L<SPVM::Builder::Config::Info> object given options %options, and returns it.

The class specified by C<class_name> option or C<script_name> option is compiled and the runtime is generated.

C<class_name> option or C<script_name> option must be defined.

Options:

=over 2

=item * C<class_name>

A class name.

=item * C<script_name>

A script name.

=back

Exceptions:

The "class_name" option or the "script_name" option must be defined. Otherwise, an exception is thrown.

=head1 Instance Methods

=head2 get_class_names

  my $class_names = $config_info->get_class_names;

Returns the all class and interface names except for anon classes and classes generated by anon methods loaded by the runtime.

=head2 has_config_file

  my $has_config_file = $config_info->has_config_file($class_name);
  
If the class given by the class name has a config file, returns 1, otherwise returns 0.

Exceptions:

The class name $class_name must be defined. Otherwise, an exception is thrown.

=head2 is_resource_loader

  my $is_resource_loader = $config_info->is_resource_loader($class_name);
  
If the class given by the class name $class_name is a class that load resources, returns 1, otherwise returns 0.

Exceptions:

The class name $class_name must be defined. Otherwise, an exception is thrown.

=head2 get_config_file

  my $config_file = $config_info->get_config_file($class_name);

Returns the file path of the config for the class given by the class name $class_name.

Exceptions:

The class name $class_name must be defined. Otherwise, an exception is thrown.

The config file for the class "%s" is not found. Otherwise, an exception is thrown.

=head2 get_config_content

  my $config_content = $config_info->get_config_content($class_name);

Returns the content of the config for the class given by the class name $class_name.

Exceptions:

Exceptions thrown by L</"get_config_file"> method could be thrown.

=head2 get_config

  my $config = $config_info->get_config($class_name);

Returns a L<config|SPVM::Builder::Config> object for the class given by the class name $class_name.

Exceptions:

Exceptions thrown by L</"get_config_file"> method could be thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
