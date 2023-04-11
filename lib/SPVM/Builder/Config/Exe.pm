package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;

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
  my ($self, %options) = @_;
  
  unless (defined $options{output_type}) {
    $options{output_type} = 'exe';
  }
  
  $self = $self->SUPER::new(%options);
  
  unless (defined $self->{before_each_compile_cbs}) {
    $self->before_each_compile_cbs([]);
  }
  
  unless (defined $self->{config_spvm_core}) {
    $self->{config_spvm_core} = SPVM::Builder::Util::API::create_default_config();
  }
  
  unless (defined $self->{config_bootstrap}) {
    $self->{config_bootstrap} = SPVM::Builder::Util::API::create_default_config();
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

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config_exe = SPVM::Builder::Config::Exe->new_c99;

=head1 Description

SPVM::Builder::Config::Exe is configuration of creating excutable files of L<spvmcc>.

=head1 Fields

Fields of B<SPVM::Builder::Config::Exe>.

Fields are inherited from L<SPVM::Builder::Config> and you can use the following fields.

=head2 no_precompile

  my $no_precompile = $config->no_precompile;
  $config->no_precompile($no_precompile);

If C<no_precompile> is a true value, precompiling is not performed.

=head2 no_compiler_api

  my $no_compiler_api = $config->no_compiler_api;
  $config->no_compiler_api($no_compiler_api);

If C<no_compiler_api> is a true value, the source codes of the L<compiler native APIs|SPVM::Document::NativeAPI::Compiler> and the L<precompile native APIs|SPVM::Document::NativeAPI::Precompile> is not linked.

=head2 config_spvm_core

  my $config_spvm_core = $config->config_spvm_core;
  $config->config_spvm_core($config_spvm_core);

Gets and sets the config(a L<SPVM::Builder::Config> object) for SPVM core source files.

The default is a config that is created by the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function in the L<SPVM::Builder::Util::API> class.

=head2 config_bootstrap

  my $config_bootstrap = $config->config_bootstrap;
  $config->config_bootstrap($config_bootstrap);

Gets and sets the config(a L<SPVM::Builder::Config> object) for the bootstrap source file that contains C<main> function in the C language.

The default is a config that is created by the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function in the L<SPVM::Builder::Util::API> class.

=head1 Methods

Methods of B<SPVM::Builder::Config::Exe>.

Methods are inherited from L<SPVM::Builder::Config> and you can use the following methods.

=head2 new

  my $config = SPVM::Builder::Config::Exe->new;

Create a new C<SPVM::Builder::Config::Exe> object.

This is same as L<SPVM::Builder::Config/"new">, but set C<output_type> field to C<exe>.

=head2 add_before_each_compile_cb

  $config->add_before_compile_cb(@before_each_compile_cbs);

Adds elements after the last element of L</"before_each_compile_cbs"> field.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
