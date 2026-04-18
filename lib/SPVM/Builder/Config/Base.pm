package SPVM::Builder::Config::Base;

use strict;
use warnings;
use Carp 'confess';
use SPVM::Builder::Util;
use SPVM::Builder::Accessor 'has';
use File::Basename 'dirname', 'fileparse';

# Base Fields
my $base_fields = [qw(
  mode
  file
  class_name
  category
  quiet
  is_jit
  is_resource
  loaded_config_files
  config_global
)];

# Accessors generation for base fields
has($base_fields);

sub new_empty {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  SPVM::Builder::Util::check_option_names($self, $self->option_names);
  
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  SPVM::Builder::Util::check_option_names($self, $self->option_names);
  
  # category
  unless (exists $self->{category}) {
    $self->category('native');
  }

  unless (exists $self->{loaded_config_files}) {
    $self->{loaded_config_files} = [];
  }
  
  # is_jit, is_resource are normally set via constructor if needed
  
  return $self;
}

# Instance Methods related to Base functionality
sub option_names {
  my ($self) = @_;
  
  return $base_fields;
}

sub create_option {
  my ($self, $name, $value) = @_;
  
  # Extract the option name without leading hyphens or slashes to check its length
  my $pure_name = $name;
  $pure_name =~ s/^[\-\/]+//;
  
  if (length $pure_name <= 1) {
    return $self->create_option_short($name, $value);
  }
  else {
    return $self->create_option_long($name, $value);
  }
}

sub clone {
  my ($self) = @_;
  
  my $clone = bless {}, ref $self;
  
  for my $name (keys %$self) {
    my $value = $self->{$name};
    
    if (ref $value eq 'ARRAY') {
      $clone->{$name} = [@$value];
    }
    elsif (ref $value eq 'HASH') {
      $clone->{$name} = &_copy_hash($value);
    }
    else {
      $clone->{$name} = $value;
    }
  }
  
  return $clone;
}

sub _copy_hash {
  my ($hash) = @_;
  
  my $clone = {};
  
  for my $name (keys %$hash) {
    my $value = $hash->{$name};
    
    if (ref $value eq 'ARRAY') {
      $clone->{$name} = [@$value];
    }
    elsif (ref $value eq 'HASH') {
      $clone->{$name} = {%$value};
    }
    else {
      $clone->{$name} = $value;
    }
  }
  
  return $clone;
}

sub get_base_dir {
  my ($self) = @_;

  my $file = $self->file;
  my $class_name = $self->class_name;

  unless (defined $file) {
    confess("The file must be defined.");
  }

  unless (defined $class_name) {
    confess("the class_name must be defined.");
  }

  my $abs_file = File::Spec->rel2abs($file);
  my $base_dir = dirname($abs_file);

  my @parts = split(/::/, $class_name);
  my $depth = scalar @parts;

  for (my $i = 0; $i < $depth; $i++) {
    $base_dir = dirname($base_dir);
  }

  return $base_dir;
}

1;

=head1 Name

SPVM::Builder::Config - Config for Compiling and Linking Native Classes

=head1 Description

SPVM::Builder::Config class gets and sets config for compiling and linking L<native classes|SPVM::Document::NativeClass>.

=head1 Fields

=head2 class_name

  my $class_name = $config->class_name;
  $config->class_name($class_name);

Gets and sets C<class_name> field, the name of the class configured by this config.

This field is automatically set and users nomally do not change it.

=head2 file

  my $file = $config->file;
  $config->file($file);

Gets and sets C<file> field, the file path of this config.

=head2 category

  my $category = $config->category;
  $config->category($category);

Gets and sets C<category> field.

If this field is C<precompile>, this config is for precompilation, 

If this field is C<native>, this config is for a native class.

This field is automatically set and users nomally do not change it.

=head2 is_resource

  my $is_resource = $config->is_resource;
  $config->is_resource($is_resource);

Gets and sets C<is_resource> field.

If this field is true, this config is for a L<resource|SPVM::Document::Resource> class.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Gets and sets C<quiet> field.

If this field is a true value, the messages from the compiler and the linker are output to C<stderr>.

If this field is a false value except for undef, the messages from the compiler and the linker are not output.

If this field is undef, this config does specify whether the messages from the compiler and the linker are output.

=head2 mode

  my $mode = $config->mode;
  $config->mode($mode);

Gets and sets C<mode> field.

=head2 config_global

  my $config_global = $config->config_global;
  $config->config_global($config_global);

Gets and sets the C<config_global> field, which provides global compilation rules.

This field is an L<SPVM::Builder::Config::Global> object (like L<SPVM::Builder::Config::Exe>) that stores shared settings used across multiple compilation units.

For example, when the L<spvmcc> command generates an executable file, it sets this field to an L<SPVM::Builder::Config::Exe> object. This allows individual resource configurations to inherit or refer to global flags, such as optimization levels or common library paths, defined in the executable's main configuration.

=head2 loaded_config_files

Returns the config files loaded by L<SPVM::Builder::Config::Util/"load_config"> function.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config::Base->new(%fields);

Creates a new C<SPVM::Builder::Config::Base> object with L<fields|/"Fields">, and returns it.

Field Default Values:

=over 2

=item * L</"file">

This value is set automatically.

=item * L</"category">

  "native"

=back

=cut

=head1 Instance Methods

=head2 clone

  my $clone = $self->clone;

Clones L<SPVM::Builder::Config> object, and returns it.

=head2 Config Mode

A config can have its mode if the config is one for an executable file generated by L<spvmcc> command.

The mode is written in the format C<.MODE_NAME> just before C<.config> extension of a config file.

C<MODE_NAME> must consist of C<a-zA-Z0-9_>.

Examples:
  
  # production mode
  MyClass.production.config
  
  # devel mode
  MyClass.devel.config

Use L</"mode"> field to get the config mode.

  my $mode = $config->mode;

The L<spvmcc> command has C<--mode> option for giving a config mode.

  spvmcc -o myapp --mode production myapp.spvm

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
