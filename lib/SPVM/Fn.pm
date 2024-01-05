package SPVM::Fn;

1;

=encoding utf8

=head1 Name

SPVM::Fn - SPVM Starndard Functions

=head1 Description

The Fn class of L<SPVM> has methods for numbers, strings, general utilities.

=head1 Usage

  use Fn;
  
  # Cut a newline LF
  my $line = (mutable string)copy "abc\n";
  Fn->chomp($line);
  
  # Contains
  my $found = Fn->contains("pppabcde", "bcd");
  
  # Split
  my $csv = "foo,bar,baz";
  my $args_width = Fn->split(",", $string);
  
  # Join
  my $args_width = ["foo", "bar", "baz"];
  my $csv = Fn->join(",", $args_width);
  
  # Constant values
  my $byte_max = Fn->BYTE_MAX();
  my $short_max = Fn->SHORT_MAX();
  my $int_max = Fn->INT_MAX();
  my $long_max = Fn->LONG_MAX();

=head1 Class Methods

=head2 BYTE_MAX

C<static method BYTE_MAX : int ();>

The same as L</"INT8_MAX">.

=head2 BYTE_MIN

C<static method BYTE_MIN : int ();>

The same as L</"INT8_MIN">.

=head2 DBL_MAX

C<static method DBL_MAX : double ();>

Returns the value of C<DBL_MAX> macro defined in C<float.h> header of the C language.

=head2 DBL_MIN

C<static method DBL_MIN : double ();>

Returns the value of C<DBL_MIN> macro defined in C<float.h> header of the C language.

=head2 DOUBLE_MAX

C<static method DOUBLE_MAX : double ();>

The same as L</"DBL_MAX">.

=head2 DOUBLE_MIN

C<static method DOUBLE_MIN : double ();>

The same as L</"DBL_MIN">.

=head2 FLOAT_MAX

C<static method FLOAT_MAX : float ();>

The same as L</"FLT_MAX">.

=head2 FLOAT_MIN

C<static method FLOAT_MIN : float();>

The same as L</"FLT_MIN">.

=head2 FLT_MAX

C<static method FLT_MAX : float ();>

Returns the value of C<FLT_MAX> macro defined in C<float.h> header of the C language.

=head2 FLT_MIN

C<static method FLT_MIN : float ();>

Returns the value of C<FLT_MIN> macro defined in C<float.h> header of the C language.

=head2 INT16_MAX

C<static method INT16_MAX : int ();>

Returns 32767. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

C<static method INT16_MIN : int ();>

Returns -32768. The minimal value of the signed 16bit integer. 

=head2 INT32_MAX

C<static method INT32_MAX : int ();>

Returns 2147483647. The maximum value of the signed 32bit integer.

=head2 INT32_MIN

C<static method INT32_MIN : int ();>

Returns -2147483648. The minimal value of the signed 32bit integer.

=head2 INT64_MAX

C<static method INT64_MAX : long ();>

Returns 9223372036854775807. The maximum value of the signed 64bit integer. 

=head2 INT64_MIN

C<static method INT64_MIN : long ();>

Returns -9223372036854775808. The minimal value of the signed 64bit integer.

=head2 INT8_MAX

C<static method INT8_MAX : int ();>

Returns 127. The maximum value of the signed 8bit integer.

=head2 INT8_MIN

C<static method INT8_MIN : int ();>

Returns -128. The minimal value of the signed 8bit integer.

=head2 INT_MAX

C<static method INT_MAX : int ();>

The same as L</"INT32_MAX">.

=head2 INT_MIN

C<static method INT_MIN : int ();>

The same as L</"INT32_MIN">.

=head2 LONG_MAX

C<static method LONG_MAX : long ();>

The same as L</"INT64_MAX">.

=head2 LONG_MIN

C<static method LONG_MIN : long ();>

The same as L</"INT64_MIN">.

=head2 RAND_MAX

C<static method RAND_MAX : int ();>

Returns 2147483647.

=head2 SHORT_MAX

