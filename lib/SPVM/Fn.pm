package SPVM::Fn;

1;

=head1 NAME

SPVM::Fn - Fn in SPVM | Starndard functions

=head1 SYNOPSYS
  
  use Fn;
  
  my $int8_max = Fn->INT8_MAX();
  my $int16_max = Fn->INT16_MAX();
  my $int32_max = Fn->INT32_MAX();
  my $int64_max = Fn->INT64_MAX();
  
  my $rand = Fn->rand();

  # Cut a newline LF
  {
    my $ret = Fn->chompr("abc\n");
  }
  
  # Copy a string
  {
    my $string = "abc";
    my $string_copy = Fn->copy_string ($string);
  }

  # Search methodstr
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
  my $objects_copy = Fn->copy_array_object($objects, sub : object ($self : self, $obj : object) {
    my $int_obj = (Int)$obj;
    my $new_int_obj = Int->new($int_obj->value);
    return $new_int_obj;
  });

  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  Fn->sort_byte($nums, 0, scalar @$nums, sub : int ($self : self, $a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  Fn->sort_short($nums, 0, scalar @$nums, sub : int ($self : self, $a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  Fn->sort_int($nums, 0, scalar @$nums, sub : int ($self : self, $a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  Fn->sort_long($nums, 0, scalar @$nums, sub : int ($self : self, $a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  Fn->sort_float($nums, 0, scalar @$nums, sub : int ($self : self, $a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  Fn->sort_double($nums, 0, scalar @$nums, sub : int ($self : self, $a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array itself by asc order
  my $nums = ["11", "1", "2", undef, ""];
  Fn->sort_double($nums, 0, scalar @$nums, sub : int ($self : self, $a : double, $b : double) {
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
  Fn->sort_object$minimals, 0, scalar @$minimals, sub : int ($self : self, $object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };


=head2 INT8_MIN

  sub INT8_MIN : byte ()

Return -128. The minimal value of the signed 8bit integer.

=head2 INT8_MAX

  INT8_MAX : byte ()

Return 127. The maximum value of the signed 8bit integer.

=head2 INT16_MIN

  sub INT16_MIN : short ()

Return -32768. The minimal value of the signed 16bit integer. 

=head2 INT16_MAX

  sub INT16_MAX : short ()

Return 32767. The maximum value of the signed 16bit integer .

=head2 INT32_MIN

  sub INT32_MIN : int ()

Return -2147483648. The minimal value of the signed 32bit integer.

=head2 INT32_MAX

  sub INT32_MAX : int ()

Return 2147483647. The maximum value of the signed 32bit integer.

=head2 INT64_MIN

  sub INT64_MIN : long ()

Return -9223372036854775808. The minimal value of signed 64bit integer.

=head2 INT64_MAX

  sub INT64_MAX : long ()

Return 9223372036854775807. The maximum value of the signed 64bit integer. 

=head2 UINT8_MAX

  sub UINT8_MAX : byte ()

Return -1. The same bit expression of 0xFF in the unsigned 8bit integer in 2's complement.

=head2 UINT16_MAX

  sub UINT16_MAX : short ()

Return -1. The same bit expression of 0xFFFF in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  sub UINT32_MAX : int ()

Return -1. The same bit expression of 0xFFFFFFFF in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  sub UINT64_MAX : long ()

Return -1. The same bit expression of 0xFFFFFFFFFFFFFFFF in the unsigned 64bit integer in 2's complement.

=head2 FLT_MIN

  sub FLT_MIN : float ()

Return the value of FLT_MIN macro defined in float.h C header.

=head2 FLT_MAX

  sub FLT_MAX : float ()

Return the value of FLT_MAX macro defined in float.h C header.

=head2 DBL_MIN

  sub DBL_MIN : double ()

Return the value of DBL_MIN macro defined in float.h C header.

=head2 DBL_MAX

  sub DBL_MAX : double ()

Return the value of DBL_MAX macro defined in float.h C header.

=head2 crand

  sub crand : int ();

Get random number(0 <= rundom_number <= Fn->RAND_MAX). This is same as rand function of C language.

The first seed is initialized by epoch time automatically. If you set a seed manually, you can use <srand> static method.

This method is not thread safe because internaly this method use rand function of C language.

=head2 rand

  sub rand : double ();

Get random number(0 <= random_number < 1). This is same as rand function of Perl language.

The first seed is initialized by epoch time automatically. If you set a seed manually, you can use <srand> static method.

This method is not thread safe because internaly this method use rand function of C language.

=head2 srand

  sub srand : void ($seed : long);

Sets random number seed for the C<crand> or C<rand> static method.

=head2 chompr

  sub chompr : string ($string : string)

Copy the string and remove "\n" of the end of line and return it.

=head2 copy_string

  sub copy_string : string ($string : string)

Copy the value of the string, and return a new string.

If the argument string is undef, return undef.

=head2 hex

  sub hex : int ($hex_string : string)

Convert hex string to int value.

the hex string must be defined, otherwise a exception occurs.

the hex string must be a valid expression which is represented by a regex "^([0-9a-fA-F]{1,8})$", otherwise a exception occurs.

=head2 index

  sub index : int ($string : string, $method_string : string, $position : int)

index function searches for one string within another.
It returns the position of the first occurrence of $method_string in $string at or after $position. If $position is omitted, starts
searching from the beginning of the string. $position before the
beginning of the string or after its end is treated as if it were
the beginning or the end, respectively. $position and the return
value are based at zero. If the methodstring is not found, "index"
returns -1.
            
=head2 is_alnum

  sub is_alnum : int ($code_point : int)

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return 1. If not, return 0.

=head2 is_alpha

  sub is_alpha : int ($code_point : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return 1. If not, return 0.

=head2 is_blank

  sub is_blank : int ($code_point : int)

If character is blank(' ', '\t'), return 1. If not, return 0.

=head2 is_cntrl

  sub is_cntrl : int ($code_point : int)

If character is a control character(0x00-0x1F, 0x7F), return 1. If not, return 0.

=head2 is_digit

  sub is_digit : int ($code_point : int)

If character is decimal digit ('0'～'9'), return 1. If not, return 0.

=head2 is_graph

  sub is_graph : int ($code_point : int)

If character has graphical representation(0x21-0x7E), return 1. If not, return 0.

=head2 is_lower

  sub is_lower : int ($code_point : int)

If character is lowercase letter('a'-'z'), return 1. If not, return 0.

=head2 is_print

  sub is_print : int ($code_point : int)

If character is printable(0x20-0x7E), return 1. If not, return 0.

=head2 is_punct

  sub is_punct : int ($code_point : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return 1. If not, return 0.

=head2 is_space

  sub is_space : int ($code_point : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return 1. If not, return 0.

=head2 is_upper

  sub is_upper : int ($code_point : int)

If character is uppercase letter('A'-'Z'), return 1. If not, return 0.

=head2 is_xdigit

  sub is_xdigit : int ($code_point : int)

If character is hexadecimal digit('0'-'9', 'A'-'F', 'a'-'f'), return 1. If not, return 0.

=head2 is_perl_space

  sub is_perl_space : int ($code_point : int)

If character is Perl space character(' ', '\r', '\n', '\t', '\f'), return 1. If not, return 0.

=head2 is_perl_word

  sub is_perl_word : int ($code_point : int)

If character is Perl word character('a'-'z', 'A'-'Z', '_', '0'-'9'), return 1. If not, return 0.

=head2 join

  sub join : string ($sep : string, $strings : string[])
  
Join a string array with separater and return it.

If separater is undef, a exception occurs.

If string array is undef, a exception occurs.

=head2 lc

  sub lc : string ($string : string)

Convert uppercase string to lowercase string.

=head2 lcfirst

  sub lcfirst : string ($string : string)

Convert first chracter of string from uppercase to lowercase.

=head2 rindex

  sub rindex : int ($string : string, $method_string : string, $offset : int)

Same as "index" function except that the search is the last of the string.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

=head2 uc

  sub uc : string ($string : string)

Convert a lowercase string to a uppercase string.

If the string is undef, a exception occur.

=head2 ucfirst

  sub ucfirst : string ($string : string)

Convert the first character of a string to a uppercase character.

If the string is undef, a exception occur.

=head2 to_lower

  sub to_lower : int ($code_point : int)

Convert uppercase letter('A'-'Z') to lowercase. If the character is not uppercase letter, return the character.

=head2 to_upper

  sub to_upper : int ($code_point : int)

Convert lowercase letter('a'-'z') to lowercase. If the character is not uppercase letter, return the character.

=head2 to_int

  sub to_int : int ($string : string, $digit : int);

Convert the string to a int value. This method is same as to_int_with_base($string, 10).

  my $string = "-2147483648";
  my $num = to_int($string);

=head2 to_int_with_base

  sub to_int_with_base : int ($string : string, $digit : int);

Convert the string to a int value with a digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][one more than 0-9]. Internal of [] is optional.

If convertion fails, a exception occuer.

  my $string = "-2147483648";
  my $num = to_int_with_base($string, 10);

=head2 to_long

  sub to_long : long ($string : string);

Convert the string to long value. This method is same as to_long($string, 10).

  my $string = "-9223372036854775808";
  my $num = to_long($string);

=head2 to_long_with_base

  sub to_long_with_base : long ($string : string, $digit : int);

Convert the string to long value with digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "-9223372036854775808";
  my $num = to_long_with_base($string, 10);

=head2 to_float

  sub to_float : float ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = to_float($string);

=head2 to_double

  sub to_double : double ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = to_double($string);

=head2 trim_ascii_space

  sub trim_ascii_space : string ($string : string)

Remove right and left spaces of the string. These spaces is ascii standard spaces which can be checked by C<is_space> method.

If the argument string is undef, return undef.

=head2 copy_array_byte

  sub copy_array_byte : byte[] ($nums : byte[])

Copy a byte array.

If the array is undef, return undef.

=head2 copy_array_short

  sub copy_array_short : short[] ($nums : short[])

Copy a short array.

If the array is undef, return undef.
  
=head2 copy_array_int

  sub copy_array_int : int[] ($nums : int[])

Copy a int array.

If the array is undef, return undef.
  
=head2 copy_array_long

  sub copy_array_long : long[] ($nums : long[])

Copy a long array.

If the array is undef, return undef.

=head2 copy_array_float

  sub copy_array_float : float[] ($nums : float[])

Copy a float array.

If the array is undef, return undef.

=head2 copy_array_double

  sub copy_array_double : double[] ($nums : double[])

Copy a double array.

If the array is undef, return undef.

=head2 copy_array_string

  sub copy_array_string : string[] ($strings : string[])

Copy a string array.

If the array is undef, return undef.

=head2 copy_array_object

  sub copy_array_object : object[] ($objects : object[], $cloner : Cloner)

Copy a object array with a L<Cloner|SPVM::Cloner> callback implemetation.

If the array is undef, return undef.

=head2 equals_array_byte

  sub equals_array_byte : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_short

  sub equals_array_short : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_int

  sub equals_array_int : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_long

  sub equals_array_long : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_float

  sub equals_array_float : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_double

  sub equals_array_double : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_string

  sub equals_array_string : int ($strs1 : double[], $strs2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_object

  sub sub equals_array_object : int ($objs1 : oarray, $objs2 : oarray, $equality_checker : EqualityChecker)

Check equality of two objects. You must sepecify a L<EqualityChecker|SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise a exception occur.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return 0.

=head2 dump_array_byte

  sub dump_array_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_short

  sub dump_array_short : string ($nums : short[])
  
Convert the elements in the short array to string and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_int

  sub dump_array_int : string ($nums : int[])
  
Convert the elements in the int array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_long

  sub dump_array_long : string ($nums : long[])
  
Convert the elements in the long array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_byte

  sub dump_array_unsigned_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string interpreting as an unsigned 8bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_short

  sub dump_array_unsigned_short : string ($nums : short[])
  
Convert the elements in the short array to string interpreting as an unsigned 16bit integer and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_unsigned_int

  sub dump_array_unsigned_int : string ($nums : int[])
  
Convert the elements in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_long

  sub dump_array_unsigned_long : string ($nums : long[])
  
Convert the elements in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_float

  sub dump_array_float : string ($nums : float[])
  
Convert the elements in the float array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_double

  sub dump_array_double : string ($nums : double[])
  
Convert the elements in the double array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_string

  sub dump_array_string : string ($strings : string[])
  
Join the strings in the array with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_array_object

  sub dump_array_object : string ($objects : oarray, $stringer : Stringer)
  
Convert the elements in the object array to string by a C<SPVM::Stringer> callback implementation and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 memcpy_byte

  sub memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_short

  sub memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_int
  
  sub memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_long
  
  sub memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_float
  
  sub memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_double
  
  sub memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_byte

  sub memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_short

  memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_int
  
  memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_long
  
  memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_float
  
  sub memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_double
  
  memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 new_array_proto

  sub new_array_proto : oarray ($proto_array : oarray, $length : int)

Create a new generic object array as the same type as the given array.

=head2 copy_array_range_byte

  sub copy_array_range_byte : byte[] ($nums : byte[], $offset : int, $length : int)
  
Slice elements in the byte array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_short

  sub copy_array_range_short : short[] ($nums : short[], $offset : int, $length : int)

Slice elements in the short array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_int

  sub copy_array_range_int : int[] ($nums : int[], $offset : int, $length : int)

Slice elements in the int array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_long

  sub copy_array_range_long : long[] ($nums : long[], $offset : int, $length : int)

Slice elements in the long array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_float

  sub copy_array_range_float : float[] ($nums : float[], $offset : int, $length : int)

Slice elements in the float array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_double

  sub copy_array_range_double : double[] ($nums : double[], $offset : int, $length : int)

Slice elements in the double array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_string
  
  sub copy_array_range_string : string[] ($strings : string[], $offset : int, $length : int)

Slice elements in the string array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_object

  sub copy_array_range_object : oarray ($elems : oarray, $offset : int, $length : int)

Slice elements in the object array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 sort_byte

    sub sort_byte : void ($nums : byte[], $offset : int, $length : int, $comparator : Comparator::Byte)

Sort byte array itself with a offset, a length, and a L<Comparator::Byte|SPVM::Comparator::Byte> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_short

    sub sort_short : void ($nums : short[], $offset : int, $length : int, $comparator : Comparator::Short)

Sort short array itself with a offset, a length, and a L<Comparator::Short|SPVM::Comparator::Short> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_int

    sub sort_int : void ($nums : int[], $offset : int, $length : int, $comparator : Comparator::Int)

Sort int array itself with a offset, a length, and a L<Comparator::Int|SPVM::Comparator::Int> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_long

    sub sort_long : void ($nums : long[], $offset : int, $length : int, $comparator : Comparator::Long)

Sort long array itself with a offset, a length, and a L<Comparator::Long|SPVM::Comparator::Long> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_float

    sub sub sort_float : void ($nums : float[], $offset : int, $length : int, $comparator : Comparator::Float)

Sort float array itself with a offset, a length, and a L<Comparator::Float|SPVM::Comparator::Float> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_double

    sub sort_double : void ($nums : double[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort double array itself with a offset, a length, and a L<Comparator::Double|SPVM::Comparator::Double> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_string

    sub sort_string : void ($nums : string[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort string array itself with a offset, a length, and a L<Comparator::String|SPVM::Comparator::String> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_object

    sub sort_object : void ($objs : oarray, $offset : int, $length : int, $comparator : Comparator::Object)

Sort object array itself with a offset, a length, and a L<Comparator::Object|SPVM::Comparator::Object> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.
