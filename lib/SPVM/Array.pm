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

C<static method copy_byte : byte[] ($array : byte[], $offset : int = 0, $length : int = -1);>

Create a new C<byte> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_double

C<static method copy_double : double[] ($array : double[], $offset : int = 0, $length : int = -1);>

Create a new C<double> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

If the array is not defined, return undef.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_float

C<static method copy_float : float[] ($array : float[], $offset : int = 0, $length : int = -1);>

Create a new C<float> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_int

C<static method copy_int : int[] ($array : int[], $offset : int = 0, $length : int = -1);>

Create a new C<int> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.
  
=head2 copy_long

C<static method copy_long : long[] ($array : long[], $offset : int = 0, $length : int = -1);>

Create a new C<long> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_object

C<static method copy_object : object[] ($array : object[], $cloner : L<Cloner|SPVM::Cloner> = undef, $offset : int = 0, $legnth : int = -1);>

Create a new object array with $length, and clone the elements of the object array from $offset to the position proceeded by $length to the created array.

Each element is cloned by the L<Cloner|SPVM::Cloner>.

If the cloner is not defined, the address of each element is copied.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_object_address

C<static method copy_object_address : object[] ($array : object[], $offset : int = 0, $legnth : int = -1);>

The alias for the following code using L</"copy_object">.

  my $ret = &copy_object($array, undef, $offset, $length);

=head2 copy_short

C<static method copy_short : short[] ($array : short[], $offset : int = 0, $length : int = -1);>

Create a new C<short> array with $length, and copy the elements from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_string

C<static method copy_string : string[] ($array : string[], $offset : int = 0, $length : int = -1);>

Create a new C<string> array with $length, and copy the elements of the C<string> array using C<copy> operator from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 copy_string_address

C<static method copy_string_address : string[] ($array : string[], $offset : int = 0, $length : int = -1);>

Create a new C<string> array with $length, and copy the addresses of the elements of the C<string> array from $offset to the position proceeded by $length to the created array.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 dump_unsigned_byte

C<static method dump_unsigned_byte : string ($array : byte[]);>

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 8-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_int

C<static method dump_unsigned_int : string ($array : int[]);>

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 32-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_long

C<static method dump_unsigned_long : string ($array : long[]);>

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 64-bit integer.

  my $ret = dump $array;

=head2 dump_unsigned_short

C<static method dump_unsigned_short : string ($array : short[]);>

Same as the following code using the L<dump operator|SPVM::Document::Language/"dump Operator"> operator, but the elements are displayed as unsigned 16-bit integer.

  my $ret = dump $array;

=head2 equals_byte

