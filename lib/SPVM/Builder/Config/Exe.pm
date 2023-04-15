package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;

# Inheritance
use base 'SPVM::Builder::Config';

# Fields
sub before_each_compile_cbs {
  my $self = shift;
  if (@_) {
    $self->{before_each_compile_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{before_each_compile_cbs};
  }
}

sub no_precompile {
  my $self = shift;
  if (@_) {
    $self->{no_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{no_precompile};
  }
}

sub no_compiler_api {
  my $self = shift;
  if (@_) {
    $self->{no_compiler_api} = $_[0];
    return $self;
  }
  else {
    return $self->{no_compiler_api};
  }
}

sub config_spvm_core {
  my $self = shift;
  if (@_) {
    $self->{config_spvm_core} = $_[0];
    return $self;
  }
  else {
    return $self->{config_spvm_core};
  }
}

sub config_bootstrap {
  my $self = shift;
  if (@_) {
    $self->{config_bootstrap} = $_[0];
    return $self;
  }
  else {
    return $self->{config_bootstrap};
  }
}

# Class Methods
sub new {
  my ($self, %fields) = @_;

  unless (defined $fields{output_type}) {
    $fields{output_type} = 'exe';
  }
  
  $self = $self->SUPER::new(%fields);
  
  unless (defined $self->before_each_compile_cbs) {
    $self->before_each_compile_cbs([]);
  }
  
  unless (defined $self->no_precompile) {
    $self->no_precompile(0);
  }
  
  unless (defined $self->no_compiler_api) {
    $self->no_compiler_api(0);
  }
  
  unless (defined $self->config_spvm_core) {
    $self->config_spvm_core(SPVM::Builder::Util::API::create_default_config());
  }
  
  unless (defined $self->config_bootstrap) {
    $self->config_bootstrap(SPVM::Builder::Util::API::create_default_config());
  }
  
  return $self;
}

# Instance Methods
sub add_before_each_compile_cb {
  my ($self, @before_each_compile_cbs) = @_;
  
  push @{$self->{before_each_compile_cbs}}, @before_each_compile_cbs;
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Configurations of creating excutable files.

=head1 Description

The SPVM::Builder::Config::Exe class has methods to manipulate a config to generate an excutable file using L<spvmcc>.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config_exe = SPVM::Builder::Config::Exe->new_c99;

=head1 Inheritance

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 no_precompile

  my $no_precompile = $config_exe->no_precompile;
  $config_exe->no_precompile($no_precompile);

Gets and sets the C<no_precompile> field.

If this field is a true value, precompiling is not performed.

=head2 no_compiler_api

  my $no_compiler_api = $config_exe->no_compiler_api;
  $config_exe->no_compiler_api($no_compiler_api);

Gets and sets the C<no_precompile> field.

If this field is a true value, the source codes of the L<compiler native APIs|SPVM::Document::NativeAPI::Compiler> and the L<precompile native APIs|SPVM::Document::NativeAPI::Precompile> is not linked.

=head2 config_spvm_core

  my $config_exe_spvm_core = $config_exe->config_spvm_core;
  $config_exe->config_spvm_core($config_exe_spvm_core);

Gets and sets the C<config_spvm_core> field.

This field is a L<SPVM::Builder::Config> object for SPVM core source files.

=head2 config_bootstrap

  my $config_exe_bootstrap = $config_exe->config_bootstrap;
  $config_exe->config_bootstrap($config_exe_bootstrap);

Gets and sets the C<config_bootstrap> field.

This field is a L<SPVM::Builder::Config> object for the bootstrap source file that contains C<main> function in the C language for the executable file.

=head1 Methods

=head2 new

  my $config_exe = SPVM::Builder::Config::Exe->new(%fields);

Create a new C<SPVM::Builder::Config::Exe> object with L</"Fields">.

This method calls the C<new> method of the L<super class|/"Inheritance"> before the own operations of this method.

Default Field Values:

If a field is not defined, the field is set to the following default value.

=over 2

=item * L</"output_type">

"exe"

=item * L</"before_each_compile_cbs">

[]

=item * L</"no_precompile">

0

=item * L</"no_compiler_api">

0

=item * L</"config_spvm_core">

The return value of the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function of the L<SPVM::Builder::Util::API> class.

=item * L</"config_bootstrap">

The return value of the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function of the L<SPVM::Builder::Util::API> class.

=back

=head2 add_before_each_compile_cb

  $config_exe->add_before_compile_cb(@before_each_compile_cbs);

Adds elements after the last element of the L</"before_each_compile_cbs"> field.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
