package SPVM::Array;

1;

=encoding utf8

=head1 Name

SPVM::Array - Array Utilities

=head1 Usage

  use Array;
  
  # Copy a byte array
  {
    my $array = [(byte)1, 2, 3];
    my $array_copy = Array->copy_byte($array);
  }

  # Copy a short array
  {
    my $array = [(short)1, 2, 3];
    my $array_copy = Array->copy_short($array);
  }

  # Copy a int array
  {
    my $array = [1, 2, 3];
    my $array_copy = Array->copy_int($array);
  }

  # Copy a long array
  {
    my $array = [(long)1, 2, 3];
    my $array_copy = Array->copy_long($array);
  }

  # Copy a float array
  {
    my $array = [1.5f, 2.5f, 3.5f];
    my $array_copy = Array->copy_float($array);
  }

  # Copy a double array
  {
    my $array = [1.5, 2.5, 3.5];
    my $array_copy = Array->copy_double($array);
  }
  
  # Copy a string array
  {
    my $array = ["abc", "def", "ghi"]
    my $array_copy = Array->copy_string($array);
  }
  
  # Check if the two byte arrays equal
  {
    my $array1 = [(byte)1, 2];
    my $array2 = [(byte)1, 2];
    my $ret = Array->equals_byte($array1, $array2);
  }

  # Check if the two short arrays equal
  {
    my $array1 = [(short)1, 2];
    my $array2 = [(short)1, 2];
    my $ret = Array->equals_short($array1, $array2);
  }

  # Check if the two int arrays equal
  {
    my $array1 = [(int)1, 2];
    my $array2 = [(int)1, 2];
    my $ret = Array->equals_int($array1, $array2);
  }

  # Check if the two long arrays equal
  {
    my $array1 = [(long)1, 2];
    my $array2 = [(long)1, 2];
    my $ret = Array->equals_long($array1, $array2);
  }

  # Check if the two float arrays equal
  {
    my $array1 = [(float)1, 2];
    my $array2 = [(float)1, 2];
    my $ret = Array->equals_float($array1, $array2);
  }

  # Check if the two double arrays equal
  {
    my $array1 = [(double)1, 2];
    my $array2 = [(double)1, 2];
    my $ret = Array->equals_double($array1, $array2);
  }

  # Check if the two string arrays equal
  {
    my $array1 = ["abc", "def"];
    my $array2 = ["abc", "def"];
    my $ret = Array->equals_string($array1, $array2);
  }
  
  # Copy object array
  my $array = [(object)Int->new(1), Int->new(2), Int->new(3)];
  my $array_copy = Array->copy_object($array, method : object ($obj : object) {
    my $int_obj = (Int)$obj;
    my $new_int_obj = Int->new($int_obj->value);
    return $new_int_obj;
  });

=head1 Description

C<Array> provides array utilities.

=head1 Class Methods

=head2 copy_byte

  static method copy_byte : byte[] ($array : byte[], $offset = 0 : int, $length = -1 : int);

Create a new C<byte> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_double

  static method copy_double : double[] ($array : double[], $offset = 0 : int, $length = -1 : int);

Create a new C<double> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

If the array is not defined, return C<undef>.

=head2 copy_float

  static method copy_float : float[] ($array : float[], $offset = 0 : int, $length = -1 : int);

Create a new C<float> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_int

  static method copy_int : int[] ($array : int[], $offset = 0 : int, $length = -1 : int);

Create a new C<int> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.
  
=head2 copy_long

  static method copy_long : long[] ($array : long[], $offset = 0 : int, $length = -1 : int);

Create a new C<long> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_object

  static method copy_object : object[] ($array : object[], $cloner = undef : Cloner, $offset = 0 : int, $legnth = -1 : int);

Create a new object array with the C<$length>, and clone the elements of the object array from the C<$offset> to the position proceeded by the C<$length> to the created array.

Each element is cloned by the L<Cloner|SPVM::Cloner>.

If the cloner is not defined, the address of each element is copied.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_object_address

  static method copy_object_address : object[] ($array : object[], $offset = 0 : int, $legnth = -1 : int);

The alias for the following code using L</"copy_object">.

  my $ret = &copy_object($array, undef, $offset, $length);

=head2 copy_short

  static method copy_short : short[] ($array : short[], $offset = 0 : int, $length = -1 : int);

Create a new C<short> array with the C<$length>, and copy the elements from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_string

  static method copy_string : string[] ($array : string[], $offset = 0 : int, $length = -1 : int);

Create a new C<string> array with the C<$length>, and copy the elements of the C<string> array using C<copy> operator from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 copy_string_address

  static method copy_string_address : string[] ($array : string[], $offset = 0 : int, $length = -1 : int);

Create a new C<string> array with the C<$length>, and copy the addresses of the elements of the C<string> array from the C<$offset> to the position proceeded by the C<$length> to the created array.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 dump_unsigned_byte

  static method dump_unsigned_byte : string ($array : byte[]);

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 8-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_int

  static method dump_unsigned_int : string ($array : int[]);

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 32-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_long

  static method dump_unsigned_long : string ($array : long[]);

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 64-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_short

  static method dump_unsigned_short : string ($array : short[]);

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 16-bit integer.

  my $ret = dump $array;

