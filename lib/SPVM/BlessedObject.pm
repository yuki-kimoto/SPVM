package SPVM::BlessedObject;

use strict;
use warnings;

sub __api {
  my $self = shift;
  if (@_) {
    $self->{__api} = $_[0];
    return $self;
  }
  else {
    return $self->{__api};
  }
}

1;

=head1 Name

SPVM::BlessedObject - Blessed object base class

=head1 Description

SPVM::BlessedObject is blessed object base class.

Current subclasses is L<SPVM::BlessedObject::Array> and L<SPVM::BlessedObject::Class>.
