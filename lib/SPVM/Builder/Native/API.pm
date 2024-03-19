package SPVM::Builder::Native::API;

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

sub env {
  my $self = shift;
  if (@_) {
    $self->{env} = $_[0];
    return $self;
  }
  else {
    return $self->{env};
  }
}

sub stack {
  my $self = shift;
  if (@_) {
    $self->{stack} = $_[0];
    return $self;
  }
  else {
    return $self->{stack};
  }
}

1;

=head1 Name

SPVM::Builder::Native::API - Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
