package SPVM::Std::TypeUtil;

1;

=head1 NAME

SPVM::Std::TypeUtil - Standard Type utilities

=head1 CLASS METHODS

=head2 BYTE_MIN

B<sub BYTE_MIN : byte ()>

A constant holding the minimum value a byte can have, C<-128>.

=head2 BYTE_MAX

B<BYTE_MAX : byte ()>

A constant holding the maximum value a byte can have, C<127>.

=head2 BYTE_BYTES

B<sub BYTE_BYTES : int ()>

The number of bytes used to represent a byte value in two's complement binary form, C<1>.

=head2 BYTE_SIZE

B<sub BYTE_SIZE : int ()>

The number of bits used to represent a byte value in two's complement binary form, C<8>.

=head2 SHORT_MIN

B<sub SHORT_MIN : short ()>

A constant holding the minimum value a short can have, C<-32768>.

=head2 SHORT_MAX

B<sub SHORT_MAX : short ()>

A constant holding the maximum value a short can have, C<32767>.

=head2 SHORT_BYTES

B<sub SHORT_BYTES : int ()>

The number of shorts used to represent a short value in two's complement binary form, C<2>.

=head2 SHORT_SIZE

B<sub SHORT_SIZE : int ()>

The number of bits used to represent a short value in two's complement binary form, C<16>.

=head2 INT_MIN

B<sub INT_MIN : int ()>

A constant holding the minimum value a int can have, C<-2147483648>.

=head2 INT_MAX

B<sub INT_MAX : int ()>

A constant holding the maximum value a int can have, C<2147483647>.

=head2 INT_BYTES

B<sub INT_BYTES : int ()>

The number of ints used to represent a int value in two's complement binary form, C<4>.

=head2 INT_SIZE

B<sub INT_SIZE : int ()>

The number of bits used to represent a int value in two's complement binary form, C<32>.

=head2 LONG_MIN

B<sub LONG_MIN : long ()>

A constant holding the minimum value a long can have, C<-9223372036854775808>.

=head2 LONG_MAX

B<sub LONG_MAX : long ()>

A constant holding the maximum value a long can have, C<9223372036854775807>.

=head2 LONG_BYTES

B<sub LONG_BYTES : int ()>

The number of longs used to represent a long value in two's complement binary form, C<8>.

=head2 LONG_SIZE

B<sub LONG_SIZE : int ()>

The number of bits used to represent a long value in two's complement binary form, C<64>.

=head2 FLOAT_MIN

B<sub FLOAT_MIN : float ()>

A constant holding the minimum value a float can have, C<-128>.

=head2 FLOAT_MAX

B<sub FLOAT_MAX : float ()>

A constant holding the maximum value a float can have, C<127>.

=head2 FLOAT_SIZE

B<sub FLOAT_SIZE : int ()>

The number of bits used to represent a float value in two's complement binary form.

=head2 FLOAT_BYTES

B<sub FLOAT_BYTES : int ()>

The number of floats used to represent a float value in two's complement binary form.

=head2 DOUBLE_MIN

B<sub DOUBLE_MIN : double ()>

A constant holding the minimum value a double can have, C<-128>.

=head2 DOUBLE_MAX

B<sub DOUBLE_MAX : double ()>

A constant holding the maximum value a double can have, C<127>.

=head2 DOUBLE_SIZE

B<sub DOUBLE_SIZE : int ()>

The number of bits used to represent a double value in two's complement binary form.

=head2 DOUBLE_BYTES

B<sub DOUBLE_BYTES : int ()>

The number of doubles used to represent a double value in two's complement binary form.