C<static method SHORT_MAX : int ();>

The same as L</"INT16_MAX">.

=head2 SHORT_MIN
  
C<static method SHORT_MIN : int ();>

The same as L</"INT16_MIN">.

=head2 UBYTE_MAX

C<static method UBYTE_MAX : int ();>

The same as L</"UINT8_MAX">.

=head2 UINT16_MAX

C<static method UINT16_MAX : int ();>

Returns -1. This represents C<0xFFFF> in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

C<static method UINT32_MAX : int ();>

Returns -1. This represents C<0xFFFFFFFF> in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

C<static method UINT64_MAX : long ();>

Returns -1. This represents C<0xFFFFFFFFFFFFFFFF> in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

C<static method UINT8_MAX : int ();>

Returns -1. This represents C<0xFF> in the unsigned 8bit integer in 2's complement.

=head2 UINT_MAX

C<static method UINT_MAX : int ();>

The same as L</"UINT32_MAX">.

=head2 ULONG_MAX

C<static method ULONG_MAX : long>

The same as L</"UINT64_MAX">.

=head2 USHORT_MAX

C<static method USHORT_MAX : int ();>

The same as L</"UINT16_MAX">.

=head2 abs

C<static method abs : int ($value : int);>

Returns the absolute value of $value.

=head2 chomp

C<static method chomp : void ($string : mutable string);>

Removes C<\r\n> or C<\n> at the end of $string.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 chompr

C<static method chompr : string ($string : string);>

Copies $string and removes C<\r\n> or C<\n> at the end of the copied string and returns it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 chr

C<static method chr : string ($code_point : int);>

Converts $code_point to the UTF-8 character and return it.

If $code_point is not a Unicode scalar value, return undef.

=head2 contains

C<static method contains : int ($string : string, $substring : string, $string_offset : int = 0, $string_length : int = -1);>

The alias for the following code using L</"index>.

  my $ret = Fn->index($string, $substring, $string_offset, $string_length) >= 0;

=head2 copy_string

C<static method copy_string : string ($string : string);>

The alias for the following code using the L<copy operator|SPVM::Document::Language/"copy Operator">

  my $ret = copy $string;

=head2 crand

C<static method crand : int ($seed : int*);>

Create a random number from 0 to L</"RAND_MAX"> using $seed and return it.

$seed is updated.

This method is thread safe.

Examples:
  
  use Sys::Time;
  my $seed = (int)Sys::Time->time;
  my $crand0 = Fn->crand(\$seed);
  my $crand1 = Fn->crand(\$seed);

=head2 equals_string_range

C<static method equals_string_range : int ($string1 : string, $string1_offset : int, $string2 : string, $string2_offset : int, $length : int);>

Compares $string1 + $string1_offset with $string2 + $string2_offset by $length. If they are euqal, returns 1, otherwise returns 0.

If $length is 0, returns 1.

Exceptions:

$string1 must be defined. Otherwise an exception is thrown.

$string2 must be defined. Otherwise an exception is thrown.

$string1_offset must be greater than or equal to 0. Otherwise an exception is thrown.

$string2_offset must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 get_code_point

C<static method get_code_point : int ($string : string, $offset_ref : int*);>

Parses the UTF-8 character at the value reffered by $offset_ref of $string and return its Unicode code point.

The offset is updated to the position of the next UTF-8 character.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

The value of $offset must be less than the length of $string. Otherwise an exception is thrown.

If an invalid UTF-8 is gotten, an exception is thrown set C<eval_error_id> to the basic type ID of the L<Error::Unicode::InvalidUTF8|SPVM::Error::Unicode::InvalidUTF8> class.

=head2 hex

C<static method hex : int ($hex_string : string);>

Converts $hex_string to the C<int> value and return it.

Exceptions:

$hex string must be defined. Otherwise an exception is thrown.

The length of $hex string must be 1 to 8. Otherwise an exception is thrown.

$hex string must contain only hex characters C<0-9a-zA-Z>. Otherwise an exception is thrown.

