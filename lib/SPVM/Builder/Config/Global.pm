package SPVM::Builder::Config::Global;

use parent 'SPVM::Builder::Config';

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;
use SPVM::Builder::Accessor 'has';

# Fields
my $fields;

BEGIN {
  $fields = [qw(
    mode
    before_compile_cbs_global
    optimize_global
    include_dirs_global
    include_dirs_spvm
    include_dirs_native
    include_dirs_native_class
    include_dirs_precompile
    external_object_files
    matches
  )];

  has($fields);
}

{
  no warnings 'redefine';

  sub include_dirs_native_class {
    my $self = shift;
    my $class_name = shift;
    unless (defined $class_name) {
      confess("The class name \$class_name must be defined.");
    }
    if (@_) {
      $self->{include_dirs_native_class}{$class_name} = $_[0];
      return $self;
    }
    else {
      return $self->{include_dirs_native_class}{$class_name};
    }
  }
}

sub option_names {
  my ($self) = @_;
  return [@{$self->SUPER::option_names}, @$fields];
}

# Class Methods
sub new {
  my $self = shift;
  
  my $default_config = SPVM::Builder::Util::API::create_default_config();
  
  my %fields = (
    %$default_config,
    category => 'spvm',
    before_compile_cbs_global => [],
    include_dirs_global => [],
    include_dirs_spvm => [],
    include_dirs_native => [],
    include_dirs_native_class => {},
    include_dirs_precompile => [],
    external_object_files => [],
    matches => [],
    @_,
  );
  
  $self = $self->SUPER::new(%fields);
  
  return $self;
}

# Instance Methods
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

sub add_before_compile_cb_global {
  my ($self, @before_compile_cbs_global) = @_;
  
  push @{$self->{before_compile_cbs_global}}, @before_compile_cbs_global;
}

sub add_include_dir_global {
  my ($self, @include_dirs_global) = @_;
  
  push @{$self->{include_dirs_global}}, @include_dirs_global;
}

sub add_include_dir_spvm {
  my ($self, @include_dirs_spvm) = @_;
  
  push @{$self->{include_dirs_spvm}}, @include_dirs_spvm;
}

sub add_include_dir_native {
  my ($self, @include_dirs_native) = @_;
  
  push @{$self->{include_dirs_native}}, @include_dirs_native;
}

sub add_include_dir_native_class {
  my ($self, $class_name, @include_dirs_native_class) = @_;
  
  unless (defined $self->{include_dirs_native_class}{$class_name}) {
    $self->{include_dirs_native_class}{$class_name} = [];
  }
  
  push @{$self->{include_dirs_native_class}{$class_name}}, @include_dirs_native_class;
}

sub add_include_dir_precompile {
  my ($self, @include_dirs_precompile) = @_;
  
  push @{$self->{include_dirs_precompile}}, @include_dirs_precompile;
}

sub add_external_object_file {
  my ($self, @external_object_files) = @_;
  
  push @{$self->{external_object_files}}, @external_object_files;
}

sub use_spvm_archive {
  my ($self, $spvm_archive) = @_;
  
  $self->{spvm_archive} = $spvm_archive;
  
  return $self;
}

sub get_spvm_archive {
  my ($self) = @_;
  
  return $self->{spvm_archive};
}

# Upgrade a hash reference to an SPVM::Builder::Config object.
# Validates that the input is a HASH ref, SPVM::Builder::Config, or undef.
sub _upgrade_to_config {
  my ($self, $config) = @_;
  
  return unless defined $config;

  if (ref $config eq 'HASH') {
    return SPVM::Builder::Config->new_empty(%$config);
  }
  
  unless (UNIVERSAL::isa($config, 'SPVM::Builder::Config')) {
    my $type = ref($config) || 'a scalar value';
    confess "The configuration must be a HASH reference, an SPVM::Builder::Config object, or undef (got $type)";
  }
  
  return $config;
}

# --- Main Methods ---

# Append a match rule.
sub match {
  my ($self, $condition, $config) = @_;
  
  $condition = $self->_upgrade_to_config($condition);
  
  confess "The config argument must be defined" unless defined $config;
  $config = $self->_upgrade_to_config($config);

  # Validation: Config values must not be undef.
  for my $key (keys %$config) {
    confess "The value of the key '$key' in config cannot be undef" unless defined $config->{$key};
  }

  for my $match (@{$self->{matches} ||= []}) {
    if ($self->_is_same_keys($match->{condition}, $condition)) {
      my $keys_str = defined $condition ? join(', ', sort keys %$condition) : 'Any';
      confess "A match rule with the same condition keys already exists: [$keys_str]";
    }
  }

  push @{$self->{matches}}, { condition => $condition, config => $config };
  return $self;
}

