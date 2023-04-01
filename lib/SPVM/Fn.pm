package SPVM::Fn;

1;

=encoding utf8

=head1 Name

SPVM::Fn - SPVM Starndard Functions

=head1 Usage

  use Fn;
  
  # Cut a newline LF
  my $line = (mutable string)copy "abc\n";
  Fn->chomp($line);
  
  # Contains
  my $found = Fn->contains("pppabcde", "bcd");
  
  # Split
  my $csv = "foo,bar,baz";
  my $items = Fn->split(",", $string);
  
  # Join
  my $items = ["foo", "bar", "baz"];
  my $csv = Fn->join(",", $items);
  
  # Constant values
  my $byte_max = Fn->BYTE_MAX();
  my $short_max = Fn->SHORT_MAX();
  my $int_max = Fn->INT_MAX();
  my $long_max = Fn->LONG_MAX();

=head1 Description

C<Fn> module provides SPVM Starndard Functions. C<Fn> contains number, string and array utilities.

=head1 Enumerations

=head2 GET_CODE_POINT_ERROR_OVER_STRING_RANGE

Returns -1. The return type is the C<int> type.

=head2 GET_CODE_POINT_ERROR_INVALID_UTF8

Returns -2. The return type is the C<int> type.

=head1 Class Methods

=head2 BYTE_MAX

  static method BYTE_MAX : int ();

The same as L</"INT8_MAX">.

=head2 BYTE_MIN

  static method BYTE_MIN : int ();

The same as L</"INT8_MIN">.

=head2 DBL_MAX

  static method DBL_MAX : double ();

Returns the value of C<DBL_MAX> macro defined in C<float.h> header of the C language.

=head2 DBL_MIN

  static method DBL_MIN : double ();

Returns the value of C<DBL_MIN> macro defined in C<float.h> header of the C language.

=head2 DOUBLE_MAX

  static method DOUBLE_MAX : double ();

The same as L</"DBL_MAX">.

=head2 DOUBLE_MIN

  static method DOUBLE_MIN : double ();

The same as L</"DBL_MIN">.

=head2 FLOAT_MAX

  static method FLOAT_MAX : float ();

The same as L</"FLT_MAX">.

=head2 FLOAT_MIN

  static method FLOAT_MIN : float();

The same as L</"FLT_MIN">.

=head2 FLT_MAX

  static method FLT_MAX : float ();

Returns the value of C<FLT_MAX> macro defined in C<float.h> header of the C language.

=head2 FLT_MIN

  static method FLT_MIN : float ();

Returns the value of C<FLT_MIN> macro defined in C<float.h> header of the C language.

=head2 INT16_MAX

  static method INT16_MAX : int ();

Returns 32767. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

  static method INT16_MIN : int ();

Returns -32768. The minimal value of the signed 16bit integer. 

=head2 INT32_MAX

  static method INT32_MAX : int ();

Returns 2147483647. The maximum value of the signed 32bit integer.

=head2 INT32_MIN

  static method INT32_MIN : int ();

Returns -2147483648. The minimal value of the signed 32bit integer.

=head2 INT64_MAX

  static method INT64_MAX : long ();

Returns 9223372036854775807. The maximum value of the signed 64bit integer. 

=head2 INT64_MIN

  static method INT64_MIN : long ();

Returns -9223372036854775808. The minimal value of the signed 64bit integer.

=head2 INT8_MAX

  static method INT8_MAX : int ();

Returns 127. The maximum value of the signed 8bit integer.

=head2 INT8_MIN

  static method INT8_MIN : int ();

Returns -128. The minimal value of the signed 8bit integer.

=head2 INT_MAX

  static method INT_MAX : int ();

The same as L</"INT32_MAX">.

=head2 INT_MIN

  static method INT_MIN : int ();

The same as L</"INT32_MIN">.

=head2 LONG_MAX

  static method LONG_MAX : long ();

The same as L</"INT64_MAX">.

=head2 LONG_MIN

  static method LONG_MIN : long ();

The same as L</"INT64_MIN">.

=head2 RAND_MAX

  static method RAND_MAX : int ();

Returns 2147483647.

=head2 SHORT_MAX

  static method SHORT_MAX : int ();

