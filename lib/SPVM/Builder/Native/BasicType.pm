package SPVM::Builder::Native::BasicType;

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

sub runtime {
  my $self = shift;
  if (@_) {
    $self->{runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{runtime};
  }
}

1;

=head1 Name

SPVM::Builder::Native::BasicType - Basic Type Builder APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
