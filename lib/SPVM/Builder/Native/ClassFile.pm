package SPVM::Builder::Native::ClassFile;

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

SPVM::Builder::Native::ClassFile - Class File Native APIs

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