=head2 equals_byte

  static method equals_byte : int ($array1 : byte[], $array2 : byte[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_double

  static method equals_double : int ($array1 : double[], $array2 : double[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_float

  static method equals_float : int ($array1 : float[], $array2 : float[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_int

  static method equals_int : int ($array1 : int[], $array2 : int[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_long

  static method equals_long : int ($array1 : long[], $array2 : long[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_object

  static method static method equals_object : int ($array1 : object[], $array2 : object[], $equality_checker : EqualityChecker);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2> using the equality checker, return C<1>.

The equality checker is not defined, the address is used to check the equality.

Otherwise return C<0>.

=head2 equals_object_address

  static method equals_object_address : int ($array1 : object[], $array2 : object[]);

The alias for the following code using L</"equals_object">.

  my $ret = &equals_object($array1, $array2, undef);

=head2 equals_short

  static method equals_short : int ($array1 : short[], $array2 : short[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2>, return C<1>.

Otherwise return C<0>.

=head2 equals_string

  static method equals_string : int ($array1 : string[], $array2 : string[]);

If the C<$array1> is not defined and the C<$array2> is not defined, return C<1>.

If the C<$array1> is defined and the C<$array2> is not defined, return C<0>.

If the C<$array1> is not defined, the C<$array2> is defined, return C<0>.

If the C<$array1> is defined and the C<$array2> is defined and the all elements of C<$array1> are equal to all elements of C<$array2> using the C<eq> operator, return C<1>.

Otherwise return C<0>.

=head2 equals_string_address

  static method equals_string_address : int ($array1 : string[], $array2 : string[]);

The alias for the following code using L</"equals_object_address">.

  my $ret = &equals_object_address($array1, $array2);

=head2 memcpy_byte

  static method memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<byte> array to the range of the elements of the C<$dest> C<byte> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_double
  
  static method memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<double> array to the range of the elements of the C<$dest> C<double> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_float
  
  static method memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<float> array to the range of the elements of the C<$dest> C<float> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_int
  
  static method memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<int> array to the range of the elements of the C<$dest> C<int> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_long
  
  static method memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<long> array to the range of the elements of the C<$dest> C<long> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_object_address

  static method memcpy_object_address : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> object array to the range of the elements of the C<$dest> object array.

Each address is copied.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_short

  static method memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int);

Copy the range of the elements of the C<$source> C<short> array to the range of the elements of the C<$dest> C<short> array.

The range of the elements of the C<$source> array is from the C<$offset> to the position proceeded by the C<$length> of the source.

The range of the elements of the C<$dest> array is from the C<$dest_offset> to the C<$dest_offset> + the C<$length>.

If the range of the elements of the C<$source> array and the range of the elements of the C<$dest> array overlap, the result is B<not> guaranteed.

Exceptions:

The C<$dest> must be defined.

The C<$source> must be defined.

The C<$length> must be greater than or equal to C<0>.

The C<$dest_offset> must be greater than or equal to C<0>.

The C<$source_offset> must be greater than or equal to C<0>.

The C<$dest_offset> + the C<$length> must be less than or equal to the length of the C<$dest>.

The C<$source_offset> + the C<$length> must be less than or equal to the length of the C<$source>.

=head2 memcpy_string_address

  static method memcpy_string_address : void ($dest : string[], $dest_offset : int, $source : string[], $source_offset : int, $length : int);

The alias for L</"memcpy_object_address">.

=head2 memmove_byte

  static method memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int);

The same as L</"memcpy_byte">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_double
  
  static method memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int);

The same as L</"memcpy_double">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_float
  
  static method memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int);

The same as L</"memcpy_float">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_int
  
  static method memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int);

The same as L</"memcpy_int">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_long
  
  static method memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int);

The same as L</"memcpy_long">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_object_address

  static method memmove_object_address : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int);

The same as L</"memcpy_object_address">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_short

  static method memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int);

The same as L</"memcpy_short">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_string_address

  static method memmove_string_address : void ($dest : string[], $dest_offset : int, $source : string[], $source_offset : int, $length : int);

The same as the following code using L</"memmove_object_address">.

  &memmove_object_address($dest, $dest_offset, $source, $source_offset, $length);

=head2 memset_byte

  static method memset_byte : void ($array : byte[], $element : int, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<byte> array to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_double

  static method memset_double : void ($array : double[], $element : double, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<double> array to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_float

  static method memset_float : void ($array : float[], $element : float, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<float> array to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_int

  static method memset_int : void ($array : int[], $element : int, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<int> array to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_long

  static method memset_long : void ($array : long[], $element : long, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<long> array to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_object

  static method memset_object : void ($array : object[], $element : object, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the object C<$array> to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_short

  static method memset_short : void ($array : short[], $element : int, $offset = 0 : int, $length = -1 : int);

Set the range of the elements of the C<short> C<$array> to the C<$element>.

The range of the elements of the C<$array> is from the C<$offset> to the position proceeded by the C<$length>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

The C<$array> must be defined.

The C<$offset> must be greater than or equal to C<0>.

The C<$offset> + the C<$length> must be less than or equal to the length of the C<$array>.

=head2 memset_string

  static method memset_string : void ($array : string[], $element : string, $offset = 0 : int, $length = -1 : int);

The alias for the following code using L</"memset_object">.

  &memset_object($dest, $element, $dest_offset, $length);

=head2 new_proto

  static method new_proto : object[] ($proto_array : object[], $length : int);

Create a new object array as the same type as the C<$proto_array> with the C<$length>.

Exceptions:

The C<$prototype> array must be defined.

The C<$length> must be greater than or equal to C<0>.