The same as L</"INT16_MAX">.

=head2 SHORT_MIN
  
  static method SHORT_MIN : int ();

The same as L</"INT16_MIN">.

=head2 UBYTE_MAX

  static method UBYTE_MAX : int ();

The same as L</"UINT8_MAX">.

=head2 UINT16_MAX

  static method UINT16_MAX : int ();

Returns -1. This represents C<0xFFFF> in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  static method UINT32_MAX : int ();

Returns -1. This represents C<0xFFFFFFFF> in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  static method UINT64_MAX : long ();

Returns -1. This represents C<0xFFFFFFFFFFFFFFFF> in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

  static method UINT8_MAX : int ();

Returns -1. This represents C<0xFF> in the unsigned 8bit integer in 2's complement.

=head2 UINT_MAX

  static method UINT_MAX : int ();

The same as L</"UINT32_MAX">.

=head2 ULONG_MAX

  static method ULONG_MAX : long

The same as L</"UINT64_MAX">.

=head2 USHORT_MAX

  static method USHORT_MAX : int ();

The same as L</"UINT16_MAX">.

=head2 abs

  static method abs : int ($value : int);

Returns the absolute value of the $value.

=head2 chomp

  static method chomp : void ($string : mutable string);

Removes C<\r\n> or C<\n> at the end of the $string.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 chompr

  static method chompr : string ($string : string);

Copies the $string and removes C<\r\n> or C<\n> at the end of the copied string and returns it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 chr

  static method chr : string ($code_point : int);

Converts the $code_point to the UTF-8 character and return it.

If the $code_point is not a Unicode scalar value, return undef.

=head2 contains

  static method contains : int ($string : string, $substring : string, $string_offset = 0 : int, $string_length = -1 : int);

The alias for the following code using L</"index>.

  my $ret = Fn->index($string, $substring, $string_offset, $string_length) >= 0;

=head2 copy_string

  static method copy_string : string ($string : string);

The alias for the following code using the L<copy operator|SPVM::Document::Language/"copy Operator">

  my $ret = copy $string;

=head2 crand

  static method crand : int ($seed : int*);

Create a random number from 0 to L</"RAND_MAX"> using the $seed and return it.

The $seed is updated.

This method is thread safe.

Examples:
  
  use Time;
  my $seed = (int)Time->time;
  my $crand0 = Fn->crand(\$seed);
  my $crand1 = Fn->crand(\$seed);

=head2 equals_string_range

  static method equals_string_range : int ($string1 : string, $string1_offset : int, $string2 : string, $string2_offset : int, $length : int);

Compares $string1 + $string1_offset with $string2 + $string2_offset by the $length. If they are euqal, returns 1, otherwise returns 0.

If the $length is 0, returns 1.

Exceptions:

The $string1 must be defined. Otherwize an exception is thrown.

The $string2 must be defined. Otherwize an exception is thrown.

The $string1_offset must be greater than or equal to 0. Otherwize an exception is thrown.

The $string2_offset must be greater than or equal to 0. Otherwize an exception is thrown.

=head2 get_code_point

  static method get_code_point : int ($string : string, $offset_ref : int*);

Parses the UTF-8 character at the value reffered by $offset_ref of the $string and return its Unicode code point.

The offset is updated to the position of the next UTF-8 character.

If the offset is greater than the length of the string, return the value of L</"GET_CODE_POINT_ERROR_OVER_STRING_RANGE">.

If the UTF-8 character is invalid, return the value of L</"GET_CODE_POINT_ERROR_INVALID_UTF8">.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $offset must be greater than or equal to 0. Otherwize an exception is thrown.

=head2 hex

  static method hex : int ($hex_string : string);

Converts the $hex_string to the C<int> value and return it.

Exceptions:

The $hex string must be defined. Otherwize an exception is thrown.

The length of the $hex string must be 1 to 8. Otherwize an exception is thrown.

The $hex string must contain only hex characters C<0-9a-zA-Z>. Otherwize an exception is thrown.

=head2 index

  static method index : int ($string : string, $substring : string, $string_offset = 0 : int, $string_length = -1 : int);

Searches for the $substring in the range of the $string from the $string_offset to the position proceeded by the $string_length.

If the $substring is found, returns the found offset, otherwise returns -1.

