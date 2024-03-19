package SPVM::Builder::Native::Env;

use strict;
use warnings;

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

SPVM::Builder::Native::Env - Runtime Environment

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
