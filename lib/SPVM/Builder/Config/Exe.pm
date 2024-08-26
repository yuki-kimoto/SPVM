package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;

# Inheritance
use base 'SPVM::Builder::Config';

# Fields
sub global_after_create_compile_info_cbs {
  my $self = shift;
  if (@_) {
    $self->{global_after_create_compile_info_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{global_after_create_compile_info_cbs};
  }
}

sub global_before_compile_cbs {
  my $self = shift;
  if (@_) {
    $self->{global_before_compile_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{global_before_compile_cbs};
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
  my $self = shift;
  
  my %fields = (
    output_type => 'exe',
    global_before_compile_cbs => [],
    config_spvm_core => SPVM::Builder::Util::API::create_default_config(),
    config_bootstrap => SPVM::Builder::Util::API::create_default_config(),
    @_,
  );
  
  $self = $self->SUPER::new(%fields);
  
  return $self;
}

# Instance Methods
sub add_global_after_create_compile_info_cb {
  my ($self, @global_after_create_compile_info_cbs) = @_;
  
  push @{$self->{global_after_create_compile_info_cbs}}, @global_after_create_compile_info_cbs;
}

sub add_global_before_compile_cb {
  my ($self, @global_before_compile_cbs) = @_;
  
  push @{$self->{global_before_compile_cbs}}, @global_before_compile_cbs;
}

sub set_global_optimize {
  my ($self, $optimize) = @_;
  
  $self->add_global_after_create_compile_info_cb(sub {
    my ($config, $comile_info) = @_;
    
    $config->optimize($optimize);
  });
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Excutable File Config

=head1 Description

The SPVM::Builder::Config::Exe class has methods to manipulate the config for the excutable file generated by the L<spvmcc> command.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config_exe = SPVM::Builder::Config::Exe->new_gnu99;

=head1 Super Class

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 global_after_create_compile_info_cbs

  my $global_after_create_compile_info_cbs = $config_exe->global_after_create_compile_info_cbs;
  $config_exe->global_after_create_compile_info_cbs($global_after_create_compile_info_cbs);

Gets and sets the C<global_after_create_compile_info_cbs> field, an array reference of callbacks that work globally called just after creating a compilation information.

This affects all compilations of native classes and precompilation classes.

=head2 global_before_compile_cbs

  my $global_before_compile_cbs = $config_exe->global_before_compile_cbs;
  $config_exe->global_before_compile_cbs($global_before_compile_cbs);

Gets and sets the C<global_before_compile_cbs> field, an array reference of callbacks that work globally called just before the compile command L</"cc"> is executed.

This affects all compilations of native classes and precompilation classes.

=head2 config_spvm_core

  my $config_exe_spvm_core = $config_exe->config_spvm_core;
  $config_exe->config_spvm_core($config_exe_spvm_core);

Gets and sets the C<config_spvm_core> field, a L<SPVM::Builder::Config> object for SPVM core source files.

This field is automatically set and users nomally do not change it.

=head2 config_bootstrap

  my $config_exe_bootstrap = $config_exe->config_bootstrap;
  $config_exe->config_bootstrap($config_exe_bootstrap);

Gets and sets the C<config_bootstrap> field, a L<SPVM::Builder::Config> object for the bootstrap source file for the executable file.

This field is automatically set and users nomally do not change it.

=head1 Methods

=head2 new

  my $config_exe = SPVM::Builder::Config::Exe->new(%fields);

Create a new L<SPVM::Builder::Config::Exe> object with L</"Fields"> and fields of its super classes.

This method calls the C<new> method of its L<super class|/"Inheritance"> given %fields with field default values applied.

Field Default Values:

=over 2

=item * L<output_type|SPVM::Builder::Config/"output_type">

  "exe"

=item * L</"global_before_compile_cbs">

  []

=item * L</"config_spvm_core">

The return value of the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function of C<SPVM::Builder::Util::API> class.

=item * L</"config_bootstrap">

The return value of the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function of C<SPVM::Builder::Util::API> class.

=item * Other Fields

  undef

=back

=head2 add_global_after_create_compile_info_cb

  $config_exe->add_global_after_create_compile_info_cb(@global_after_create_compile_info_cbs);

Adds @global_after_create_compile_info_cbs to the end of L</"global_after_create_compile_info_cbs"> field.

Examples:

  $config_exe->add_global_after_create_compile_info_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc = $config->cc;
    
    # Do something
  });

=head2 add_global_before_compile_cb

  $config_exe->add_global_before_compile_cb(@global_before_compile_cbs);

Adds @global_before_compile_cbs to the end of L</"global_before_compile_cbs"> field.

Examples:

  $config_exe->add_global_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 set_global_optimize

  $config_exe->set_global_optimize("-O0 -g");

Sets C<optimize> that works globally. This is the same as the following code.

  $config_exe->add_global_after_create_compile_info_cb(sub {
    my ($config, $comile_info) = @_;
    
    $config->optimize($optimize);
  });

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
