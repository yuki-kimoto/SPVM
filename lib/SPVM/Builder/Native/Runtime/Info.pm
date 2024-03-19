package SPVM::Builder::Native::Runtime::Info;

use strict;
use warnings;

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

# Class Methods
sub new {
  my $class = shift;
  
  my $self = bless {
    @_;
  }, __PACKAGE__;
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::Native::Runtime::Info - Runtime Information

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