If the $string_length is less than 0, the $string_length is calculated from the length of the $string and the $string_offset.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $substring must be defined. Otherwize an exception is thrown.

The $string_offset must be greater than or equal to 0. Otherwize an exception is thrown.

The $string_offset + the $string_length must be less than or equal to the length of the $string. Otherwize an exception is thrown.

=head2 init_string

  static method init_string : void ($string : mutable string, $ascii_code = 0 : int, $offset = 0 int, $length = -1);

Sets the characters in the $string from the $offset to the position proceeded by the $length to the $ascii_code.

If the $length is less than 0, the $length is set to the length of the $string - the $offset.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $offset + the $length must be less than or equal to the length of the $string.

=head2 is_alnum

  static method is_alnum : int ($code_point : int);

If the Unicode $code_point is an ASCII alphanumeric C<A-Za-z0-9>, return 1. Otherwise return 0.

=head2 is_alpha

  static method is_alpha : int ($code_point : int);

If the Unicode $code_point is an ASCII alphabetic C<A-Za-z>, return 1. Otherwise return 0.

=head2 is_array

  static method is_array : int ($object : object);

If the $object is defined and the type of the $object is the L<array type|SPVM::Document::Language/"Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_array"> is used to check the type.

=head2 is_blank

  static method is_blank : int ($code_point : int);

If the Unicode $code_point is an ASCII blank C<0x20(SP, ' ')>, C<0x09(HT, '\t')>, return 1. Otherwise return 0.

=head2 is_class

  static method is_class : int ($object : object);

If the $object is defined and the type of the $object is the L<class type|SPVM::Document::Language/"Class Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_class"> is used to check the type.

=head2 is_cntrl

  static method is_cntrl : int ($code_point : int);

If the Unicode $code_point is an ASCII control character C<0x00-0x1F>, C<0x7F>, return 1. Otherwise return 0.

=head2 is_digit

  static method is_digit : int ($code_point : int);

If the Unicode $code_point is an ASCII decimal digit 0-9, return 1. Otherwise return 0.

=head2 is_graph

  static method is_graph : int ($code_point : int);

If the $character is an ASCII graphical character C<0x21-0x7E>, return 1. Otherwise return 0.

=head2 is_hex_digit

  static method is_hex_digit : int ($code_point : int);

If the $character is a hexadecimal digit C<0-9a-fA-F>, return 1. Otherwise return 0.

=head2 is_lower

  static method is_lower : int ($code_point : int);

If the Unicode $code_point is an ASCII lowercase character C<a-z>, return 1. Otherwise return 0.

=head2 is_mulnum_array

  static method is_mulnum_array : int ($object : object);

If the $object is defined and the type of the $object is the L<multi-numeric array type|SPVM::Document::Language/"Multi-Numeric Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_mulnum_array"> is used to check the type.

=head2 is_numeric_array

  static method is_numeric_array : int ($object : object);

If the $object is defined and the type of the $object is the L<numeric array type|SPVM::Document::Language/"Numeric Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_numeric_array"> is used to check the type.

=head2 is_object_array

  static method is_object_array : int ($object : object);

If the $object is defined and the type of the $object is an L<object array type|SPVM::Document::Language/"Object Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_object_array"> is used to check the type.

=head2 is_perl_space

  static method is_perl_space : int ($code_point : int);

If the Unicode $code_point is an Perl ASCII space character C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')>,  return 1. Otherwise return 0.

Note that prior to Perl v5.18, C<\s> in ASCII mode did not match the vertical tab C<0x0B(VT)>. C<is_perl_space> is the same as this behavior.

Current Perl C<\s> in ASCII mode is the same as L</"is_space">.

=head2 is_perl_word

  static method is_perl_word : int ($code_point : int);

If the Unicode $code_point is an Perl ASCII word character C<a-zA-Z0-9_>, return 1. Otherwise return 0.

=head2 is_pointer_class

  static method is_pointer_class : int ($object : object);

If the $object is defined and the $object is a L<pointer class|SPVM::Document::Language/"Pointer Class">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_pointer_class"> is used to check the type.

=head2 is_print

  static method is_print : int ($code_point : int);