=head2 index

C<static method index : int ($string : string, $substring : string, $begin : int = 0, $end : int = -1);>

Searches for $substring in the range of $string from $begin to $end.

The search is performed from the beginning of the range of $string.

If $substring is found, returns the found offset, otherwise returns -1.

If $end is less than 0, $end is set to the length of $string minus 1.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$substring must be defined. Otherwise an exception is thrown.

$begin must be greater than or equal to 0. Otherwise an exception is thrown.

$end must be less than the length of $string.

=head2 init_string

C<static method init_string : void ($string : mutable string, $ascii_code : int = 0, $offset = 0 int, $length = -1);>

Sets the characters in $string from $offset to the position proceeded by $length to $ascii_code.

If $length is less than 0, $length is set to the length of $string - $offset.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $string.

=head2 is_alnum

C<static method is_alnum : int ($code_point : int);>

If the Unicode $code_point is an ASCII alphanumeric C<A-Za-z0-9>, return 1. Otherwise return 0.

=head2 is_alpha

C<static method is_alpha : int ($code_point : int);>

If the Unicode $code_point is an ASCII alphabetic C<A-Za-z>, return 1. Otherwise return 0.

=head2 is_array

C<static method is_array : int ($object : object);>

If $object is defined and the type of $object is the L<array type|SPVM::Document::Language/"Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_array"> is used to check the type.

=head2 is_blank

C<static method is_blank : int ($code_point : int);>

If the Unicode $code_point is an ASCII blank C<0x20(SP, ' ')>, C<0x09(HT, '\t')>, return 1. Otherwise return 0.

=head2 is_class

C<static method is_class : int ($object : object);>

If $object is defined and the type of $object is the L<class type|SPVM::Document::Language/"Class Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_class"> is used to check the type.

=head2 is_cntrl

C<static method is_cntrl : int ($code_point : int);>

If the Unicode $code_point is an ASCII control character C<0x00-0x1F>, C<0x7F>, return 1. Otherwise return 0.

=head2 is_digit

C<static method is_digit : int ($code_point : int);>

If the Unicode $code_point is an ASCII decimal digit 0-9, return 1. Otherwise return 0.

=head2 is_graph

C<static method is_graph : int ($code_point : int);>

If $character is an ASCII graphical character C<0x21-0x7E>, return 1. Otherwise return 0.

=head2 is_hex_digit

C<static method is_hex_digit : int ($code_point : int);>

If $character is a hexadecimal digit C<0-9a-fA-F>, return 1. Otherwise return 0.

=head2 is_lower

C<static method is_lower : int ($code_point : int);>

If the Unicode $code_point is an ASCII lowercase character C<a-z>, return 1. Otherwise return 0.

=head2 is_mulnum_array

C<static method is_mulnum_array : int ($object : object);>

If $object is defined and the type of $object is the L<multi-numeric array type|SPVM::Document::Language/"Multi-Numeric Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_mulnum_array"> is used to check the type.

=head2 is_numeric_array

C<static method is_numeric_array : int ($object : object);>

If $object is defined and the type of $object is the L<numeric array type|SPVM::Document::Language/"Numeric Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_numeric_array"> is used to check the type.

=head2 is_object_array

C<static method is_object_array : int ($object : object);>

If $object is defined and the type of $object is an L<object array type|SPVM::Document::Language/"Object Array Type">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_object_array"> is used to check the type.

=head2 is_perl_space

C<static method is_perl_space : int ($code_point : int);>

If the Unicode $code_point is an Perl ASCII space character C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')>,  return 1. Otherwise return 0.

Note that prior to Perl v5.18, C<\s> in ASCII mode did not match the vertical tab C<0x0B(VT)>. C<is_perl_space> is the same as this behavior.

Current Perl C<\s> in ASCII mode is the same as L</"is_space">.

=head2 is_perl_word

C<static method is_perl_word : int ($code_point : int);>

If the Unicode $code_point is an Perl ASCII word character C<a-zA-Z0-9_>, return 1. Otherwise return 0.

