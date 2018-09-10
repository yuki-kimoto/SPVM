package SPVM::Byte;

1;

=head1 NAME

SPVM::Byte - Byte object

=head1 CLASS METHODS

=head2 new

  sub new : Byte ($value : byte)

Construct Byte object with specified value.

=head1 METHODS

=head2 val

  sub val : byte ($self : self)

Get value.

=head2 set_val

  sub set_val : void ($self : self, $value : byte)

Set value.