If the Unicode C<$$code_point> is an ASCII printable character C<0x20-0x7E>, return 1. Otherwise return 0.

=head2 is_punct

  static method is_punct : int ($code_point : int);

If the Unicode $code_point is an ASCII a punctuation character C<0x21-0x2F>, C<0x3A-0x40>, C<0x5B-0x60>, C<0x7B-0x7E>, return 1. Otherwise return 0.

=head2 is_space

  static method is_space : int ($code_point : int);

If the Unicode $code_point is an ASCII a white-space C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0B(VT)>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')> return 1. Otherwise return 0.

=head2 is_upper

  static method is_upper : int ($code_point : int);

If the $code_point is an ASCII uppercase character C<A-Z>, return 1. Otherwise return 0.

=head2 is_xdigit

  static method is_xdigit : int ($code_point : int);

If the $code_point is an ASCII hexadecimal digit C<0-9A-Fa-f>, return 1. Otherwise return 0.

=head2 join

  static method join : string ($separator : string, $strings : string[]);

Concatenates the $strings with the $separater and return it.

Exceptions:

The $strings must be defined. Otherwize an exception is thrown.

The $separator must be defined. Otherwize an exception is thrown.

=head2 labs

  static method labs : long ($value : long);

Returns the absolute value of the $value.

=head2 lc

  static method lc : string ($string : string);

Converts the ASCII uppercase characters C<A-Z> in the $string to the corresponding ASCII lowercase characters C<a-z>. And return it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 lcfirst

  static method lcfirst : string ($string : string);

If the first character of the $string is an ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase characters C<a-z>. And return the converted string.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 look_code_point

  static method look_code_point : int ($string : string, $offset_ref : int*);

The same as L</"get_code_point">, but the offset is not updated.

=head2 memcpy

  static method memcpy : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

Copies the range of the $source to the the range of the $dest.

The range of the $dest is from the $offset to the position proceeded by the $length of the destination.

The range of the $source is from the $offset to the position proceeded by the $length of the source.

The unit of the $offset and the $length is C<byte> size.

If the range of the $source and the range of the $dest overlap, the result is B<not> guaranteed.

Exceptions:

The $dest must be defined. Otherwize an exception is thrown.

The type of the $dest must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwize an exception is thrown.

The $source must be defined. Otherwize an exception is thrown.

The type of the $source must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwize an exception is thrown.

The $dest must not be a read-only string. If so, an exception is thrown.

The $length must be greater than or equal to 0. Otherwize an exception is thrown.

The $dest_offset + the $length must be less than or equal to the length of the $dest. Otherwize an exception is thrown.

The $source_offset + the $length must be less than or equal to the length of the $source. Otherwize an exception is thrown.

=head2 memmove

  static method memmove : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

The same as L</"memcpy">, but even if the range of the $source and the range of the $dest overlap, the result is guaranteed.

=head2 ord

  static method ord : int ($string : string);

The alias for the following code using L</"get_code_point">.

  my $offset = 0;
  my $code_point = Fn->get_code_point($string, \$offset);

=head2 powi

  static method powi : int ($base : int, $exponant : int);

Calculates the exponentiation from the $base number and the $exponant number.

Exceptions:

The $exponant number must be greater than or equal to 0. Otherwize an exception is thrown.

If the $base number is 0, the $exponant number can't be 0.

=head2 powl

  static method powl : long ($base : long, $exponant : long);

Calculates the exponentiation from the $base number and the $exponant number.

Exceptions:

The $exponant number must be greater than or equal to 0. Otherwize an exception is thrown.

If the $base number is 0, the $exponant number can't be 0.

=head2 rand

  static method rand : double ($seed : int*, $max = 1 : int);

Gets a 64bit floating point random number that is greater than or equal to 0 and less than 1 using the $seed.

If the $max is specified, the $max is multiplied to the return value.

The seed is updated.

This method is thread safe.

Examples:

  use Time;
  my $seed = (int)Time->time;
  my $rand0 = Fn->rand(\$seed);
  my $rand1 = Fn->rand(\$seed);

=head2 repeat

  static method repeat : double ($string : string, $count : int);

Concatenates the $string the number of times specified in the $count and return it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $repeat count must be greater than or equal to 0.

Examples:
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

