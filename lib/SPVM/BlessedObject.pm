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

sub __get_type_name { my $ret; eval { $ret =  shift->_xs___get_type_name(@_) }; if ($@) { confess $@ } $ret; }

1;

=head1 Name

SPVM::BlessedObject - SPVM object

=head1 Description

The object of the C<SPVM::BlessedObject> class holds a SPVM object.

=head1 Instance Methods

=head2 __api

  my $api = $self->__api;
  $self->__api($api);

Gets and sets a L<SPVM::ExchangeAPI> object.

=head2 __get_type_name

  my $type_name = $self->__get_type_name;

Gets the SPVM type name of the object.

=head1 Well Known Child Classes

=over 2

=item * L<SPVM::BlessedObject::String>

=item * L<SPVM::BlessedObject::Array>

=item * L<SPVM::BlessedObject::Class>

=back