C<static method equals_byte : int ($array1 : byte[], $array2 : byte[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_double

C<static method equals_double : int ($array1 : double[], $array2 : double[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_float

C<static method equals_float : int ($array1 : float[], $array2 : float[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_int

C<static method equals_int : int ($array1 : int[], $array2 : int[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_long

C<static method equals_long : int ($array1 : long[], $array2 : long[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_object

C<static method static method equals_object : int ($array1 : object[], $array2 : object[], $equality_checker : L<EqualityChecker|SPVM::EqualityChecker>);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2 using the equality checker, return 1.

The equality checker is not defined, the address is used to check the equality.

Otherwise return 0.

=head2 equals_object_address

C<static method equals_object_address : int ($array1 : object[], $array2 : object[]);>

The alias for the following code using L</"equals_object">.

  my $ret = &equals_object($array1, $array2, undef);

=head2 equals_short

C<static method equals_short : int ($array1 : short[], $array2 : short[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2, return 1.

Otherwise return 0.

=head2 equals_string

C<static method equals_string : int ($array1 : string[], $array2 : string[]);>

If $array1 is not defined and $array2 is not defined, return 1.

If $array1 is defined and $array2 is not defined, return 0.

If $array1 is not defined, $array2 is defined, return 0.

If $array1 is defined and $array2 is defined and the all elements of $array1 are equal to all elements of $array2 using the C<eq> operator, return 1.

Otherwise return 0.

=head2 equals_string_address

C<static method equals_string_address : int ($array1 : string[], $array2 : string[]);>

The alias for the following code using L</"equals_object_address">.

  my $ret = &equals_object_address($array1, $array2);

=head2 memcpy_byte

C<static method memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<byte> array to the range of the elements of $dest C<byte> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_double
  
C<static method memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<double> array to the range of the elements of $dest C<double> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_float
  
C<static method memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<float> array to the range of the elements of $dest C<float> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_int
  
C<static method memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<int> array to the range of the elements of $dest C<int> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_long
  
C<static method memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<long> array to the range of the elements of $dest C<long> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_object_address

C<static method memcpy_object_address : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int);>

Copy the range of the elements of $source object array to the range of the elements of $dest object array.

Each address is copied.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_short

C<static method memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int);>

Copy the range of the elements of $source C<short> array to the range of the elements of $dest C<short> array.

The range of the elements of $source array is from $offset to the position proceeded by $length of the source.

The range of the elements of $dest array is from $dest_offset to $dest_offset + $length.

If the range of the elements of $source array and the range of the elements of $dest array overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$source_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memcpy_string_address

C<static method memcpy_string_address : void ($dest : string[], $dest_offset : int, $source : string[], $source_offset : int, $length : int);>

The alias for L</"memcpy_object_address">.

=head2 memmove_byte

C<static method memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int);>

The same as L</"memcpy_byte">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_double
  
C<static method memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int);>

The same as L</"memcpy_double">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_float
  
C<static method memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int);>

The same as L</"memcpy_float">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_int
  
C<static method memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int);>

The same as L</"memcpy_int">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_long
  
C<static method memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int);>

The same as L</"memcpy_long">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_object_address

C<static method memmove_object_address : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int);>

The same as L</"memcpy_object_address">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_short

C<static method memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int);>

The same as L</"memcpy_short">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 memmove_string_address

C<static method memmove_string_address : void ($dest : string[], $dest_offset : int, $source : string[], $source_offset : int, $length : int);>

The same as the following code using L</"memmove_object_address">.

  &memmove_object_address($dest, $dest_offset, $source, $source_offset, $length);

=head2 memset_byte

C<static method memset_byte : void ($array : byte[], $element : int, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<byte> array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_double

C<static method memset_double : void ($array : double[], $element : double, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<double> array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_float

C<static method memset_float : void ($array : float[], $element : float, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<float> array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_int

C<static method memset_int : void ($array : int[], $element : int, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<int> array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_long

C<static method memset_long : void ($array : long[], $element : long, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<long> array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_object

C<static method memset_object : void ($array : object[], $element : object, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the object $array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_short

C<static method memset_short : void ($array : short[], $element : int, $offset : int = 0, $length : int = -1);>

Set the range of the elements of the C<short> $array to $element.

The range of the elements of $array is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $array. Otherwise an exception is thrown.

=head2 memset_string

C<static method memset_string : void ($array : string[], $element : string, $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"memset_object">.

  &memset_object($dest, $element, $dest_offset, $length);

=head2 merge_byte

C<static method merge_byte : byte[] ($array1 : byte[], $array2 : byte[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_short

C<static method merge_short : short[] ($array1 : short[], $array2 : short[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_int

C<static method merge_int : int[] ($array1 : int[], $array2 : int[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_long

C<static method merge_long : long[] ($array1 : long[], $array2 : long[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_float

C<static method merge_float : float[] ($array1 : float[], $array2 : float[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_double

C<static method merge_double : double[] ($array1 : double[], $array2 : double[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_string

C<static method merge_string : string[] ($array1 : string[], $array2 : string[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 merge_object

C<static method merge_object : object[] ($array1 : object[], $array2 : object[]);>

Creates a new array by merging the array $array1 and the array $array2, and returns it.

Exceptions:

\$array1 must be defined. Otherwise an exception is thrown.

\$array2 must be defined. Otherwise an exception is thrown.

=head2 new_proto

C<static method new_proto : object[] ($proto_array : object[], $length : int);>

Create a new object array as the same type as $proto_array with $length.

Exceptions:

$prototype array must be defined. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 shuffle_object

C<static method shuffle_object : void ($array : object[], $seed_ref : int*);>

Shuffles the array $array with the reference to a seed $seed_ref.

Exceptions:

$array must be defined. Otherwise an exception is thrown.

=head2 repeat_string

C<static method repeat_string : string[] ($strings : string[], $count : int);>

Creates a new array that repeats the string $strings $count times, and returns it.

Exceptions:

$strings must be defined. Otherwise an exception is thrown.

$count must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 copy_object_with_proto

C<static method copy_object_with_proto : object[] ($array : object[], $proto : object[], $cloner : L<Cloner|SPVM::Cloner> = undef, $offset : int = 0, $length : int = -1);>

The same as L</"copy_object">, but can give the prototype array $proto for the copied array.

=head2 copy_object_address_with_proto

C<static method copy_object_address_with_proto : object[] ($array : object[], $proto : object[], $offset : int = 0, $length : int = -1);>

The same as L</"copy_object_address">, but can give the prototype array $proto for the copied array.

=head2 to_object_array_byte

C<static method to_object_array_byte : L<Byte|SPVM::Byte>[] ($array : byte[]);>

Creates a new L<Byte|SPVM::Byte> array with the same length as the byte array $array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_object_array_short

C<static method to_object_array_short : L<Short|SPVM::Short>[] ($array : short[]);>

Creates a new L<Short|SPVM::Short> array with the same length as the short array $array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_object_array_int

C<static method to_object_array_int : L<Int|SPVM::Int>[] ($array : int[]);>

Creates a new L<Int|SPVM::Int> array with the same length as the int array $array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_object_array_long

C<static method to_object_array_long : L<Long|SPVM::Long>[] ($array : long[]);>

Creates a new L<Long|SPVM::Long> array with the same length as the long array $array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_object_array_float

C<static method to_object_array_float : L<Float|SPVM::Float>[] ($array : float[]);>

Creates a new L<Float|SPVM::Float> array with the same length as the float array $array, copies the elements in $array to it, and returns it.

=head2 to_object_array_double

C<static method to_object_array_double : L<Double|SPVM::Double>[] ($array : double[]);>

Creates a new L<Double|SPVM::Double> array with the same length as the double array $array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_array_byte

C<static method to_array_byte : byte[] ($object_array : L<Byte|SPVM::Byte>[]);>

Creates a new byte array with the same length as the L<Byte|SPVM::Byte> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

=head2 to_array_short

C<static method to_array_short : short[] ($object_array : L<Short|SPVM::Short>[]);>

Creates a new short array with the same length as the L<Short|SPVM::Short>> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $object_array must be defined. Otherwise, an exception is thrown.

=head2 to_array_int

C<static method to_array_int : int[] ($object_array : L<Int|SPVM::Int>[]>);>

Creates a new int array with the same length as the L<Int|SPVM::Int> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $object_array must be defined. Otherwise, an exception is thrown.

=head2 to_array_long

C<static method to_array_long : long[] ($object_array : L<Long|SPVM::Long>[]);>

Creates a new long array with the same length as the L<Long|SPVM::Long> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $object_array must be defined. Otherwise, an exception is thrown.

=head2 to_array_float

C<static method to_array_float : float[] ($object_array : L<Float|SPVM::Float>[]);>

Creates a new float array with the same length as the L<Float|SPVM::Float> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $object_array must be defined. Otherwise, an exception is thrown.

=head2 to_array_double

C<static method to_array_double : double[] ($object_array : L<Double|SPVM::Double>[]);>

Creates a new double[ array with the same length as the L<Double|SPVM::Double> array $object_array, copies the elements in $array to it, and returns it.

Exceptions:

The array $object_array must be defined. Otherwise, an exception is thrown.

=head2 new_array_proto_element

C<static method new_array_proto_element : object[] ($proto_element : object, $length : int);>

Create a new object array of the type when the prototype element $proto_element are arrayed with the length $length.

Exceptions:

The prototype element $proto_element must be defined. Otherwise an exception is thrown.

The length $length must be greater than or equal to 0. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
