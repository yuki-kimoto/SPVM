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
  force
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
  
  # file
  $self->file(undef);

  # force (default is undef)
  
  # quiet (default is undef)

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

sub _remove_ext_from_config_file {
  my ($config_file) = @_;
  
  my ($config_base_name, $config_dir) = fileparse $config_file;
  
  $config_base_name =~ s/(\.[^\.]+)?\.config$//;
  
  my $config_file_without_ext = "$config_dir$config_base_name";
  
  return $config_file_without_ext;
}

sub _eval_config_content {
  
  $_[0] = qq|{\nuse strict;\nuse warnings;\nuse utf8;\n\nuse SPVM::Builder::Config;\nuse SPVM::Builder::Config::Exe;\n# line 1 "$_[1]"\n$_[0]\n}\n|;
  
  return eval $_[0];
}

sub load_config {
  my ($self, $config_file) = @_;
  
  unless (-f $config_file) {
    confess("The config file \"$config_file\" must exist");
  }
  
  my $config;
  {
    open my $fh, '<', $config_file
      or confess("The config file \"$config_file\" can't found: $!");
    
    my $config_content = do { $/ = undef; <$fh> };
    
    $config = &_eval_config_content($config_content, $config_file);
  }
  
  if ($@) {
    confess("The config file \"$config_file\" can't be parsed: $@");
  }
  
  unless (defined $config && $config->isa('SPVM::Builder::Config::Linker')) {
    confess("The config file must be an SPVM::Builder::Config::Linker object.");
  }
  
  push @{$config->loaded_config_files}, $config_file;
  
  $config->file($config_file);
  
  if ($self) {
    bless $config, ref $self || $self;
  }
  
  return $config;
}

sub load_mode_config {
  my ($self, $config_file, $mode, $options) = @_;
  
  $options //= {};
  
  my $mode_config_file = SPVM::Builder::Config::Base::_remove_ext_from_config_file($config_file);
  if (defined $mode) {
    $mode_config_file .= ".$mode";
  }
  $mode_config_file .= ".config";
  
  unless (-f $mode_config_file) {
    confess("Can't find the config file '$mode_config_file'");
  }
  
  my $config = SPVM::Builder::Config::Base::load_config($self, $mode_config_file);
  
  if (defined $mode) {
    $config->mode($mode);
  }
  
  return $config;
}

sub load_base_config {
  my ($self, $config_file, $args) = @_;
  
  my $config = $self->load_mode_config($config_file, undef, $args);
  
  return $config;
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

The SPVM::Builder::Config class has methods to get and set config for compiling and linking L<native classes|SPVM::Document::NativeClass>.

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

This field is set by L</"load_config"> method and users should not set it.

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

=head2 force

  my $force = $config->force;
  $config->force($force);

Gets and sets C<force> field.

If this field is a true value, the compilation and linking are forced.

If this field is a false value except for undef, the compilation and linking are performed following the rule of the L<dependency resolution|SPVM::Document::NativeClass/"Dependency Resolution">.

If this field is undef, this config does not specify whether the compilation and linking are perfomed.

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

Returns the config files loaded by L</"load_config"> method.

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

=head2 load_config

  my $config = $config->load_config($config_file);

Loads a config file given a config file path and an array refernce containing L<config arguments|/"Config Arguments">, and returns an L<SPVM::Builder::Config> object.

Examples:

  my $config = $config->load_config(__FILE__);

=head2 load_base_config

  my $config = $config->load_base_config($config_file);

Creates the base config file path from the config file path $config_file, and calls L<load_config|SPVM::Builder::Config/"load_config"> method given the base config file path and config arguments, and returns its return value.

A base config file is the config file that removes its mode.

  # Config file
  MyClass.mode.config
  
  # Base config file
  MyClass.config

Examples:

  my $config = SPVM::Builder::Config::Global->load_base_config(__FILE__);

=head2 load_mode_config

  my $config = $config->load_mode_config($config_file, $mode);

Creates a L<mode config file|/"Config Mode"> path from the config file path $config_file, and calls L<load_config|SPVM::Builder::Config/"load_config"> method given the mode config file path and config arguments, and returns its return value.

  my $config = SPVM::Builder::Config::Global->load_mode_config(__FILE__, "production");

L</"mode>" field is set to $mode.

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