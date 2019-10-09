=head1 NAME

SPVM::CORE - SPVM core functions

=head2 DESCRIPTION

SPVM::CORE is SPVM core functions.

=head2 SYNOPSYS
  
  # Cut a newline
  {
    my $ret = chompr("abc\n");
  }
  
  # Create a new float complex array
  {
    my $re_values = [1.5f, 2.5f, 3.5f];
    my $im_values = [5.5f, 6.5f, 7.5f];
    my $farray = complex_farray($re_values, $im_values);
  }

  # Create a new double complex array
  {
    my $re_values = [1.5, 2.5, 3.5];
    my $im_values = [5.5, 6.5, 7.5];
    my $farray = complex_darray($re_values, $im_values);
  }
  
  # Create a new float complex value
  {
    my $z = complexf(1.5f, 2.5f);
  }

  # Create a new double complex value
  {
    my $z = complexd(1.5f, 2.5f);
  }
  
  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = copy_barray($nums);
  }

  # Copy a string
  {
    my $str = "abc";
    my $str_copy = copy_str($str);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = copy_sarray($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = copy_iarray($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = copy_larray($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = copy_farray($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = copy_darray($nums);
  }
  
=head1 CLASS METHODS

=head2 chompr

  sub chompr : string ($string : string)

Copy the string and remove the newline "\n" from the end of string and return it.

=head2 complex_farray

  sub complex_farray : SPVM::Complex_2f[] ($re_values : float[], $im_values : float[])

Create a new array of L<SPVM::Complex_2f> with real values and imaginary values.

=head2 complex_darray

  sub complex_darray : SPVM::Complex_2d[] ($re_values : double[], $im_values : double[])

Create a new array of L<SPVM::Complex_2d> with real values and imaginary values.

=head2 complexf

  sub complexf : SPVM::Complex_2f ($re : float, $im : float)

Return a new value of L<SPVM::Complex_2f>.

=head2 complexd

sub complexd : SPVM::Complex_2d ($re : double, $im : double)

Return a new value of L<SPVM::Complex_2d>.

=head2 copy_barray

  sub copy_barray : byte[] ($nums : byte[])

Copy a byte array.

=head2 

  sub copy_str : string ($string : string)

Copy a string.

=head2 

  sub copy_sarray : short[] ($nums : short[])

Copy a short array.
  
=head2 

  sub copy_iarray : int[] ($nums : int[])

Copy a int array.
  
=head2 

  sub copy_larray : long[] ($nums : long[])

Copy a long array.

=head2 

  sub copy_farray : float[] ($nums : float[])

Copy a float array.

=head2 

  sub copy_darray : double[] ($nums : double[])

Copy a double array.

=head2 

  sub copy_strarray : string[] ($strings : string[])

Copy a string array.

=head2 print

Print string to stdout.

  sub print : void ($string : string);

=head2 warn

Print string with file name and line number to stderr. line break is added to end of string.

  sub warn : void ($string : string);
  
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

=head2 copy_str

B<sub copy_str : string ($string : string)>
  
  my $string = "abced";
  my $string_copy = copy_str($string);

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