=head2 replace_chars

  static method replace_chars : void ($string : mutable string, $from_ch : int, $to_ch : int);

Replaces all characters specified by the second argument in the $string with the characters specified by the third argument.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 rindex

  static method rindex : int ($string : string, $substring : string, $offset = 0 : int, $length = -1 : int);

Searches for the substring in the range of the $string from the $offset to the position proceeded by the $length in the direction from back to front.

If the $substring is found, return the $found offset. Otherwise return -1.

If the length is less than 0, the length to the end of the string is calculated from the length of the string and the offset.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $substring must be defined. Otherwize an exception is thrown.

The $offset must be greater than or equal to 0. Otherwize an exception is thrown.

The $offset + the $length must be less than or equal to the length of the $string. Otherwize an exception is thrown.

=head2 sizeof_native_int

  static method sizeof_native_int : int ();

Returns the native C<int> size. This is the same value as C<sizeof(int)> in the C language.

=head2 sizeof_native_pointer

  static method sizeof_native_pointer : int ();

Returns the native pointer size. This is the same value as C<sizeof(void*)> in the C language.

=head2 shorten

    static method shorten : void ($string : mutable string, $length : int32_t);

Shortens the $string to the $length specified by the argument using L<SPVM::Document::NativeAPI/"shorten">.

If the length specified by the argument is greater than or equal to the length of the string, nothing is performed.

Exceptions:

The $string must be defined.

The $length must be greater than or equal to 0. Otherwize an exception is thrown.

=head2 shorten_null_char

  static method shorten_null_char : void ($string : mutable string);

Shortens the $string just before the first null character C<\0>.

If null characters is not found, do nothing.

Exceptions:

The $string must be defined.  Otherwize an exception is thrown.

B<Example:>
  
  my $message = (mutable string)copy "foo\0bar";
  
  # "foo"
  my $message_shoten = Fn->shorten_null_char($message);
  
=head2 split

  static method split : string[] ($separator : string, $string : string, $limit = -1 : int);

If the $limit is less than 0, split the $string by the specific $separator and convert them to an string array and return it.

If the $limit is greater than than 0, the limit becomes the length of the maximam separated elements.

Exceptions:

The $separator must be defined. Otherwize an exception is thrown.

The $string must be defined. Otherwize an exception is thrown.

The $limit can't be 0. Otherwize an exception is thrown.

=head2 substr

  static method substr : string ($string : string, $offset : int, $length = -1 : int);

Gets the substring from the $string. The extracting range of the string is from the $offset to the position proceeded by the $length, and returns it.

If the length is less than 0, the length to the end of the string is calculated from the length of the $string and the $offset.

=head2 to_code_points

  static method to_code_points : int[] ($string : string)

Converts the $string to the Unicode code points, and returns it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $string contains an invalid Unicode code point. Otherwize an exception is thrown.

=head2 to_double

  static method to_double : double ($string : string);

Converts the $string to the C<double> value using C<strtod> in the C language.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $string must be the string that can be parsed as a double number. Otherwize an exception is thrown.

The $string must be a double number in the $correct range. Otherwize an exception is thrown.

Examples:

  my $string = "1.25";
  my $num = Fn->to_double($string);

=head2 to_float

  static method to_float : float ($string : string);

Converts the $string to the C<double> value using C<strtof> in the C language.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $string must be the string that can be parsed as a float number. Otherwize an exception is thrown.

The $string must be a float number in the $correct range. Otherwize an exception is thrown.

Examples:

  my $string = "1.25";
  my $num = Fn->to_float($string);

=head2 to_int

  static method to_int : int ($string : string, $digit : int);

The alias for the following code using L</"to_int_with_base">.

  my $ret = Fn->to_int_with_base($string, 10);

=head2 to_int_with_base

Converts the $string to the C<int> value with $digit using C<strtol> in the C language.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $string must be the string that can be parsed as an int number. Otherwize an exception is thrown.

The $string must be an int number in the $correct range. Otherwize an exception is thrown.

Examples:

  my $string = "-2147483648";
  my $num = Fn->to_int_with_base($string, 10);

=head2 to_long

  static method to_long : long ($string : string);

The alias for the following code using L</"to_long_with_base">.

  my $ret = Fn->to_long_with_base($string, 10);