=head2 is_pointer_class

C<static method is_pointer_class : int ($object : object);>

If $object is defined and $object is a L<pointer class|SPVM::Document::Language/"Pointer Class">, return 1. Otherwise return 0.

L<SPVM::Document::NativeAPI/"is_pointer_class"> is used to check the type.

=head2 is_print

C<static method is_print : int ($code_point : int);>

If the Unicode C<$$code_point> is an ASCII printable character C<0x20-0x7E>, return 1. Otherwise return 0.

=head2 is_punct

C<static method is_punct : int ($code_point : int);>

If the Unicode $code_point is an ASCII a punctuation character C<0x21-0x2F>, C<0x3A-0x40>, C<0x5B-0x60>, C<0x7B-0x7E>, return 1. Otherwise return 0.

=head2 is_space

C<static method is_space : int ($code_point : int);>

If the Unicode $code_point is an ASCII a white-space C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0B(VT)>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')> return 1. Otherwise return 0.

=head2 is_upper

C<static method is_upper : int ($code_point : int);>

If $code_point is an ASCII uppercase character C<A-Z>, return 1. Otherwise return 0.

=head2 is_xdigit

C<static method is_xdigit : int ($code_point : int);>

If $code_point is an ASCII hexadecimal digit C<0-9A-Fa-f>, return 1. Otherwise return 0.

=head2 join

C<static method join : string ($separator : string, $strings : string[]);>

Concatenates $strings with $separater and return it.

Exceptions:

$strings must be defined. Otherwise an exception is thrown.

$separator must be defined. Otherwise an exception is thrown.

=head2 labs

C<static method labs : long ($value : long);>

Returns the absolute value of $value.

=head2 lc

C<static method lc : string ($string : string);>

Converts the ASCII uppercase characters C<A-Z> in $string to the corresponding ASCII lowercase characters C<a-z>. And return it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 lcfirst

C<static method lcfirst : string ($string : string);>

If the first character of $string is an ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase characters C<a-z>. And return the converted string.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 look_code_point

C<static method look_code_point : int ($string : string, $offset_ref : int*);>

The same as L</"get_code_point">, but the offset is not updated.

=head2 memcpy

C<static method memcpy : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);>

Copies the range of $source to the the range of $dest.

The range of $dest is from $offset to the position proceeded by $length of the destination.

The range of $source is from $offset to the position proceeded by $length of the source.

The unit of $offset and $length is C<byte> size.

If the range of $source and the range of $dest overlap, the result is B<not> guaranteed.

Exceptions:

$dest must be defined. Otherwise an exception is thrown.

The type of $dest must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception is thrown.

$source must be defined. Otherwise an exception is thrown.

The type of $source must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception is thrown.

$dest must not be a read-only string. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$dest_offset + $length must be less than or equal to the length of $dest. Otherwise an exception is thrown.

$source_offset + $length must be less than or equal to the length of $source. Otherwise an exception is thrown.

=head2 memmove

C<static method memmove : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);>

The same as L</"memcpy">, but even if the range of $source and the range of $dest overlap, the result is guaranteed.

=head2 ord

C<static method ord : int ($string : string);>

The alias for the following code using L</"get_code_point">.

  my $offset = 0;
  my $code_point = Fn->get_code_point($string, \$offset);

=head2 powi

C<static method powi : int ($base : int, $exponant : int);>

Calculates the exponentiation from $base number and $exponant number.

Exceptions:

$exponant number must be greater than or equal to 0. Otherwise an exception is thrown.

If $base number is 0, $exponant number cannnot be 0.

=head2 powl

C<static method powl : long ($base : long, $exponant : long);>

Calculates the exponentiation from $base number and $exponant number.

Exceptions:

$exponant number must be greater than or equal to 0. Otherwise an exception is thrown.

If $base number is 0, $exponant number cannnot be 0.

=head2 rand

C<static method rand : double ($seed : int*, $max : int = 1);>