# Prepend a match rule.
sub prepend_match {
  my ($self, $condition, $config) = @_;
  
  $condition = $self->_upgrade_to_config($condition);
  
  confess "The config argument must be defined" unless defined $config;
  $config = $self->_upgrade_to_config($config);

  for my $match (@{$self->{matches} ||= []}) {
    if ($self->_is_same_keys($match->{condition}, $condition)) {
      my $keys_str = defined $condition ? join(', ', sort keys %$condition) : 'Any';
      confess "A match rule with the same condition keys already exists: [$keys_str]";
    }
  }

  unshift @{$self->{matches}}, { condition => $condition, config => $config };
  return $self;
}

# Update a match rule.
sub update_match {
  my ($self, $condition, $config) = @_;
  
  $condition = $self->_upgrade_to_config($condition);
  
  confess "The config argument must be defined" unless defined $config;
  $config = $self->_upgrade_to_config($config);

  my $updated = 0;
  for my $match (@{$self->{matches} ||= []}) {
    if ($self->_is_same_keys($match->{condition}, $condition)) {
      $match->{config} = $config;
      $updated = 1;
      last;
    }
  }
  confess "Match rule not found for update" unless $updated;
  return $self;
}

# Delete a match rule.
sub delete_match {
  my ($self, $condition) = @_;
  
  $condition = $self->_upgrade_to_config($condition);

  my $deleted = 0;
  my @new_matches;
  for my $match (@{$self->{matches} ||= []}) {
    if ($self->_is_same_keys($match->{condition}, $condition)) {
      $deleted = 1;
      next;
    }
    push @new_matches, $match;
  }
  confess "Match rule not found for delete" unless $deleted;
  $self->{matches} = \@new_matches;
  return $self;
}

# Search for a match rule.
sub search_match {
  my ($self, $condition) = @_;
  
  $condition = $self->_upgrade_to_config($condition);
  
  for my $match (@{$self->{matches} ||= []}) {
    if ($self->_is_same_keys($match->{condition}, $condition)) {
      return $match->{config};
    }
  }
  return;
}

# --- Syntax Sugar for "Any" Conditions ---

sub match_any         { shift->match(undef, @_) }
sub prepend_match_any { shift->prepend_match(undef, @_) }
sub update_match_any  { shift->update_match(undef, @_) }
sub delete_match_any  { shift->delete_match(undef) }
sub search_match_any  { shift->search_match(undef) }

# --- Internal Helper ---

# Check if two config objects have the same set of keys.
sub _is_same_keys {
  my ($self, $c1, $c2) = @_;
  
  return 1 if !defined $c1 && !defined $c2;
  return 0 if !defined $c1 || !defined $c2;

  my @keys1 = sort keys %$c1;
  my @keys2 = sort keys %$c2;
  return 0 unless scalar @keys1 == scalar @keys2;
  for my $i (0 .. $#keys1) {
    return 0 unless $keys1[$i] eq $keys2[$i];
  }
  return 1;
}

1;

=head1 Name

SPVM::Builder::Config::Global - Excutable File Config

=head1 Description

The SPVM::Builder::Config::Global class has methods to manipulate the config for the excutable file generated by L<spvmcc> command.

=head1 Usage

  use SPVM::Builder::Config::Global;
  
  my $config_global = SPVM::Builder::Config::Global->new;

=head1 Details

=head2 Warning: Should Not Change Compiler Flags

The fields for compiler flags in L<SPVM::Builder::Config> such as L<SPVM::Builder::Config/"cc">, L<SPVM::Builder::Config/"std"> should not be changed.

This is because the compiler flags are used to compile SPVM core source files and a bootstrap source file generagted by C<spvmcc> command.

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

=head1 Super Class

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 mode

  my $mode = $config->mode;
  $config->mode($mode);

Gets and sets C<mode> field.

=head2 before_compile_cbs_global

  my $before_compile_cbs_global = $config_global->before_compile_cbs_global;
  $config_global->before_compile_cbs_global($before_compile_cbs_global);

Gets and sets the C<before_compile_cbs_global> field, an array reference of callbacks that work globally called just before the compile command L</"cc"> is executed.

This affects all compilations.

