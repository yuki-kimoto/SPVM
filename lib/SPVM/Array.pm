package SPVM::Array;

1;

=encoding utf8

=head1 Name

SPVM::Array - Array Utilities

=head1 Usage

  use Array;
  
  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = Array->copy_byte($nums);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = Array->copy_short($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = Array->copy_int($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = Array->copy_long($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = Array->copy_float($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = Array->copy_double($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = Array->copy_string($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = Array->equals_byte($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = Array->equals_short($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = Array->equals_int($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = Array->equals_long($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = Array->equals_float($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = Array->equals_double($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = Array->equals_string($strs1, $strs2);
  }
  
  # Copy object array
  my $objects = [(object)Int->new(1), Int->new(2), Int->new(3)];
  my $objects_copy = Array->copy_object($objects, method : object ($obj : object) {
    my $int_obj = (Int)$obj;
    my $new_int_obj = Int->new($int_obj->value);
    return $new_int_obj;
  });

=head1 Description

C<Array> provides array utilities.

=head1 Class Methods

=head2 copy_byte

  static method copy_byte : byte[] ($nums : byte[])

Copy a byte array.

If the array is undef, return undef.

=head2 copy_double

  static method copy_double : double[] ($nums : double[])

Copy a double array.

If the array is undef, return undef.

=head2 copy_float

  static method copy_float : float[] ($nums : float[])

Copy a float array.

If the array is undef, return undef.

=head2 copy_int

  static method copy_int : int[] ($nums : int[])

Copy a int array.

If the array is undef, return undef.
  
=head2 copy_long

  static method copy_long : long[] ($nums : long[])

Copy a long array.

If the array is undef, return undef.

=head2 copy_object

  static method copy_object : object[] ($objects : object[], $cloner : Cloner)

Copy a object array with a L<Cloner|SPVM::Cloner> callback implemetation.

If the array is undef, return undef.

=head2 copy_range_byte

  static method copy_range_byte : byte[] ($nums : byte[], $offset : int, $length : int)
  
Slice elements in the byte array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_double

  static method copy_range_double : double[] ($nums : double[], $offset : int, $length : int)

Slice elements in the double array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_float

  static method copy_range_float : float[] ($nums : float[], $offset : int, $length : int)

Slice elements in the float array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_int

  static method copy_range_int : int[] ($nums : int[], $offset : int, $length : int)

Slice elements in the int array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_long

  static method copy_range_long : long[] ($nums : long[], $offset : int, $length : int)

Slice elements in the long array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_object

  static method copy_range_object : object[] ($elems : object[], $offset : int, $length : int)

Slice elements in the object array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_short

  static method copy_range_short : short[] ($nums : short[], $offset : int, $length : int)

Slice elements in the short array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_string
  
  static method copy_range_string : string[] ($strings : string[], $offset : int, $length : int)

Slice elements in the string array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_short

  static method copy_short : short[] ($nums : short[])

Copy a short array.

If the array is undef, return undef.
  
=head2 copy_string

  static method copy_string : string[] ($strings : string[])

Copy a string array.

If the array is undef, return undef.

=head2 dump_byte

  static method dump_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_double

  static method dump_double : string ($nums : double[])
  
Convert the elements in the double array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_float

  static method dump_float : string ($nums : float[])
  
Convert the elements in the float array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_int

  static method dump_int : string ($nums : int[])
  
Convert the elements in the int array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_long

  static method dump_long : string ($nums : long[])
  
Convert the elements in the long array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_object

  static method dump_object : string ($objects : object[], $stringer : Stringer)
  
Convert the elements in the object array to string by a C<SPVM::Stringer> callback implementation and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_short

  static method dump_short : string ($nums : short[])
  
Convert the elements in the short array to string and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_string

  static method dump_string : string ($strings : string[])
  
Join the strings in the array with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_unsigned_byte

  static method dump_unsigned_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string interpreting as an unsigned 8bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_unsigned_int

  static method dump_unsigned_int : string ($nums : int[])
  
Convert the elements in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_unsigned_long

  static method dump_unsigned_long : string ($nums : long[])
  
Convert the elements in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_unsigned_short

  static method dump_unsigned_short : string ($nums : short[])
  
Convert the elements in the short array to string interpreting as an unsigned 16bit integer and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 equals_byte

  static method equals_byte : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_double

  static method equals_double : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_float

  static method equals_float : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_int

  static method equals_int : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_long

  static method equals_long : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_object

  static method static method equals_object : int ($objs1 : object[], $objs2 : object[], $equality_checker : EqualityChecker)

Check equality of two objects. You must sepecify a L<EqualityChecker|SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise an exception occurs.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return C<0>.

=head2 equals_short

  static method equals_short : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_string

  static method equals_string : int ($strs1 : double[], $strs2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 hex

  static method hex : int ($hex_string : string)

Convert hex string to int value.

the hex string must be defined, otherwise an exception occurs.

the hex string must be a valid expression which is represented by a regex "^([0-9a-fA-F]{1,8})$", otherwise an exception occurs.

=head2 index

  static method index : int ($string : string, $sub_string : string, $start_pos : int)

Search for the substring in the string from the starting position
and return the found position. If the substring is not found, return C<-1>.

=head2 index_len

  static method index_len : int ($string : string, $sub_string : string, $start_pos : int, $max_string_length : int)

Same as the L<"index"> method except that the max length of the string can be specified.

If the max string length of the argument is greater than the lenght of the string, the max string length become the length of string.

=head2 is_alnum

  static method is_alnum : int ($code_point : int)

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return C<1>. Otherwise return C<0>.

=head2 is_alpha

  static method is_alpha : int ($code_point : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return C<1>. Otherwise return C<0>.

=head2 is_blank

  static method is_blank : int ($code_point : int)

If character is blank(' ', '\t'), return C<1>. Otherwise return C<0>.

=head2 is_cntrl

  static method is_cntrl : int ($code_point : int)

If character is a control character(0x00-0x1F, 0x7F), return C<1>. Otherwise return C<0>.

=head2 is_digit

  static method is_digit : int ($code_point : int)

If character is decimal digit C<0-9>, return C<1>. Otherwise return C<0>.

=head2 is_graph

  static method is_graph : int ($code_point : int)

If character has graphical representation(C<0x21-0x7E>), return C<1>. Otherwise return C<0>.

=head2 is_hex_digit

  static method is_hex_digit : int ($code_point : int)

If the character is hexadecimal digit C<0-9a-fA-F>, return C<1>. Otherwise return C<0>.

=head2 is_lower

  static method is_lower : int ($code_point : int)

If character is lowercase letter('a'-'z'), return C<1>. Otherwise return C<0>.

=head2 is_perl_space

  static method is_perl_space : int ($code_point : int)

If character is Perl space character(' ', '\r', '\n', '\t', '\f'), return C<1>. Otherwise return C<0>.

=head2 is_perl_word

  static method is_perl_word : int ($code_point : int)

If character is Perl word character('a'-'z', 'A'-'Z', '_', '0'-'9'), return C<1>. Otherwise return C<0>.

=head2 is_print

  static method is_print : int ($code_point : int)

If character is printable(0x20-0x7E), return C<1>. Otherwise return C<0>.

=head2 is_punct

  static method is_punct : int ($code_point : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return C<1>. Otherwise return C<0>.

=head2 is_space

  static method is_space : int ($code_point : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return C<1>. Otherwise return C<0>.

=head2 is_upper

  static method is_upper : int ($code_point : int)

If character is uppercase letter('A'-'Z'), return C<1>. Otherwise return C<0>.

=head2 is_xdigit

  static method is_xdigit : int ($code_point : int)

If character is hexadecimal digit('0'-'9', 'A'-'F', 'a'-'f'), return C<1>. Otherwise return C<0>.

=head2 is_mulnum_array

  static method is_mulnum_array : int ($object : object)

If the object is a multi numeric array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_numeric_array

  static method is_numeric_array : int ($object : object)

If the object is a numeric array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 is_object_array

  static method is_object_array : int ($object : object)

If the object is a object array, returns C<1>, otherwise returns C<0>.

If the object is C<NULL>, returns C<0>.

=head2 join

  static method join : string ($sep : string, $strings : string[])
  
Join a string array with separater and return it.

If separater is undef, an exception occurs.

If string array is undef, an exception occurs.

=head2 labs

  static method labs : long ($x : long)

Return the absolute value.

=head2 lc

  static method lc : string ($string : string)

Convert uppercase string to lowercase string.

=head2 lcfirst

  static method lcfirst : string ($string : string)

Convert first chracter of string from uppercase to lowercase.

=head2 memcpy_byte

  static method memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_double
  
  static method memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_float
  
  static method memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_int
  
  static method memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_long
  
  static method memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_short

  static method memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_object

  static method memcpy_object : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int)

Copy source object array to destination object array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove

  static method memmove : void ($dest : object, $dest_byte_offset : int, $source : object, $source_byte_offset : int, $byte_length : int);

The destination must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

If the destination is a read-only string, an exception is thrown.

The source must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

Copy the source to the destination with the given each offset and the given length by byte unit.

If source data range and destination data overlap, the result is not guaranteed.

The destnation must be defined, otherwise an exception occurs.

The source must be defined, otherwise an exception occurs.

The length must be more than or equals to 0, otherwise an exception occurs.

The destnation byte offset + byte length must be within the byte range of the destnation, otherwise an exception occurs.

The source byte offset + byte length must be within the byte range of the source, otherwise an exception occurs.

=head2 memmove_byte

  static method memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_double
  
  memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_float
  
  static method memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_int
  
  memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_long
  
  memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_short

  memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_object

  static method memmove_object : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int)

Copy source object array to destination object array with the each offset and a length.

If source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 new_proto

  static method new_proto : object[] ($proto_array : object[], $length : int)

Create a new generic object array as the same type as the given array.

=head2 memset_byte

  static method memset_byte : void ($dest : byte[], $dest_offset : int, $value : byte, $length : int)

Set each element of the C<byte> array to the value with the offset and the length.

=head2 memset_double

  static method memset_double : void ($dest : double[], $dest_offset : int, $value : double, $length : int)

Set each element of the C<double> array to the value with the offset and the length.

=head2 memset_float

  static method memset_float : void ($dest : float[], $dest_offset : int, $value : float, $length : int)

Set each element of the C<float> array to the value with the offset and the length.

=head2 memset_int

  static method memset_int : void ($dest : int[], $dest_offset : int, $value : int, $length : int)

Set each element of the C<int> array to the value with the offset and the length.

=head2 memset_long

  static method memset_long : void ($dest : long[], $dest_offset : int, $value : long, $length : int)

Set each element of the C<long> array to the value with the offset and the length.

=head2 memset_short

  static method memset_short : void ($dest : short[], $dest_offset : int, $value : short, $length : int)

Set each element of the C<short> array to the value with the offset and the length.

=head2 memset_object

  static method memset_object : void ($dest : object[], $dest_offset : int : int, $value : object, $length)

Set each element of the object array to the value with the offset and the length.