Gets a 64bit floating point random number that is greater than or equal to 0 and less than 1 using $seed.

If $max is specified, $max is multiplied to the return value.

The seed is updated.

This method is thread safe.

Examples:

  use Sys::Time;
  my $seed = (int)Sys::Time->time;
  my $rand0 = Fn->rand(\$seed);
  my $rand1 = Fn->rand(\$seed);

=head2 repeat

C<static method repeat : double ($string : string, $count : int);>

Concatenates $string the number of times specified in $count and return it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$repeat count must be greater than or equal to 0.

Examples:
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

=head2 replace_chars

C<static method replace_chars : void ($string : mutable string, $from_ch : int, $to_ch : int);>

Replaces all characters specified by the second argument in $string with the characters specified by the third argument.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 rindex

C<static method rindex : int ($string : string, $substring : string, $end : int = -1, $begin : int = 0);>

Searches for $substring in the range of $string from $begin to $end.

The search is performed from the end of the range of $string.

If $substring is found, returns the found offset, otherwise returns -1.

If $end is less than 0, $end is set to the length of $string minus 1.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$substring must be defined. Otherwise an exception is thrown.

$begin must be greater than or equal to 0. Otherwise an exception is thrown.

$end must be less than the length of $string.

=head2 sizeof_native_int

C<static method sizeof_native_int : int ();>

Returns the native C<int> size. This is the same value as C<sizeof(int)> in the C language.

=head2 sizeof_native_pointer

C<static method sizeof_native_pointer : int ();>

Returns the native pointer size. This is the same value as C<sizeof(void*)> in the C language.

=head2 shorten

C<static method shorten : void ($string : mutable string, $length : int32_t);>

Shortens $string to $length specified by the argument using L<SPVM::Document::NativeAPI/"shorten">.

If the length specified by the argument is greater than or equal to the length of the string, nothing is performed.

Exceptions:

$string must be defined.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 shorten_null_char

C<static method shorten_null_char : void ($string : mutable string);>

Shortens $string just before the first null character C<\0>.

If null characters is not found, do nothing.

Exceptions:

$string must be defined.  Otherwise an exception is thrown.

B<Example:>
  
  my $message = (mutable string)copy "foo\0bar";
  
  # "foo"
  my $message_shoten = Fn->shorten_null_char($message);
  
=head2 split

C<static method split : string[] ($separator : string, $string : string, $limit : int = -1);>

If $limit is less than 0, split $string by the specific $separator and convert them to an string array and return it.

If $limit is greater than than 0, the limit becomes the length of the maximam separated elements.

Exceptions:

$separator must be defined. Otherwise an exception is thrown.

$string must be defined. Otherwise an exception is thrown.

$limit cannnot be 0. Otherwise an exception is thrown.

=head2 substr

C<static method substr : string ($string : string, $offset : int, $length : int = -1, $replacement : string = undef);>

Cuts a substring of $length from $offset of $string, and returns it.

If $length is ommited, $length is the length of $string minus $offset.

If the length is less than 0, the length to the end of the string is calculated from the length of $string and $offset.

Replacement:

If $replacement is given, returns a string that is the replacement string $replacement of $string from $offset to $length.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $string. Otherwise an exception is thrown.

=head2 to_code_points

C<static method to_code_points : int[] ($string : string)>

Converts $string to the Unicode code points, and returns it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string contains an invalid Unicode code point. Otherwise an exception is thrown.

=head2 to_double

C<static method to_double : double ($string : string);>

Converts $string to the C<double> value using C<strtod> in the C language.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string must be the string that can be parsed as a double number. Otherwise an exception is thrown.

$string must be a double number in $correct range. Otherwise an exception is thrown.

Examples:

  my $string = "1.25";
  my $num = Fn->to_double($string);

=head2 to_float

C<static method to_float : float ($string : string);>

Converts $string to the C<double> value using C<strtof> in the C language.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string must be the string that can be parsed as a float number. Otherwise an exception is thrown.

$string must be a float number in $correct range. Otherwise an exception is thrown.

