package SPVM::Long;

1;

=head1 NAME

SPVM::Long - Long object

=head1 CLASS METHODS

=head2 new

  sub new : Long ($value : long)

Construct Long object with specified value.

=head1 METHODS

=head2 get_value

  sub get_value : long ($self : self)

Get value.

=head2 set_value

  sub set_value : void ($self : self, $value : long)

Set value.
