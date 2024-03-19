package SPVM::Builder::Native::Compiler;

use strict;
use warnings;
use Scalar::Util 'weaken';

use SPVM::Builder::Native::Runtime;

### Fields

sub get_runtime { shift->{runtime} }

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
  
  my $env_api = SPVM::Builder::Native::Env->new;
  
  $self->env_api($env_api);
  
  $self->create_native_compiler;
  
  my $runtime = $self->get_runtime;
  
  $runtime->{compiler} = $self;
  
  weaken $runtime->{compiler};
  
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

SPVM::Builder::Native::Compiler - Compiler Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