Examples:

  my $string = "1.25";
  my $num = Fn->to_float($string);

=head2 to_int

C<static method to_int : int ($string : string, $digit : int);>

The alias for the following code using L</"to_int_with_base">.

  my $ret = Fn->to_int_with_base($string, 10);

=head2 to_int_with_base

Converts $string to the C<int> value with $digit using C<strtol> in the C language.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string must be the string that can be parsed as an int number. Otherwise an exception is thrown.

$string must be an int number in $correct range. Otherwise an exception is thrown.

Examples:

  my $string = "-2147483648";
  my $num = Fn->to_int_with_base($string, 10);

=head2 to_long

C<static method to_long : long ($string : string);>

The alias for the following code using L</"to_long_with_base">.

  my $ret = Fn->to_long_with_base($string, 10);

=head2 to_long_with_base

C<static method to_long_with_base : long ($string : string, $digit : int);>

Converts $string to the C<long> value with $digit using C<strtoll> in the C language.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$digit must be one of 2, 8, 10, or 16. Otherwise an exception is thrown.

$string must be the string that can be parsed as a long number. Otherwise an exception is thrown.

$string must be a long number in $correct range. Otherwise an exception is thrown.

Examples:

  my $string = "-9223372036854775808";
  my $num = Fn->to_long_with_base($string, 10);

=head2 to_lower

C<static method to_lower : int ($code_point : int);>

If $code_point is the ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase character C<a-z>.

If $code_point is not an ASCII uppercase character, return itself.

=head2 to_upper

C<static method to_upper : int ($code_point : int);>

If $code_point is the ASCII lowercase character C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>.

If $code_point is not an ASCII lowercase character, return itself.

=head2 to_utf8_chars

C<static method to_utf8_chars : string[] ($string : string);>

Converts $string to UTF-8 characters, and returns it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string contains an invalid Unicode code point. Otherwise an exception is thrown.

Examples:

  my $string = "あいうa";
  
  # ["あ", "い", "う", "a"]
  my $utf8_chars = Fn->to_utf8_chars($string);

=head2 tr

C<static method tr : string ($string : string, $pattern : string, $replace : string)>

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

$string must be defined. Otherwise an exception is thrown.

$pattern must be defined. Otherwise an exception is thrown.

$replace must be defined. Otherwise an exception is thrown.

If $string contains an invalid Unicode code point, an exception is thrown.

The range format of the (pattern|replace) cannnot be contain an invalid Unicode code point. If so, an exception is thrown. If so, an exception is thrown.

The second character ot the range format of the (pattern|replace) must be \"-\". Otherwise an exception is thrown.

The range format of the (pattern|replace) must be 1 or 3 characters. Otherwise an exception is thrown.

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

C<static method trim : string ($string : string);>

Removes the right and left spaces of $string and return it.

The removed spaces is the same as the spaces L</"is_space"> method returns 1.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 uc

C<static method uc : string ($string : string);>

Converts the ASCII lowercase characters C<a-z> in $string to the corresponding ASCII uppercase characters C<A-Z>. And return it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 ucfirst

C<static method ucfirst : string ($string : string);>

If the first character of $string is an ASCII lowercase characters C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>. And return the converted string.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 utf8_length

C<static method utf8_length : int ($string : string)>

Gets the length as a UTF-8 string from $string, and returns it.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

If $string contains an invalid Unicode code point, an exception is thrown.

Examples:

  # 3
  my $utf8_length = Fn->utf8_length("あいう");

=head2 utf8_substr

C<static method utf8_substr : string ($string : string, $utf8_offset : int, $utf8_length : int = -1);>

Gets the substring from $string. The extracting range of the string is from $utf8_offset to the position proceeded by $utf8_length, and returns it.

If the length is less than 0, the length to the end of the string is calculated from the length of $string and $utf8_offset.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

If $string contains an invalid Unicode code point, an exception is thrown.

$utf8_offset + $utf8_length must be less than or equal to the UTF-8 length of $string. Otherwise an exception is thrown.

