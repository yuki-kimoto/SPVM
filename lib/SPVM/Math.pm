package SPVM::Math;

1;

=head1 NAME

SPVM::Math - Math Library

=head1 FUNCTIONS

=head2 INFINITYF

  sub INFINITYF : float ()

=head2 NANF

  sub NANF : float ()
  
=head2 isinff

  sub isinff : int($x : float)

=head2 isfinitef

  sub isfinitef : int($x : float)

=head2 isnanf

  sub isnanf : int ($x : float)
  
=head2 INFINITY

  sub INFINITY : double ()

=head2 NAN

  sub NAN : double ()
  
=head2 isinf

  sub isinf : int ($x : double)

=head2 isfinite

  sub isfinite : int ($x : double)

=head2 isnan

  sub isnan : int ($x : double)

=head2 E

B<sub E : double ()>

The double value that is closer than any other to e, the base of the natural logarithms.

=head2 PI

B<sub PI : double ()>

The double value that is closer than any other to pi, the ratio of the circumference of a circle to its diameter.

=head2 sin

B<sub sin : double ($x : double)>

Returns the trigonometric sine of an angle. Special cases:

=over 2

=item* If the argument is NaN or an infinity, then the result is NaN.

=item* If the argument is zero, then the result is a zero with the same sign as the argument.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - an angle, in radians.

B<Returns:>

the sine of the argument.

=head2 cos

B<sub cos : double ($x : double)>

Returns the trigonometric cosine of an angle. Special cases:

=over 2

=item* If the argument is NaN or an infinity, then the result is NaN.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - an angle, in radians.

B<Returns:>

the cosine of the argument.

=head2 tan

B<sub tan : double ($x : double)>

Returns the trigonometric tangent of an angle. Special cases:

=over 2

=item* If the argument is NaN or an infinity, then the result is NaN.

=item* If the argument is zero, then the result is a zero with the same sign as the argument.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - an angle, in radians.

B<Returns:>

the tangent of the argument.

=head2 asin

B<sub asin : double ($x : double)>

Returns the arc sine of a value; the returned angle is in the range -pi/2 through pi/2. Special cases:

=over 2

=item * If the argument is NaN or its absolute value is greater than 1, then the result is NaN.

=item * If the argument is zero, then the result is a zero with the same sign as the argument.

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - the value whose arc sine is to be returned.

B<Returns:>

the arc sine of the argument.

=head2 acos

B<sub acos : double ($x : double)>

Returns the arc cosine of a value; the returned angle is in the range 0.0 through pi. Special case:

=over 2

=item * If the argument is NaN or its absolute value is greater than 1, then the result is NaN.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - the value whose arc cosine is to be returned.

B<Returns:>

the arc cosine of the argument.

=head2 atan

B<sub atan : double ($x : double)>

Returns the arc tangent of a value; the returned angle is in the range -pi/2 through pi/2. Special cases:

=over 2

=item * If the argument is NaN, then the result is NaN.

=item * If the argument is zero, then the result is a zero with the same sign as the argument.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - the value whose arc tangent is to be returned.

B<Returns:>

the arc tangent of the argument.

=head2 erf

  sub erf : double ($x : double);

=head2 erfc

  sub erfc : double ($x : double);

=head2 BYTE_MIN

B<sub BYTE_MIN : byte ()>

A constant holding the minimum value a byte can have, C<-128>.

=head2 BYTE_MAX

B<BYTE_MAX : byte ()>

A constant holding the maximum value a byte can have, C<127>.

=head2 SHORT_MIN

B<sub SHORT_MIN : short ()>

A constant holding the minimum value a short can have, C<-32768>.

=head2 SHORT_MAX

B<sub SHORT_MAX : short ()>

A constant holding the maximum value a short can have, C<32767>.

=head2 INT_MIN

B<sub INT_MIN : int ()>

A constant holding the minimum value a int can have, C<-2147483648>.

=head2 INT_MAX

B<sub INT_MAX : int ()>

A constant holding the maximum value a int can have, C<2147483647>.

=head2 LONG_MIN

B<sub LONG_MIN : long ()>

A constant holding the minimum value a long can have, C<-9223372036854775808>.

=head2 LONG_MAX

B<sub LONG_MAX : long ()>

A constant holding the maximum value a long can have, C<9223372036854775807>.

=head2 FLT_MIN

B<sub FLT_MIN : float ()>

=head2 FLT_MAX

B<sub FLT_MAX : float ()>

=head2 DBL_MIN

B<sub DBL_MIN : double ()>

=head2 DBL_MAX

B<sub DBL_MAX : double ()>
