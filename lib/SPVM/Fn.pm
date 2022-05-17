package SPVM::Fn;

1;

=head1 NAME

SPVM::Fn - SPVM Starndard Functions

=head1 SYNOPSYS

=head2 SPVM

  use Fn;
  
  my $int8_max = Fn->INT8_MAX();
  my $int16_max = Fn->INT16_MAX();
  my $int32_max = Fn->INT32_MAX();
  my $int64_max = Fn->INT64_MAX();
  
  # Cut a newline LF
  {
    my $ret = Fn->chompr("abc\n");
  }
  
  # Copy a string
  {
    my $string = "abc";
    my $string_copy = Fn->copy_string ($string);
  }

  # Search substr
  {
    my $found_offset = Fn->index("pppabcde", "bcd", 2);
  }

  # split a string by the specific separator
  my $string = "foo,bar,baz";
  my $splited_strs = Fn->split(",", $string);

  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = Fn->copy_array_byte($nums);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = Fn->copy_array_short($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = Fn->copy_array_int($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = Fn->copy_array_long($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = Fn->copy_array_float($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = Fn->copy_array_double($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = Fn->copy_array_string($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = Fn->equals_array_byte($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = Fn->equals_array_short($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = Fn->equals_array_int($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = Fn->equals_array_long($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = Fn->equals_array_float($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = Fn->equals_array_double($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = Fn->equals_array_string($strs1, $strs2);
  }
  
  # Copy object array
  my $objects = [(object)Int->new(1), Int->new(2), Int->new(3)];
  my $objects_copy = Fn->copy_array_object($objects, method : object ($obj : object) {
    my $int_obj = (Int)$obj;
    my $new_int_obj = Int->new($int_obj->value);
    return $new_int_obj;
  });

  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  Fn->sort_byte($nums, 0, scalar @$nums, method : int ($a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  Fn->sort_short($nums, 0, scalar @$nums, method : int ($a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  Fn->sort_int($nums, 0, scalar @$nums, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  Fn->sort_long($nums, 0, scalar @$nums, method : int ($a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  Fn->sort_float($nums, 0, scalar @$nums, method : int ($a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  Fn->sort_double($nums, 0, scalar @$nums, method : int ($a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array itself by asc order
  my $nums = ["11", "1", "2", undef, ""];
  Fn->sort_double($nums, 0, scalar @$nums, method : int ($a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort object array itself by asc order
  my $minimals = new TestCase::Minimal[3];
  $minimals->[0] = TestCase::Minimal->new;
  $minimals->[0]{x} = 3;
  $minimals->[0]{y} = 5;
  $minimals->[1] = TestCase::Minimal->new;
  $minimals->[1]{x} = 3;
  $minimals->[1]{y} = 7;
  $minimals->[2] = TestCase::Minimal->new;
  $minimals->[2]{x} = 2;
  $minimals->[2]{y} = 9;
  Fn->sort_object($minimals, 0, scalar @$minimals, method : int ($object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };

=head2 Perl

  use SPVM 'Fn';
  
  my $int8_max = SPVM::Fn->INT8_MAX();
  my $int16_max = SPVM::Fn->INT16_MAX();
  my $int32_max = SPVM::Fn->INT32_MAX();
  my $int64_max = SPVM::Fn->INT64_MAX();

=head1 DESCRIPTION

B<Fn> module provides SPVM Starndard Functions. B<Fn> contains number, string and array utilities.

=head1 CLASS METHODS

Class method of B<Fn> module.

=head2 DBL_MAX

  static method DBL_MAX : double ()

Return the value of DBL_MAX macro defined in C<float.h> header of C language.

=head2 DBL_MIN

  static method DBL_MIN : double ()

Return the value of DBL_MIN macro defined in C<float.h> header of C language.

=head2 FLT_MAX

  static method FLT_MAX : float ()

Return the value of FLT_MAX macro defined in C<float.h> header of C language.

=head2 FLT_MIN

  static method FLT_MIN : float ()

Return the value of FLT_MIN macro defined in C<float.h> header of C language.

=head2 INT16_MAX

  static method INT16_MAX : short ()

Return 32767. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

  static method INT16_MIN : short ()

Return -32768. The minimal value of the signed 16bit integer. 

=head2 INT32_MAX

  static method INT32_MAX : int ()

Return 2147483647. The maximum value of the signed 32bit integer.

=head2 INT32_MIN

  static method INT32_MIN : int ()

Return -2147483648. The minimal value of the signed 32bit integer.

=head2 INT64_MAX

  static method INT64_MAX : long ()

Return 9223372036854775807. The maximum value of the signed 64bit integer. 

=head2 INT64_MIN

  static method INT64_MIN : long ()

Return -9223372036854775808. The minimal value of signed 64bit integer.

=head2 INT8_MAX

  INT8_MAX : byte ()

Return 127. The maximum value of the signed 8bit integer.

=head2 INT8_MIN

  static method INT8_MIN : byte ()

Return -128. The minimal value of the signed 8bit integer.

=head2 UINT16_MAX

  static method UINT16_MAX : short ()

Return -1. The same bit expression of 0xFFFF in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  static method UINT32_MAX : int ()

Return -1. The same bit expression of 0xFFFFFFFF in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  static method UINT64_MAX : long ()

Return -1. The same bit expression of 0xFFFFFFFFFFFFFFFF in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

  static method UINT8_MAX : byte ()

Return -1. The same bit expression of 0xFF in the unsigned 8bit integer in 2's complement.

=head2 abs

  static method abs : int ($x : int)

Return the absolute value.

=head2 chomp

  static method chomp : void ($string : mutable string)

Remove C<\n> of the end of the string. This method changes the given string itself.

If the string is C<undef> or the length is zero, does nothing.

=head2 chompr

  static method chompr : string ($string : string)

Copy the string and remove "\n" of the end of the string and return it.

=head2 chr

  static method chr : string ($unicode_code_point : int) {

Convert Unicode code point to a UTF-8 character. If the Unicode code point is not a Unicode scalar value, return C<undef>.

See also L<Unicode->is_unicode_scalar_value|SPVM::Unicode/"is_unicode_scalar_value">.

=head2 copy_array_byte

  static method copy_array_byte : byte[] ($nums : byte[])

Copy a byte array.

If the array is undef, return undef.

=head2 copy_array_double

  static method copy_array_double : double[] ($nums : double[])

Copy a double array.

If the array is undef, return undef.

=head2 copy_array_float

  static method copy_array_float : float[] ($nums : float[])

Copy a float array.

If the array is undef, return undef.

=head2 copy_array_int

  static method copy_array_int : int[] ($nums : int[])

Copy a int array.

If the array is undef, return undef.
  
=head2 copy_array_long

  static method copy_array_long : long[] ($nums : long[])

Copy a long array.

If the array is undef, return undef.

=head2 copy_array_object

  static method copy_array_object : object[] ($objects : object[], $cloner : Cloner)

Copy a object array with a L<Cloner|SPVM::Cloner> callback implemetation.

If the array is undef, return undef.

=head2 copy_array_range_byte

  static method copy_array_range_byte : byte[] ($nums : byte[], $offset : int, $length : int)
  
Slice elements in the byte array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_double

  static method copy_array_range_double : double[] ($nums : double[], $offset : int, $length : int)

Slice elements in the double array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_float

  static method copy_array_range_float : float[] ($nums : float[], $offset : int, $length : int)

Slice elements in the float array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_int

  static method copy_array_range_int : int[] ($nums : int[], $offset : int, $length : int)

Slice elements in the int array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_long

  static method copy_array_range_long : long[] ($nums : long[], $offset : int, $length : int)

Slice elements in the long array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_object

  static method copy_array_range_object : object[] ($elems : object[], $offset : int, $length : int)

Slice elements in the object array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_short

  static method copy_array_range_short : short[] ($nums : short[], $offset : int, $length : int)

Slice elements in the short array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_range_string
  
  static method copy_array_range_string : string[] ($strings : string[], $offset : int, $length : int)

Slice elements in the string array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_array_short

  static method copy_array_short : short[] ($nums : short[])

Copy a short array.

If the array is undef, return undef.
  
=head2 copy_array_string

  static method copy_array_string : string[] ($strings : string[])

Copy a string array.

If the array is undef, return undef.

=head2 copy_string

  static method copy_string : string ($string : string)

Copy the value of the string, and return a new string.

If the argument string is undef, return undef.

=head2 crand

  static method crand : int ($seed : int*);

Get random number(0 <= rundom_number <= Fn->RAND_MAX) with a seed.

The seed is updated.

This method is thread safe different from C<rand> function of C<C language>.

B<Examples:>
  
  use Time;
  my $seed = (int)Time->time;
  my $crand0 = Fn->crand(\$seed);
  my $crand1 = Fn->crand(\$seed);

=head2 dump_array_byte

  static method dump_array_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_double

  static method dump_array_double : string ($nums : double[])
  
Convert the elements in the double array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_float

  static method dump_array_float : string ($nums : float[])
  
Convert the elements in the float array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_int

  static method dump_array_int : string ($nums : int[])
  
Convert the elements in the int array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_long

  static method dump_array_long : string ($nums : long[])
  
Convert the elements in the long array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_object

  static method dump_array_object : string ($objects : object[], $stringer : Stringer)
  
Convert the elements in the object array to string by a C<SPVM::Stringer> callback implementation and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_array_short

  static method dump_array_short : string ($nums : short[])
  
Convert the elements in the short array to string and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_string

  static method dump_array_string : string ($strings : string[])
  
Join the strings in the array with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_array_unsigned_byte

  static method dump_array_unsigned_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string interpreting as an unsigned 8bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_int

  static method dump_array_unsigned_int : string ($nums : int[])
  
Convert the elements in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_long

  static method dump_array_unsigned_long : string ($nums : long[])
  
Convert the elements in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_unsigned_short

  static method dump_array_unsigned_short : string ($nums : short[])
  
Convert the elements in the short array to string interpreting as an unsigned 16bit integer and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 equals_array_byte

  static method equals_array_byte : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_double

  static method equals_array_double : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_float

  static method equals_array_float : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_int

  static method equals_array_int : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_long

  static method equals_array_long : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_object

  static method static method equals_array_object : int ($objs1 : object[], $objs2 : object[], $equality_checker : EqualityChecker)

Check equality of two objects. You must sepecify a L<EqualityChecker|SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise an exception occurs.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return 0.

=head2 equals_array_short

  static method equals_array_short : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_string

  static method equals_array_string : int ($strs1 : double[], $strs2 : double[])

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

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return 1. If not, return 0.

=head2 is_alpha

  static method is_alpha : int ($code_point : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return 1. If not, return 0.

=head2 is_blank

  static method is_blank : int ($code_point : int)

If character is blank(' ', '\t'), return 1. If not, return 0.

=head2 is_cntrl

  static method is_cntrl : int ($code_point : int)

If character is a control character(0x00-0x1F, 0x7F), return 1. If not, return 0.

=head2 is_digit

  static method is_digit : int ($code_point : int)

If character is decimal digit ('0'-'9'), return 1. If not, return 0.

=head2 is_graph

  static method is_graph : int ($code_point : int)

If character has graphical representation(0x21-0x7E), return 1. If not, return 0.

=head2 is_lower

  static method is_lower : int ($code_point : int)

If character is lowercase letter('a'-'z'), return 1. If not, return 0.

=head2 is_perl_space

  static method is_perl_space : int ($code_point : int)

If character is Perl space character(' ', '\r', '\n', '\t', '\f'), return 1. If not, return 0.

=head2 is_perl_word

  static method is_perl_word : int ($code_point : int)

If character is Perl word character('a'-'z', 'A'-'Z', '_', '0'-'9'), return 1. If not, return 0.

=head2 is_print

  static method is_print : int ($code_point : int)

If character is printable(0x20-0x7E), return 1. If not, return 0.

=head2 is_punct

  static method is_punct : int ($code_point : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return 1. If not, return 0.

=head2 is_space

  static method is_space : int ($code_point : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return 1. If not, return 0.

=head2 is_upper

  static method is_upper : int ($code_point : int)

If character is uppercase letter('A'-'Z'), return 1. If not, return 0.

=head2 is_xdigit

  static method is_xdigit : int ($code_point : int)

If character is hexadecimal digit('0'-'9', 'A'-'F', 'a'-'f'), return 1. If not, return 0.

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

=head2 memcpy

  static method memcpy : void ($dest : object, $dest_byte_offset : int, $source : object, $source_byte_offset : int, $byte_length : int);

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

If source data range and destination data overlap, the result is not guaranteed.

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

=head2 new_array_proto

  static method new_array_proto : object[] ($proto_array : object[], $length : int)

Create a new generic object array as the same type as the given array.

=head2 ord

  static method ord : int ($utf8_character : string)

Gets the Unicode code point from the first character of the specified <UTF-8> string.

If the specified C<UTF-8> character is C<undef>, returns a negative value.

If the length of the specified C<UTF-8> string is C<0>, returns a negative value.

If the specified C<UTF-8> character is invalid C<UTF-8> character, returns a negative value.

=head2 powi

  static method powi : int ($x : int, $y : int)

Calculate the exponentiation.

=head2 powl

  static method powl : long ($x : long, $y : long)

Calculate the exponentiation.

=head2 rand

  static method rand : double ($seed : int*)

Get random number(0 <= random_number < 1)with a seed.

The seed is updated.

This method is thread safe different from C<rand> function of C<C language>.

B<Examples:>

  use Time;
  my $seed = (int)Time->time;
  my $rand0 = Fn->rand(\$seed);
  my $rand1 = Fn->rand(\$seed);

=head2 repeat

  static method repeat : double ($string : string, $count : int)

Gets the repeat string.

If the string is not defined, an exception will be thrown.

If the repeat is not more than C<0>, an exception will be thrown.

B<Examples:>
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

=head2 rindex

  static method rindex : int ($string : string, $sub_string : string, $start_pos : int)

Search for the substring in the string from the starting position to the start of the string.
and return the found position. If the substring is not found, return C<-1>.

=head2 rindex_len

  static method rindex_len : int ($string : string, $sub_string : string, $start_pos : int, $max_string_length : int)

Same as the L<"rindex"> method except that the max length of the string can be specified.

If the max string length of the argument is greater than the lenght of the string, the max string length become the length of string.

=head2 shorten

    static method shorten : void ($string : mutable string, $length : int32_t)

Shorten the string to the given length.

If the string is null, does nothing.

If the given length is greater than the length of the string, does nothing.

If the given length is lower than C<0>, the given length become C<0>.

In the level of native APIs, the charaters of the after the given length are filled with C<\0>.

=head2 sort_byte

    static method sort_byte : void ($nums : byte[], $offset : int, $length : int, $comparator : Comparator::Byte)

Sort byte array itself with a offset, a length, and a L<Comparator::Byte|SPVM::Comparator::Byte> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_double

    static method sort_double : void ($nums : double[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort double array itself with a offset, a length, and a L<Comparator::Double|SPVM::Comparator::Double> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_float

    static method static method sort_float : void ($nums : float[], $offset : int, $length : int, $comparator : Comparator::Float)

Sort float array itself with a offset, a length, and a L<Comparator::Float|SPVM::Comparator::Float> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_int

    static method sort_int : void ($nums : int[], $offset : int, $length : int, $comparator : Comparator::Int)

Sort int array itself with a offset, a length, and a L<Comparator::Int|SPVM::Comparator::Int> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_long

    static method sort_long : void ($nums : long[], $offset : int, $length : int, $comparator : Comparator::Long)

Sort long array itself with a offset, a length, and a L<Comparator::Long|SPVM::Comparator::Long> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_object

    static method sort_object : void ($objs : object[], $offset : int, $length : int, $comparator : Comparator)

Sort object array itself with a offset, a length, and a L<Comparator|SPVM::Comparator> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_short

    static method sort_short : void ($nums : short[], $offset : int, $length : int, $comparator : Comparator::Short)

Sort short array itself with a offset, a length, and a L<Comparator::Short|SPVM::Comparator::Short> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_string

    static method sort_string : void ($nums : string[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort string array itself with a offset, a length, and a L<Comparator::String|SPVM::Comparator::String> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 split

  static method split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

=head2 sprintf

  static method sprintf : string ($format : string, $args : object[]...)

Create a formatted string with the format and the embdded values.

=begin html

<table>
  <tr><th>Specifiers</th><th>Descriptions</th><th>Acceptable Types</th></tr>
  <tr><td>%c</td><td>Signed 8bit integer to an ASCII character</td><td>Byte</td></tr>
  <tr><td>%d</td><td>Signed 32bit integer</td><td>L<Int|SPVM::Int></td></tr>
  <tr><td>%u</td><td>Unsigned 32bit integer</td><td>L<Int|SPVM::Int></td></tr>
  <tr><td>%x</td><td></td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9a-z</code><td>L<Int|SPVM::Int></td></tr>
  <tr><td>%X</td><td></td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9A-Z</code><td>L<Int|SPVM::Int></td></tr>
  <tr><td>%ld</td><td>Signed 64bit integer</td><td>L<Long|SPVM::Long></td></tr>
  <tr><td>%lu</td><td>Unsigned 64bit integer</td><td>L<Long|SPVM::Long></td></tr>
  <tr><td>%lx</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9a-z</code></td><td>L<Long|SPVM::Long></td></tr>
  <tr><td>%lX</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9A-Z</code></td><td>L<Long|SPVM::Long></td></tr>
  <tr><td>%f</td><td>64bit floating point</td><td>L<Double|SPVM::Double>, L<Float|SPVM::Float></td></tr>
  <tr><td>%s</td><td>String</td><td>string</td></tr>
  <tr><td>%U</td><td>Unicode Code Point to a UTF-8 character</td><td></td></tr>
</table>

=end html

=head3 Format Options

=head4 Zero Padding
  
  # Format
  "%05d"
  
  # Value
  123
  
  # Output
  "00123"

=head4 Plus

  # Format
  %+d
  
  # Value
  123
  
  # Output
  "+123"

=head4 Left Justified

  # Format
  "%-5d"
  
  # Value
  123
  
  # Output
  "123  "

=head4 Number of Decimal Places Displayed

  # Format
  "%.2f"
  
  # Value
  3.1415
  
  # Output
  "3.14"

=head2 substr

  static method substr : string ($string : string, $offset : int, $length : int)

Get the substring of the string with the start offset and the length.

=head2 to_double

  static method to_double : double ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, an exception occuer.

  my $string = "1.25";
  my $num = to_double($string);

=head2 to_float

  static method to_float : float ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, an exception occuer.

  my $string = "1.25";
  my $num = to_float($string);

=head2 to_int

  static method to_int : int ($string : string, $digit : int);

Convert the string to a int value. This method is same as to_int_with_base($string, 10).

  my $string = "-2147483648";
  my $num = to_int($string);

=head2 to_int_with_base

  static method to_int_with_base : int ($string : string, $digit : int);

Convert the string to a int value with a digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][one more than 0-9]. Internal of [] is optional.

If convertion fails, an exception occuer.

  my $string = "-2147483648";
  my $num = to_int_with_base($string, 10);

=head2 to_long

  static method to_long : long ($string : string);

Convert the string to long value. This method is same as to_long($string, 10).

  my $string = "-9223372036854775808";
  my $num = to_long($string);

=head2 to_long_with_base

  static method to_long_with_base : long ($string : string, $digit : int);

Convert the string to long value with digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][zero more than 0-9]. Internal of [] is optional.

If the convertion fails, an exception occuer.

  my $string = "-9223372036854775808";
  my $num = to_long_with_base($string, 10);

=head2 to_lower

  static method to_lower : int ($code_point : int)

Convert uppercase letter('A'-'Z') to lowercase. If the character is not uppercase letter, return the character.

=head2 to_upper

  static method to_upper : int ($code_point : int)

Convert lowercase letter('a'-'z') to lowercase. If the character is not uppercase letter, return the character.

=head2 trim_ascii_space

  static method trim_ascii_space : string ($string : string)

Remove right and left spaces of the string. These spaces is ascii standard spaces which can be checked by C<is_space> method.

If the argument string is undef, return undef.

=head2 uc

  static method uc : string ($string : string)

Convert a lowercase string to a uppercase string.

If the string is undef, an exception occurs.

=head2 ucfirst

  static method ucfirst : string ($string : string)

Convert the first character of a string to a uppercase character.

If the string is undef, an exception occurs.


