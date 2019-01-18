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

=head2 E

B<sub E : double ()>

The double value that is closer than any other to e, the base of the natural logarithms.

=head2 PI

B<sub PI : double ()>

The double value that is closer than any other to pi, the ratio of the circumference of a circle to its diameter.

=head2 time

Get epoch time.

  sub time : long ();

Wapper of time of C99 time library.

=head2 INFINITYF

  sub INFINITYF : float ()

Wapper of INFINITY of C99 math library.

=head2 NANF

  sub NANF : float ()

Wapper of NAN of C99 math library.
  
=head2 isinff

  sub isinff : int($x : float)

Wapper of isinf of C99 math library.

=head2 isfinitef

  sub isfinitef : int($x : float)

Wapper of isfinite of C99 math library.

=head2 isnanf

  sub isnanf : int ($x : float)

Wapper of isnan of C99 math library.
  
=head2 INFINITY

  sub INFINITY : double ()

Wapper of INFINITY of C99 math library.

=head2 NAN

  sub NAN : double ()

Wapper of NAN of C99 math library.
  
=head2 isinf

  sub isinf : int ($x : double)

Wapper of isinf of C99 math library.

=head2 isfinite

  sub isfinite : int ($x : double)

Wapper of isfinite of C99 math library.

=head2 isnan

  sub isnan : int ($x : double)

Wapper of isnan of C99 math library.

=head2 sin

B<sub sin : double ($x : double)>

Wapper of sin of C99 math library.

=head2 cos

B<sub cos : double ($x : double)>

Wapper of cos of C99 math library.

=head2 tan

B<sub tan : double ($x : double)>

Wapper of tan of C99 math library.

=head2 asin

B<sub asin : double ($x : double)>

Wapper of asin of C99 math library.

=head2 acos

B<sub acos : double ($x : double)>

Wapper of acos of C99 math library.

=head2 atan

B<sub atan : double ($x : double)>

Wapper of atan of C99 math library.

=head2 erf

  sub erf : double ($x : double);

Wapper of erf of C99 math library.

=head2 erfc

  sub erfc : double ($x : double);

Wapper of erf of C99 math library.

=head2 INT8_MIN

B<sub INT8_MIN : byte ()>

Wapper of INT8_MIN of C99 cstdint library.

=head2 INT8_MAX

B<INT8_MAX : byte ()>

Wapper of INT8_MAX of C99 cstdint library.

=head2 INT16_MIN

B<sub INT16_MIN : short ()>

Wapper of INT16_MIN of C99 cstdint library.

=head2 INT16_MAX

B<sub INT16_MAX : short ()>

Wapper of INT16_MAX of C99 cstdint library.

=head2 INT32_MIN

B<sub INT32_MIN : int ()>

Wapper of INT32_MIN of C99 cstdint library.

=head2 INT32_MAX

B<sub INT32_MAX : int ()>

Wapper of INT32_MAX of C99 cstdint library.

=head2 INT64_MIN

B<sub INT64_MIN : long ()>

Wapper of INT64_MIN of C99 cstdint library.

=head2 INT64_MAX

B<sub INT64_MAX : long ()>

Wapper of INT64_MAX of C99 cstdint library.

=head2 FLT_MIN

B<sub FLT_MIN : float ()>

Wapper of FLT_MIN of C99 float library.

=head2 FLT_MAX

B<sub FLT_MAX : float ()>

Wapper of FLT_MAX of C99 float library.

=head2 DBL_MIN

B<sub DBL_MIN : double ()>

Wapper of DBL_MIN of C99 float library.

=head2 DBL_MAX

B<sub DBL_MAX : double ()>

Wapper of DBL_MAX of C99 float library.

=head2 copy_string

B<sub copy_string : string ($string : string)>
  
  my $string = "abced";
  my $string_copy = copy_string($string);

Copy string.

=head2 copy_barray

B<sub copy_barray : byte[] ($nums : byte[])>

  my $nums = [(byte)1, 2, 3];
  my $nums_copy = copy_barray($nums);
  
Copy byte array.

=head2 copy_sarray

B<sub copy_sarray : short[] ($nums : short[])>

  my $nums = [(short)1, 2, 3];
  my $nums_copy = copy_sarray($nums);

Copy short array.

=head2 copy_iarray

B<sub copy_iarray : int[] ($nums : int[])>

  my $nums = [1, 2, 3];
  my $nums_copy = copy_iarray($nums);

Copy int array.

=head2 copy_larray

B<sub copy_larray : long[] ($nums : long[])>

  my $nums = [(long)1, 2, 3];
  my $nums_copy = copy_larray($nums);

Copy long array.
  
=head2 copy_farray

B<sub copy_farray : float[] ($nums : float[])>

  my $nums = [0.5f, 0.25f, 0.3f];
  my $nums_copy = copy_farray($nums);

Copy float array.

=head2 copy_darray

B<sub copy_darray : double[] ($nums : double[])>

  my $nums = [0.5, 0.25, 0.3];
  my $nums_copy = copy_darray($nums);

Copy double array.

=head2 copy_oarray

B<sub copy_oarray : object[] ($objects : object[])>

  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = copy_oarray($objects);

Copy object array.

Array is sharrow copy, not deeply copy.