=head2 to_long_with_base

  static method to_long_with_base : long ($string : string, $digit : int);

Converts the $string to the C<long> value with $digit using C<strtoll> in the C language.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $digit must be one of 2, 8, 10, or 16. Otherwize an exception is thrown.

The $string must be the string that can be parsed as a long number. Otherwize an exception is thrown.

The $string must be a long number in the $correct range. Otherwize an exception is thrown.

Examples:

  my $string = "-9223372036854775808";
  my $num = Fn->to_long_with_base($string, 10);

=head2 to_lower

  static method to_lower : int ($code_point : int);

If the $code_point is the ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase character C<a-z>.

If the $code_point is not an ASCII uppercase character, return itself.

=head2 to_upper

  static method to_upper : int ($code_point : int);

If the $code_point is the ASCII lowercase character C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>.

If the $code_point is not an ASCII lowercase character, return itself.

=head2 to_utf8_chars

  static method to_utf8_chars : string[] ($string : string);

Converts the $string to UTF-8 characters, and returns it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $string contains an invalid Unicode code point. Otherwize an exception is thrown.

Examples:

  my $string = "あいうa";
  
  # ["あ", "い", "う", "a"]
  my $utf8_chars = Fn->to_utf8_chars($string);

=head2 tr

  static method tr : string ($string : string, $pattern : string, $replace : string)

Replaced the range of $pattern with the range of $replace in a $string and returns a replaced string.

The range must be the format C<a-z> or C<a>. If the format is C<a>, it is converted to C<a-a>.

  # The range format examples
  "a-z"
  "0-9"
  "a"
  "5"
  "０-９"
  "あ-ん"

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

The $pattern must be defined. Otherwize an exception is thrown.

The $replace must be defined. Otherwize an exception is thrown.

If the $string contains an invalid Unicode code point, an exception is thrown.

The range format of the (pattern|replace) can't be contain an invalid Unicode code point. If so, an exception is thrown. If so, an exception is thrown.

The second character ot the range format of the (pattern|replace) must be \"-\". Otherwize an exception is thrown.

The range format of the (pattern|replace) must be 1 or 3 characters. Otherwize an exception is thrown.

The exceptions of the L<"/get_code_point"> method can be thrown.

C<Examples:>

  {
    my $string = "０１２３４５６７８９";
    my $pattern = "０-９";
    my $replace = "0-9";
    
    # "0123456789"
    my $ret = Fn->tr($string, $pattern, $replace);
  }
  
  {
    my $string = "abcd";
    my $pattern = "a-c";
    my $replace = "x-z";
    
    # "xyzd"
    my $ret = Fn->tr($string, $pattern, $replace);
  }
}

=head2 trim

  static method trim : string ($string : string);

Removes the right and left spaces of the $string and return it.

The removed spaces is the same as the spaces L</"is_space"> method returns 1.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 uc

  static method uc : string ($string : string);

Converts the ASCII lowercase characters C<a-z> in the $string to the corresponding ASCII uppercase characters C<A-Z>. And return it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 ucfirst

  static method ucfirst : string ($string : string);

If the first character of the $string is an ASCII lowercase characters C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>. And return the converted string.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

=head2 utf8_length

  static method utf8_length : int ($string : string)

Gets the length as a UTF-8 string from the $string, and returns it.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

If the $string contains an invalid Unicode code point, an exception is thrown.

Examples:

  # 3
  my $utf8_length = Fn->utf8_length("あいう");

=head2 utf8_substr

  static method utf8_substr : string ($string : string, $utf8_offset : int, $utf8_length = -1 : int);

Gets the substring from the $string. The extracting range of the string is from the $utf8_offset to the position proceeded by the $utf8_length, and returns it.

If the length is less than 0, the length to the end of the string is calculated from the length of the $string and the $utf8_offset.

Exceptions:

The $string must be defined. Otherwize an exception is thrown.

If the $string contains an invalid Unicode code point, an exception is thrown.

The $utf8_offset + the $utf8_length must be less than or equal to the UTF-8 length of the $string. Otherwize an exception is thrown.

Examples:

  # "いえ"
  my $utf8_substr = Fn->utf8_substr("あいうえ", 1, 2);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
