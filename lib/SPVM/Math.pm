package SPVM::Math;

1;

=head1 NAME

SPVM::Math - Math Library

=head1 FUNCTIONS

=head2 E

B<double E()>

The double value that is closer than any other to e, the base of the natural logarithms.

=head2 PI

B<double PI()>

The double value that is closer than any other to pi, the ratio of the circumference of a circle to its diameter.

=head2 sin

B<double sin(double $x)>

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

B<double cos(double $x)>

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

B<double tan(double $x)>

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

B<double asin(double $x)>

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

B<public static double acos(double $x)>

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

B<double atan(double $x)>

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

=head2 to_radians

B<double toRadians(double angdeg)>

Converts an angle measured in degrees to an approximately equivalent angle measured in radians. The conversion from degrees to radians is generally inexact.

B<Parameters:>

angdeg - an angle, in degrees

B<Returns:>

the measurement of the angle angdeg in radians.
