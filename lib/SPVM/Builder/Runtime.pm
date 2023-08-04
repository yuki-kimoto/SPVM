package SPVM::Builder::Runtime;

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

1;

=head1 Name

SPVM::Builder::Runtime - SPVM Builder Runtime

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
