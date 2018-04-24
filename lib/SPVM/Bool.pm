package SPVM::Bool;

1;

=head1 NAME

SPVM::Bool - Bool Utility

=head1 CLASS METHODS

=head2 new_true

  sub new_true : Bool ()

Construct Byte object with true.

=head2 new_false

  sub new_false : Bool ()

Construct Byte object with false.

=head1 METHODS

=head2 is_true

  sub is_true : int ($self : self)

Check if the value is true.

=head2 set_true

  sub set_true : void ($self : self)

Set true.

=head2 set_false

  sub set_false : void ($self : self)

Set false.
