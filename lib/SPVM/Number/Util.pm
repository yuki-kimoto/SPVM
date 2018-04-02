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

=head2 SHORT_MIN_VALUE

B<sub SHORT_MIN_VALUE : short ($class : class)>

A constant holding the minimum value a short can have, C<-32768>.

=head2 SHORT_MAX_VALUE

B<sub SHORT_MAX_VALUE : short ($class : class)>

A constant holding the maximum value a short can have, C<32767>.

=head2 SHORT_BYTES

B<sub SHORT_BYTES : int ($class : class)>

The number of shorts used to represent a short value in two's complement binary form, C<2>.

=head2 SHORT_SIZE

B<sub SHORT_SIZE : int ($class : class)>

The number of bits used to represent a short value in two's complement binary form, C<16>.
