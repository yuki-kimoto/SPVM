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

sub module_dirs {
  my $self = shift;
  if (@_) {
    $self->{module_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{module_dirs};
  }
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  $self->create_compiler;
  
  return $self;
}

1;
