package SPVM::BlessedObject;

use strict;
use warnings;

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

SPVM::BlessedObject - Blessed object base class

=head1 Description

SPVM::BlessedObject is blessed object base class.

Current subclasses is L<SPVM::BlessedObject::Array> and L<SPVM::BlessedObject::Class>.
