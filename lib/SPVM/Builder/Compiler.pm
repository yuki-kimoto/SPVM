package SPVM::Builder::Compiler;

use strict;
use warnings;

use SPVM::Builder::Runtime;

### Fields

sub get_runtime { shift->{runtime} }

sub env_api {
  my $self = shift;
  if (@_) {
    $self->{env_api} = $_[0];
    return $self;
  }
  else {
    return $self->{env_api};
  }
}

sub pointer {
  my $self = shift;
  if (@_) {
    $self->{pointer} = $_[0];
    return $self;
  }
  else {
    return $self->{pointer};
  }
}

sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->{include_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs};
  }
}

sub print_error_messages {
  my ($self, $fh) = @_;

  my $error_messages = $self->get_error_messages;
  for my $error_message (@$error_messages) {
    printf $fh "[CompileError]$error_message\n";
  }
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $env_api = SPVM::Builder::Env->new;
  
  $self->env_api($env_api);
  
  $self->create_native_compiler;
  
  my $runtime = $self->get_runtime;
  
  $runtime->env_api($env_api);
  
  return $self;
}

sub compile_with_exit {
  my ($self, $class_name, $file, $line) = @_;
  
  my $success = $self->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $self->print_error_messages(*STDERR);
    exit(255);
  }
}

1;

=head1 Name

SPVM::Builder::Compiler - SPVM Builder Compiler

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
