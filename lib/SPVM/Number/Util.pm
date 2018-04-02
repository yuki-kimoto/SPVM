package SPVM::Number::Util;

1;

=head1 NAME

SPVM::Number::Util - Number utility

=head1 CLASS METHODS

=head2 BYTE_MIN_VALUE

B<sub BYTE_MIN_VALUE : byte ($class : class)>

A constant holding the minimum value a byte can have, C<-128>.

=head2 BYTE_MAX_VALUE

B<BYTE_MAX_VALUE : byte ($class : class)>

A constant holding the maximum value a byte can have, C<127>.

=head2 BYTE_BYTES

B<sub BYTE_BYTES : int ($class : class)>

The number of bytes used to represent a byte value in two's complement binary form, C<1>.

=head2 BYTE_SIZE

B<sub BYTE_SIZE : int ($class : class)>

The number of bits used to represent a byte value in two's complement binary form, C<8>.