=head2 optimize_global

  my $optimize_global = $config->optimize_global;
  $config->optimize_global($optimize_global);

Gets and sets C<optimize> field, an arugment of the compiler L</"cc"> for optimization in all compilation.

=head2 include_dirs_global

  my $include_dirs_global = $config->include_dirs_global;
  $config->include_dirs_global($include_dirs_global);

Gets and sets C<include_dirs> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in all compilation.

=head2 include_dirs_spvm

  my $include_dirs_spvm = $config->include_dirs_spvm;
  $config->include_dirs_spvm($include_dirs_spvm);

Gets and sets C<include_dirs_spvm> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 include_dirs_native

  my $include_dirs_native = $config->include_dirs_native;
  $config->include_dirs_native($include_dirs_native);

Gets and sets C<include_dirs_native> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 include_dirs_native_class

  my $include_dirs_native_class = $config->include_dirs_native_class($class_name);
  $config->include_dirs_native_class($class_name, $include_dirs_native);

Gets and sets the value of C<include_dirs_native_class> field's class name key $class_name, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 include_dirs_precompile

  my $include_dirs_precompile = $config->include_dirs_precompile;
  $config->include_dirs_precompile($include_dirs_precompile);

Gets and sets C<include_dirs_precompile> field, an array reference containing C<-I> arugments of the compiler L</"cc"> in compilation for precompilation.

=head2 external_object_files

  my $external_object_files = $config->external_object_files;
  $config->external_object_files($external_object_files);

Gets and sets C<external_object_files> field, an array reference containing additinal external object files linked to an executable file.

=head2 spvm_archive

An SPVM archive.

See L</"use_spvm_archive"> and L</"get_spvm_archive">.

=head1 Methods

=head2 new

  my $config_global = SPVM::Builder::Config::Global->new(%fields);

Create a new L<SPVM::Builder::Config::Global> object with L</"Fields"> and fields of its super classes.

This method calls the C<new> method of its L<super class|/"Inheritance"> given %fields with field default values applied.

Field Default Values:

=over 2

=item * L<output_type|SPVM::Builder::Config/"output_type">

  "exe"

=item * L</"before_compile_cbs_global">

  []

=item * Other Fields

  undef

=back

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

=head2 add_before_compile_cb_global

  $config_global->add_before_compile_cb_global(@before_compile_cbs_global);

Adds @before_compile_cbs_global to the end of L</"before_compile_cbs_global"> field.

Examples:

  $config_global->add_before_compile_cb_global(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 add_include_dir_global

  $config->add_include_dir_global(@include_dirs_global);

Adds @include_dirs_global to the end of L</"include_dirs_global"> field.

=head2 add_include_dir_spvm

  $config->add_include_dir_spvm(@include_dirs_spvm);

Adds @include_dirs_spvm to the end of L</"include_dirs_spvm"> field.

=head2 add_include_dir_native

  $config->add_include_dir_native(@include_dirs_native);

Adds @include_dirs_native to the end of L</"include_dirs_native"> field.

=head2 add_include_dir_native_class

  $config->add_include_dir_native_class($class_name, @include_dirs_native_class);

Adds @include_dirs_native_class to the end of L</"include_dirs_native_class"> field's key $class_name.

=head2 add_include_dir_precompile

  $config->add_include_dir_precompile(@include_dirs_precompile);

Adds @include_dirs_precompile to the end of L</"include_dirs_precompile"> field.

=head2 add_external_object_file

  $config->add_external_object_file(@external_object_files);

Adds @external_object_files to the end of L</"external_object_files"> field.

=head2 use_spvm_archive

  $config->use_spvm_archive($spvm_archive);
  $config->use_spvm_archive($spvm_archive, $options);

Loads an SPVM archive.

Actually, L</"spvm_archive"> field is just set to $spvm_archive, and the loading happens later.

SPVM Archive is a format used to bundle SPVM class files, compiled SPVM native classes, precompiled classes, third-party header files, and static libraries into a single directory or a C<.tar.gz> file.

See L<SPVM::Document::Archive> for details.

Examples:

  my $config_dir = File::Basename::dirname __FILE__;
  
  $config->use_spvm_archive("$config_dir/spvm-archive-myapp");
  
  $config->use_spvm_archive("$config_dir/spvm-archive-myapp.tar.gz");
  
=head2 get_spvm_archive

  my $spvm_archive = $config->get_spvm_archive;

Gets an SPVM archive.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
