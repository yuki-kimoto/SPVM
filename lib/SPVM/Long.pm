package SPVM::Long;

1;

=head1 NAME

SPVM::Long - Long Utility

=head1 CLASS METHODS

=head2 MIN_VALUE

B<sub MIN_VALUE : long ($class : class)>

A constant holding the minimum value a long can have, C<-9223372036854775808>.

=head2 MAX_VALUE

B<sub MAX_VALUE : long ($class : class)>

A constant holding the maximum value a long can have, C<9223372036854775807>.

=head2 BYTES

B<sub BYTES : int ($class : class)>

The number of longs used to represent a long value in two's complement binary form, C<8>.

=head2 SIZE

B<sub SIZE : int ($class : class)>

The number of bits used to represent a long value in two's complement binary form, C<64>.