Examples:

  # "いえ"
  my $utf8_substr = Fn->utf8_substr("あいうえ", 1, 2);

=head2 merge_options

C<static method merge_options : object[] ($options1 : object[], $options2 : object[]);>

Creates a new any object array merging $options1 and $options2, and returns it.

If $options2 contains the same key of $options1, the key of $options1 is overwritten by the key of $options2.

Exceptions:

$options1 must be defined. Otherwise an exception is thrown.

$options2 must be defined. Otherwise an exception is thrown.

The length of $options1 must be an even number. Otherwise an exception is thrown.

The length of $options2 must be an even number. Otherwise an exception is thrown.

The key of $options1 must be defined. Otherwise an exception is thrown.

The key of $options1 must be the string type. Otherwise an exception is thrown.

The key of $options2 must be defined. Otherwise an exception is thrown.

The key of $options2 must be the string type. Otherwise an exception is thrown.

Exceptions of the L<Hash|SPVM::Hash> class can be thrown.

Examples:

  my $merged_options = Fn->merge_options({foo => 1, bar => 2}, {baz => 5});

=head2 object_to_int

C<static method object_to_int : int ($object : object);>

Converts the address of $object to a value of the int type, and returns it.

=head2 get_spvm_version_string

C<static method get_spvm_version_string : string ();>

Returns the the L<version string|SPVM::Document::Language/"Version String"> of the SPVM language.

=head2 get_spvm_version_string

C<static method get_spvm_version_string : string ();>

Returns the the L<version string|SPVM::Document::Language/"Version String"> of the SPVM language.

=head2 get_spvm_version_number

C<static method get_spvm_version_number : double ();>

Returns the L<version number|SPVM::Document::Language/"Version Number"> of the SPVM language.

=head2 get_version_number

C<static method get_version_number : double ($basic_type_name : string);>

Returns the L<version number|SPVM::Document::Language/"Version Number"> of a class.

Exceptions:

$basic_type_name must be defined. Otherwise an exception is thrown.

The class specified by $basic_type_name must be loaded. Otherwise an exception is thrown.

=head2 defer

C<static method defer : L<Scope::Guard|SPVM::Scope::Guard> ($callback : L<Callback|SPVM::Callback>);>

Calls the L<new|Scope::Guard/"new"> method in the L<Scope::Guard|SPVM::Scope::Guard> class and return its return value.

=head2 get_memory_blocks_count

C<static method get_memory_blocks_count : int ();>

Gets the count of the memory blocks allocated by the L<new_memory_block|SPVM::Document::NativeAPI/"new_memory_block"> native API.

=head2 to_address

C<static method to_address : string ($object : object);>

Gets the address of an object $object as a string.

=head2 check_option_names

C<static method check_option_names : void ($options : object[], $available_option_names : string[]);>

Checks if the options $options that contain name-value pairs has the available option names $available_option_names.

If $options is undef, nothing is done.

If the check is ok, nothing is done. Otherwise the following exception is thrown.

The "%s" option is not available.

%s is an option name.

Examples:

  my $options = {foo => 1, bar => 2};
  
  my $available_option_names = ["foo", "bar", "baz"];
  
  Fn->check_option_names($options, $available_option_names);

=head2 get_basic_type_id

  static method get_basic_type_id : int ($basic_type_name : string);

Gets the basic type ID of the basic type $basic_type_name.

Exceptions:

$basic_type_name must be defined. Otherwise an exception is thrwon.

If the basic type is not found, an exception is thrwon.

=head2 memset_char

C<static method memset_char : void ($string : mutable string, $char : int, $offset : int = 0, $length : int = -1);>

Set the range of the characters of the string $string to the character $char.

$char is an ASCII code.

The range of the characters of $string is from the offset $offset to the position proceeded by the length $length.

If $length is less than 0, the length to the end of the string is calculated from the length of $string and $offset.

Exceptions:

$string must be defined.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $string. Otherwise an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
