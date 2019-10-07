=head1 NAME

SPVM::CORE - SPVM core functions

=head1 CLASS METHODS

=head2 chompr

  sub chompr : string ($string : string)

Copy the string and remove the newline "\n" from the end of string and return it.

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
