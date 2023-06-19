package SPVM::Builder::Compiler;

use strict;
use warnings;

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
  
  $self->create_compiler;
  
  return $self;
}

sub use {
  my ($self, $module_name, $file, $line) = @_;
  
  my $success = $self->compile($module_name, __FILE__, __LINE__);
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
