package SPVM::BlessedObject;

use strict;
use warnings;

sub api {
  my $self = shift;
  if (@_) {
    $self->{api} = $_[0];
    return $self;
  }
  else {
    return $self->{api};
  }
}

1;

=head1 Name

SPVM::BlessedObject - Blessed object base class

=head1 Description

SPVM::BlessedObject is blessed object base class.

Current subclasses is L<SPVM::BlessedObject::Array> and L<SPVM::BlessedObject::Class>.
