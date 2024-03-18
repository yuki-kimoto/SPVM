package SPVM::Builder::ClassFile;

use strict;
use warnings;

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

1;

=head1 Name

SPVM::Builder::ClassFile - Class File Builder APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License