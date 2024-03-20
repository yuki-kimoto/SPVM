package SPVM::Builder::Native::Method;

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

SPVM::Builder::Native::Method - Method Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
