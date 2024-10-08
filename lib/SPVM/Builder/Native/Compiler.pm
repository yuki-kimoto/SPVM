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

sub boot_env {
  my $self = shift;
  if (@_) {
    $self->{boot_env} = $_[0];
    return $self;
  }
  else {
    return $self->{boot_env};
  }
}

sub get_formatted_error_messages {
  my ($self, $fh) = @_;
  
  my $formatted_error_messages = [];
  my $error_messages = $self->get_error_messages;
  for my $error_message (@$error_messages) {
    push @$formatted_error_messages, "[Compilation Error]$error_message\n";
  }
  
  return $formatted_error_messages;
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $boot_env = SPVM::Builder::Native::Env->new;
  
  $self->boot_env($boot_env);
  
  $self->create_native_compiler;
  
  my $runtime = $self->get_runtime;
  
  $runtime->{compiler} = $self;
  
  weaken $runtime->{compiler};
  
  return $self;
}

sub compile_with_exit {
  my ($self, $class_name, $file, $line) = @_;
  
  $self->set_start_file($file);
  
  $self->set_start_line($line);
  
  eval { $self->compile($class_name); };
  
  if ($@) {
    Carp::confess(join("\n", @{$self->get_formatted_error_messages}));
  }
}

sub compile_anon_class_with_exit {
  my ($self, $source, $file, $line) = @_;
  
  $self->set_start_file($file);
  
  $self->set_start_line($line);
  
  my $anon_class_name;
  
  eval { $anon_class_name = $self->compile_anon_class($source); };
  
  if ($@) {
    Carp::confess(join("\n", @{$self->get_formatted_error_messages}));
  }
  
  return $anon_class_name;
}

1;

=head1 Name

SPVM::Builder::Native::Compiler - Compiler Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
