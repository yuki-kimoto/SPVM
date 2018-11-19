=head1 NAME

SPVM::CORE - SPVM Standard Functions

=head1 SPVM Standard Functions

=head1 FUNCTIONS

=head2 print

Print string to stdout.

  sub print : void ($string : string);

=head2 warn

Print string with file name and line number to stderr. line break is added to end of string.

  sub warn : void ($string : string);

=head2 time

Get epoch time.

  sub time : long ();

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

=back

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

=head2 INT8_MIN

B<sub INT8_MIN : byte ()>

=head2 INT8_MAX

B<INT8_MAX : byte ()>

=head2 INT16_MIN

B<sub INT16_MIN : short ()>

=head2 INT16_MAX

B<sub INT16_MAX : short ()>

=head2 INT32_MIN

B<sub INT32_MIN : int ()>

=head2 INT32_MAX

B<sub INT32_MAX : int ()>

=head2 INT64_MIN

B<sub INT64_MIN : long ()>

=head2 INT64_MAX

B<sub INT64_MAX : long ()>

=head2 FLT_MIN

B<sub FLT_MIN : float ()>

=head2 FLT_MAX

B<sub FLT_MAX : float ()>

=head2 DBL_MIN

B<sub DBL_MIN : double ()>

=head2 DBL_MAX

B<sub DBL_MAX : double ()>

=head2 copy_string

B<sub copy_string : string ($string : string)>
  
  my $string = "abced";
  my $string_copy = copy_string $string;

Copy string.

=head2 copy_byte_array

B<sub copy_byte_array : byte[] ($nums : byte[])>

  my $nums = [(byte)1, 2, 3];
  my $nums_copy = copy_byte_array $nums;
  
Copy byte array.

=head2 copy_short_array

B<sub copy_short_array : short[] ($nums : short[])>

  my $nums = [(short)1, 2, 3];
  my $nums_copy = copy_short_array $nums;

Copy short array.

=head2 copy_int_array

B<sub copy_int_array : int[] ($nums : int[])>

  my $nums = [1, 2, 3];
  my $nums_copy = copy_int_array $nums;

Copy int array.

=head2 copy_long_array

B<sub copy_long_array : long[] ($nums : long[])>

  my $nums = [(long)1, 2, 3];
  my $nums_copy = copy_long_array $nums;

Copy long array.
  
=head2 copy_float_array

B<sub copy_float_array : float[] ($nums : float[])>

  my $nums = [0.5f, 0.25f, 0.3f];
  my $nums_copy = copy_float_array $nums;

Copy float array.

=head2 copy_double_array

B<sub copy_double_array : double[] ($nums : double[])>

  my $nums = [0.5, 0.25, 0.3];
  my $nums_copy = copy_double_array $nums;

Copy double array.

=head2 copy_object_array

B<sub copy_object_array : object[] ($objects : object[])>

  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = copy_object_array $objects;

Copy object array.

Array is sharrow copy, not deeply copy.
