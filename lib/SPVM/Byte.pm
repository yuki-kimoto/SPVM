package SPVM::Byte;

1;

=head1 NAME

SPVM::Byte - Byte Utility

=head1 CLASS METHODS

=head2 MIN_VALUE

B<sub MIN_VALUE : byte ($class : class)>

A constant holding the minimum value a byte can have, C<-128>.

=head2 MAX_VALUE

B<MAX_VALUE : byte ($class : class)>

A constant holding the maximum value a byte can have, C<127>.

=head2 BYTES

B<sub BYTES : int ($class : class)>

The number of bytes used to represent a byte value in two's complement binary form, C<1>.

=head2 SIZE

B<sub SIZE : int ($class : class)>

The number of bits used to represent a byte value in two's complement binary form, C<8>.
