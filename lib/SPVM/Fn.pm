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

C<static method BYTE_MAX : byte ();>

The same as L</"INT8_MAX">.

=head2 BYTE_MIN

C<static method BYTE_MIN : byte ();>

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

C<static method INT16_MAX : short ();>

Returns 32767. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

C<static method INT16_MIN : short ();>

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

C<static method INT8_MAX : byte ();>

Returns 127. The maximum value of the signed 8bit integer.

=head2 INT8_MIN

C<static method INT8_MIN : byte ();>

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

C<static method SHORT_MAX : short ();>

The same as L</"INT16_MAX">.

=head2 SHORT_MIN
  
C<static method SHORT_MIN : short ();>

The same as L</"INT16_MIN">.

=head2 UBYTE_MAX

C<static method UBYTE_MAX : byte ();>

The same as L</"UINT8_MAX">.

=head2 UINT16_MAX

C<static method UINT16_MAX : short ();>

Returns -1. This represents C<0xFFFF> in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

C<static method UINT32_MAX : int ();>

Returns -1. This represents C<0xFFFFFFFF> in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

C<static method UINT64_MAX : long ();>

Returns -1. This represents C<0xFFFFFFFFFFFFFFFF> in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

C<static method UINT8_MAX : byte ();>

Returns -1. This represents C<0xFF> in the unsigned 8bit integer in 2's complement.

=head2 UINT_MAX

C<static method UINT_MAX : int ();>

The same as L</"UINT32_MAX">.

=head2 ULONG_MAX

C<static method ULONG_MAX : long>

The same as L</"UINT64_MAX">.

=head2 USHORT_MAX

C<static method USHORT_MAX : short ();>

The same as L</"UINT16_MAX">.

=head2 abs

C<static method abs : int ($value : int);>

Returns the absolute value of $value.

=head2 chomp

C<static method chomp : int ($string : mutable string);>

Removes C<\r\n> or C<\n> at the end of $string, and returns the removed length.

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

C<static method contains : int ($string : string, $substring : string, $begin : int = 0, $end : int = -1);>

Checks if $string contains $substring.

Implementation:

The alias for the following code using L</"index"> method.

  my $ret = Fn->index($string, $substring, $begin, $end) >= 0;

=head2 copy_string

C<static method copy_string : string ($string : string);>

The alias for the following code using L<copy operator|SPVM::Document::Language::Operators/"copy Operator">

  my $ret = copy $string;

=head2 crand

C<static method crand : int ($seed_ref : int*);>

Create a random number from 0 to L</"RAND_MAX"> using $$seed_ref and return it.

$$seed_ref is updated.

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

If an invalid UTF-8 is gotten, an exception is thrown set C<eval_error_id> to the basic type ID of L<Error::Unicode::InvalidUTF8|SPVM::Error::Unicode::InvalidUTF8> class.

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

If $substring is found, returns the found offset. Otherwise, returns -1.

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

If the Unicode $code_point is an ASCII alphanumeric C<A-Za-z0-9>, returns 1, otherwise returns 0.

=head2 is_alpha

C<static method is_alpha : int ($code_point : int);>

If the Unicode $code_point is an ASCII alphabetic C<A-Za-z>, returns 1, otherwise returns 0.

=head2 is_array

C<static method is_array : int ($object : object);>

If $object is defined and the type of $object is array type, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_array"> is used to check the type.

=head2 is_blank

C<static method is_blank : int ($code_point : int);>

If the Unicode $code_point is an ASCII blank C<0x20(SP, ' ')>, C<0x09(HT, '\t')>, returns 1, otherwise returns 0.

=head2 is_class

C<static method is_class : int ($object : object);>

If $object is defined and the type of $object is a class type, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_class"> is used to check the type.

=head2 is_cntrl

C<static method is_cntrl : int ($code_point : int);>

If the Unicode $code_point is an ASCII control character C<0x00-0x1F>, C<0x7F>, returns 1, otherwise returns 0.

=head2 is_digit

C<static method is_digit : int ($code_point : int);>

If the Unicode $code_point is an ASCII decimal digit 0-9, returns 1, otherwise returns 0.

=head2 is_graph

C<static method is_graph : int ($code_point : int);>

If $character is an ASCII graphical character C<0x21-0x7E>, returns 1, otherwise returns 0.

=head2 is_hex_digit

C<static method is_hex_digit : int ($code_point : int);>

If $character is a hexadecimal digit C<0-9a-fA-F>, returns 1, otherwise returns 0.

=head2 is_lower

C<static method is_lower : int ($code_point : int);>

If the Unicode $code_point is an ASCII lowercase character C<a-z>, returns 1, otherwise returns 0.

=head2 is_mulnum_array

C<static method is_mulnum_array : int ($object : object);>

If $object is defined and the type of $object is a multi-numeric array type, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_mulnum_array"> is used to check the type.

=head2 is_numeric_array

C<static method is_numeric_array : int ($object : object);>

If $object is defined and the type of $object is a numeric array type, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_numeric_array"> is used to check the type.

=head2 is_object_array

C<static method is_object_array : int ($object : object);>

If $object is defined and the type of $object is an object array type, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_object_array"> is used to check the type.

=head2 is_perl_space

C<static method is_perl_space : int ($code_point : int);>

If the Unicode $code_point is an Perl ASCII space character C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')>,  returns 1, otherwise returns 0.

Note that prior to Perl v5.18, C<\s> in ASCII mode did not match the vertical tab C<0x0B(VT)>. C<is_perl_space> is the same as this behavior.

Current Perl C<\s> in ASCII mode is the same as L</"is_space">.

=head2 is_perl_word

C<static method is_perl_word : int ($code_point : int);>

If the Unicode $code_point is an Perl ASCII word character C<a-zA-Z0-9_>, returns 1, otherwise returns 0.

=head2 is_pointer_class

C<static method is_pointer_class : int ($object : object);>

If $object is defined and $object is a L<pointer class|SPVM::Document::Language::Class/"Pointer Class">, returns 1, otherwise returns 0.

L<SPVM::Document::NativeAPI/"is_pointer_class"> is used to check the type.

=head2 is_print

C<static method is_print : int ($code_point : int);>

If the Unicode C<$$code_point> is an ASCII printable character C<0x20-0x7E>, returns 1, otherwise returns 0.

=head2 is_punct

C<static method is_punct : int ($code_point : int);>

If the Unicode $code_point is an ASCII a punctuation character C<0x21-0x2F>, C<0x3A-0x40>, C<0x5B-0x60>, C<0x7B-0x7E>, returns 1, otherwise returns 0.

=head2 is_space

C<static method is_space : int ($code_point : int);>

If the Unicode $code_point is an ASCII a white-space C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0B(VT)>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')> returns 1, otherwise returns 0.

=head2 is_upper

C<static method is_upper : int ($code_point : int);>

If $code_point is an ASCII uppercase character C<A-Z>, returns 1, otherwise returns 0.

=head2 is_xdigit

C<static method is_xdigit : int ($code_point : int);>

If $code_point is an ASCII hexadecimal digit C<0-9A-Fa-f>, returns 1, otherwise returns 0.

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

Copies the range of $source to the range of $dest.

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

Gets a 64bit floating point random number that is greater than or equal to 0 and less than $max using $seed.

If $max is specified, $max is multiplied to the return value.

The seed is updated.

This method is thread safe.

Examples:

  use Sys::Time;
  my $seed = (int)Sys::Time->time;
  my $rand0 = Fn->rand(\$seed);
  my $rand1 = Fn->rand(\$seed);

Exceptions:

The max number \$max must be greater than 0. Otherwise an exception is thrown.

See Also:

If you want to omit $seed, you can use L<Sys#rand|SPVM::Sys/"rand"> method.

=head2 repeat

C<static method repeat : string ($string : string, $count : int);>

Concatenates $string the number of times specified in $count and return it.

Exceptions:

The $string must be defined. Otherwise an exception is thrown.

The repeat count $count count be a non-negative integer. Otherwise an exception is thrown.

Examples:
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

See Also:

See L<Array#repeat|SPVM::Array/"repeat"> method about repeating an array.

=head2 replace_chars

C<static method replace_chars : void ($string : mutable string, $from_ch : int, $to_ch : int);>

Replaces all characters specified by the second argument in $string with the characters specified by the third argument.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

=head2 rindex

C<static method rindex : int ($string : string, $substring : string, $end : int = -1, $begin : int = 0);>

Searches for $substring in the range of $string from $begin to $end.

The search is performed from the end of the range of $string.

If $substring is found, returns the found offset. Otherwise, returns -1.

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

Cuts a substring of $length from $offset of a string $string, and returns it.

If $length is ommited or $offset plus $length is less than or equal to the length of $string, $length is set to the length of $string minus $offset.

If the length is less than 0, the length to the end of the string is calculated from the length of $string and $offset.

Replacement:

If $replacement is given, $string is set to a string that is the replacement string $replacement of $string from $offset to $length.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$string must be a string. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

The offset $offset must be less than or equal to the length of the string $string. Otherwise an exception is thrown.

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

C<static method to_int : int ($string : string, $unsigned : int = 0);>

The alias for the following code using L</"to_int_with_base">.

  my $ret = Fn->to_int_with_base($string, 10, $unsigned);

=head2 to_int_with_base

C<static method to_int_with_base : int ($string : string, $digit : int, $unsigned : int = 0);>

Converts $string to the C<int> value with $digit.

If $unsigned is a true value, the conversion is performed using C<strtoull> in the C language, and the range is checked as a 32-bit unsigned integer.

If $unsigned is a false value, the conversion is performed using C<strtol> in the C language, and the range is checked as a 32-bit signed integer.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$digit must be one of 2, 8, 10, or 16. Otherwise an exception is thrown.

$string must be the string that can be parsed as a 32-bit integer. Otherwise an exception is thrown.

$string must be an integer in the correct range. Otherwise an exception is thrown.

Examples:

  my $string = "4294967295";
  my $num = Fn->to_int_with_base($string, 10, 1);

=head2 to_long

C<static method to_long : long ($string : string, $unsigned : int = 0);>

The alias for the following code using L</"to_long_with_base">.

  my $ret = Fn->to_long_with_base($string, 10, $unsigned);

=head2 to_long_with_base

C<static method to_long_with_base : long ($string : string, $digit : int, $unsigned : int = 0);>

Converts $string to the C<long> value with $digit.

If $unsigned is a true value, the conversion is performed using C<strtoull> in the C language, and the range is checked as a 64-bit unsigned integer.

If $unsigned is a false value, the conversion is performed using C<strtoll> in the C language, and the range is checked as a 64-bit signed integer.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$digit must be one of 2, 8, 10, or 16. Otherwise an exception is thrown.

$string must be the string that can be parsed as a 64-bit integer. Otherwise an exception is thrown.

$string must be a 64-bit integer in the correct range. Otherwise an exception is thrown.

Examples:

  my $string = "18446744073709551615";
  my $num = Fn->to_long_with_base($string, 10, 1);

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

If $options1 is not defined, $options1 is set to an empty any object array.

If $options2 is not defined, $options2 is set to an empty any object array.

Exceptions:

The length of $options1 must be an even number. Otherwise an exception is thrown.

The length of $options2 must be an even number. Otherwise an exception is thrown.

Exceptions thrown by the L<merge_object|SPVM::Array/"merge_object"> in the Array class could be thrown.

Examples:

  my $merged_options = Fn->merge_options({foo => 1, bar => 2}, {baz => 5});

=head2 object_to_int

C<static method object_to_int : int ($object : object);>

Converts the address of $object to a value of int type, and returns it.

=head2 get_spvm_version_string

C<static method get_spvm_version_string : string ();>

Returns the L<version string|SPVM::Document::Language::Class/"Version String"> of the SPVM language.

=head2 get_spvm_version_number

C<static method get_spvm_version_number : double ();>

Returns the L<version number|SPVM::Document::Language::Class/"Version Number"> of the SPVM language.

=head2 get_version_string

C<static method get_version_string : string ($basic_type_name : string);>

Returns the L<version string|SPVM::Document::Language::Class/"Version String"> of the class $basic_type_name.

=head2 get_version_number

C<static method get_version_number : double ($basic_type_name : string);>

Returns the L<version number|SPVM::Document::Language::Class/"Version Number"> of the class $basic_type_name.

Exceptions:

$basic_type_name must be defined. Otherwise an exception is thrown.

The class specified by $basic_type_name must be loaded. Otherwise an exception is thrown.

=head2 defer

C<static method defer : L<Scope::Guard|SPVM::Scope::Guard> ($callback : L<Callback|SPVM::Callback>);>

Calls L<Scope::Guard#new|Scope::Guard/"new"> and return its return value.

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

=head2 or

C<static method or : object ($left : object, $right : object);>

If $left is a true value, returns $left. Otherwise, returns $right;

=head2 if

C<static method if : object ($condition : int, $left : object, $right : object);>

If $condition is a true value, returns $left. Otherwise, returns $right;

=head2 grep

C<static method grep : object[] ($callback : L<Callback::Grep|SPVM::Callback::Grep>, $array : object[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_byte

C<static method grep_byte : byte[] ($callback : L<Callback::Grep::Byte|SPVM::Callback::Grep::Byte>, $array : byte[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_short

C<static method grep_short : short[] ($callback : L<Callback::Grep::Short|SPVM::Callback::Grep::Short>, $array : short[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_int

C<static method grep_int : int[] ($callback : L<Callback::Grep::Int|SPVM::Callback::Grep::Int>, $array : int[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_long

C<static method grep : long[] ($callback : L<Callback::Grep::Long|SPVM::Callback::Grep::Long>, $array : long[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_float

C<static method grep_float : float[] ($callback : L<Callback::Grep::Float|SPVM::Callback::Grep::Float>, $array : float[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 grep_double

C<static method grep_double : double[] ($callback : L<Callback::Grep::Double|SPVM::Callback::Grep::Double>, $array : double[]);>

Returns a new array containing only the elements of the array $array for which the callback $callback returned a true value.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 map

C<static method map : object[] ($callback : L<Callback::Map|SPVM::Callback::Map>, $array : object[]);>

Returns a new array with each element of the array $array processed in the callback $callback.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 map_expand

C<static method map_expand : object[] ($callback : L<Callback::MapExpand|SPVM::Callback::MapExpand>, $array : object[]);>

Returns a new array with each element of the array $array processed in the callback $callback which returns multiple values.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The callback $callback must be defined. Otherwise, an exception is thrown.

=head2 get_compile_type_name

C<static method get_compile_type_name : string ($basic_type_name : string, $type_dimension : int, $type_flag : int);>

Create a compile-time type name given the basic type name $basic_type_name, the type dimension $type_dimension, the type flag $type_flag, and returns it.

If C<$type_flag & 1> is true, the type is a reference type.

If C<$type_flag & 2> is true, the type is one that have a mutable qualifier.

Examples:
  
  # int[][]
  my $compile_type_name = Fn->get_compile_type_name("int", 2, 0);
  
  # int*
  my $compile_type_name = Fn->get_compile_type_name("int", 0, 1);

Exceptions:

The basic type name $basic_type_name must be defined. Otherwise, an exception is thrown.

The type dimension $type_dimension must be grether than or equal to 0 and less than or equal to 255. Otherwise, an exception is thrown.

=head2 is_any_numeric_array

C<static method is_any_numeric_array : int ($object : object);>

If the object $object is defined and the type of $object is a numeric array type or a multi-numeric array type, returns 1, otherwise returns 0.

An any numeric array means an array of a numeric array type or a multi-numeric array type.

=head2 array_length

C<static method array_length : int ($array : object);>

Returns the array length of the array $array.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The type of the array $array must be an array type. Otherwise, an exception is thrown.

=head2 get_elem_size

C<static method get_elem_size : int ($array : object);>

Returns the element byte size of the array $array.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The type of the array $array must be an array type. Otherwise, an exception is thrown.

=head2 get_elem_type_name

C<static method get_elem_type_name : string ($array : object);>

Returns the element type name of the array $array.

Implementation:
  
  my $type_name = type_name $array;
  my $ret = Fn->substr($type_name, 0, length $type_name - 2);

Note that this is not the real element type name of each element. It is merely the type name of the array, but without the trailing C<[]>.

Exceptions:

The array $array must be defined. Otherwise, an exception is thrown.

The type of the array $array must be an array type. Otherwise, an exception is thrown.

=head2 print_stderr

C<static method print_stderr : void ($string : string);>

Prints the string $string to L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

If $string is undef, this method produces no output.

=head2 say_stderr

C<static method say_stderr : void ($string : string);>

Prints the string $string with a new line C<\n> to L<SPVM's standard error|SPVM::Document::Language::System/"Standard Streams">.

If $string is undef, this method prints C<\n>.

=head2 memcmp

C<static method memcmp : void ($data1 : object, $data1_offset : int, $data2 : object, $data2_offset : int, $length : int);>

Compares the data $data1 from index $dest_offset with the data $data2 from index $data2_offset to the length $length using C<memcmp> C function, and returns the result.

Unit of $data1_offset, $data2_offset, and $length is bytes.

Exceptions:

$data1 must be defined. Otherwise an exception is thrown.

The type of $data1 must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception is thrown.

$data2 must be defined. Otherwise an exception is thrown.

The type of $data2 must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception is thrown.

$data1 must not be a read-only string. Otherwise an exception is thrown.

$length must be greater than or equal to 0. Otherwise an exception is thrown.

$data1_offset + $length must be less than or equal to the length of $data1. Otherwise an exception is thrown.

$data2_offset + $length must be less than or equal to the length of $data2. Otherwise an exception is thrown.

=head2 reverse_inplace

C<static method reverse_inplace : void ($array_or_string : object);>

Reverses the elements in the array $array_or_string or the characters in the string $array_or_string in-place.

Exceptions:

$array_or_string must be defined. Otherwise an exception is thrown.

The type of $array_or_string must be an array type or string type. Otherwise an exception is thrown.

The string $array_or_string must not be read-only. Otherwise an exception is thrown.

=head2 is_string_array

C<static method is_string_array : int ($object : object)>

If $object is defined and the type of $object is string array type C<string[]>, returns 1, otherwise returns 0.

=head2 length

C<static method length : int ($array_or_string : object);>

Returns the array length of $array_or_string if the type of $array_or_sring is an array type.

Returns the string length of $array_or_string if the type of $array_or_sring is string type.

Exceptions:

$array_or_string must be defined. Otherwise an exception is thrown.

The type of $array_or_string must be an array type or string type. Otherwise an exception is thrown.

=head2 get_elem_or_char_size

C<static method get_elem_or_char_size : int ($array_or_string : object);>

Returns the element byte size of the array $array if the type of $array_or_sring is an array type.

Returns 1, the byte size of C<byte> type if the type of $array_or_sring is string type.

Exceptions:

The array $array_or_string must be defined. Otherwise, an exception is thrown.

The type of the array $array_or_string must be an array type. Otherwise, an exception is thrown.

=head2 copy

C<static method copy : object ($array_or_string : object, $shallow : int = 0);>

Copies $array_or_string and returns it.

Implementation:

If $array_or_string is undef, returns undef.

If the type of $array_or_string is an string array type and $shallow is a false value, the copy is performed by L<Array#copy_string|SPVM::Array/"copy_string"> method.

If the type of $array_or_string is an string array type and $shallow is a true value, the copy is performed by L<Array#copy_string_address|SPVM::Array/"copy_string_address"> method.

If the type of $array_or_string is an object array type and $shallow is a false value, the copy is performed by L<Array#copy_object|SPVM::Array/"copy_object"> method given L<Cloner#default_cloner|SPVM::Cloner/"default_cloner"> method.

If the type of $array_or_string is an object array type and $shallow is a true value, the copy is performed by L<Array#copy_object_address|SPVM::Array/"copy_object_address"> method.

If the type of $array_or_string is a numeric array type or a multi-numeric array type, the copy is performed by L<Array#copy_any_numeric|SPVM::Array/"copy_any_numeric"> method.

If the type of $array_or_string is string type, the copy is performed by C<copy> operator.

Exceptions:

The type of $array_or_string must be an array type or string type.

=head2 reverse

C<static method reverse : object ($array_or_string : object);>

Reterns a new array that reverses the elements in the array $array_or_string or the characters in the string $array_or_string.

This method calls L</"copy"> method and L</"reverse_inplace"> method to create a new array and reverses elements.

Exceptions:

Exceptions thrown by L</"copy"> method and L</"reverse_inplace"> method could be thrown.

=head2 slice

C<static method slice : object ($array : object, $offset : int, $length :int);>

Slices the array $array from the offset $offset to the length $length, and returns it.

The type of $array must be an object array type, a numeric array type, or a multi-numeric array type.

This method calls L<Array#memcpy_object|SPVM::Array/"memcpy_object"> method or L</"memcpy"> method to slice $array.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

The type of the array $array must be an object array type, a numeric array type or a multi-numeric array type. Otherwise an exception is thrown.

Exceptions thrown by L<Array#memcpy_object|SPVM::Array/"memcpy_object"> method or L</"memcpy"> method could be thrown.

=head2 system_is_little_endian 

C<static method system_is_little_endian ();>

If the system is little-endian, returns 1, otherwise returns 0.

=head2 sprintf

C<static method sprintf : string ($format : string, $args : object...);>

Calls L<Format#sprintf|SPVM::Format/"sprintf"> method and returns its return value.

Exceptions:

Exceptions thrown by thrown L<Format#sprintf|SPVM::Format/"sprintf"> method could be thrown.

Examples:

  my $ret = Fn->sprintf("%s %d", "abc", 2);

=head2 sort_asc

C<static method sort_asc : object ($array : object);>

Copies the array $array using L</"copy"> method, sorts the copied array by ascendant order, and returns it.

The type of $array must be a numeric array type.

Thie method calls a corresponding method in L<Sort|SPVM::Sort> class.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

The type of the array $array must be a numeric array type. Otherwise an exception is thrown.

=head2 sort_desc

C<static method sort_desc : object ($array : object);>

Copies the array $array using L</"copy"> method, sorts the copied array by descendant order, and returns it.

The type of $array must be a numeric array type.

Thie method calls a corresponding method in L<Sort|SPVM::Sort> class.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

The type of the array $array must be a numeric array type. Otherwise an exception is thrown.

=head2 sort

C<static method sort : object[] ($array : object[], $comparator : Comparator);>

Copies the array $array using L</"copy"> method, sorts the copied array by the order specified by the comparator $comparator, and returns it.

This method calls L<Sort#sort_object|SPVM::Sort/"sort_object"> method to sort the copied array.

Exceptions:

Exceptions thrown by thrown L<Sort#sort_object|SPVM::Sort/"sort_object"> method could be thrown.

=head2 change_endian

C<static method change_endian : void ($binary : mutable string, $size : int, $offset : int = 0);>

The byte order of the first $size bytes of the binary data $binary at the offset $offset are reversed in-plcae.

Exceptions:

The binary data $binary must be defined. Otherwise an exception is thrown.

The byte size $size must be greater than 0. Otherwise an exception is thrown.

The offset $offset must be greater than or equal to 0. Otherwise an exception is thrown.

The byte size $size must be less than or equal to the offset $offset plus the length of the binary data $binary.

=head2 big_endian_to_system_endian

C<static method big_endian_to_system_endian : void ($binary : mutable string, $size : int, $offset : int = 0);>

The byte order of the first $size bytes of the binary data $binary at the offset $offset are changed from big endian to system endian.

This method calls L</"change_endian"> method to change endian.

Exceptions:

Exceptions thrown by L</"change_endian"> method could be thrown.

=head2 system_endian_to_big_endian

C<static method system_endian_to_big_endian : void ($binary : mutable string, $size : int, $offset : int = 0);>

The byte order of the first $size bytes of the binary data $binary at the offset $offset are changed from system endian to big endian.

This method calls L</"change_endian"> method to change endian.

Exceptions:

Exceptions thrown by L</"change_endian"> method could be thrown.

=head2 little_endian_to_system_endian

C<static method little_endian_to_system_endian : void ($binary : mutable string, $size : int, $offset : int = 0);>

The byte order of the first $size bytes of the binary data $binary at the offset $offset are changed from little endian to system endian.

This method calls L</"change_endian"> method to change endian.

Exceptions:

Exceptions thrown by L</"change_endian"> method could be thrown.

=head2 system_endian_to_little_endian

C<static method system_endian_to_little_endian : void ($binary : mutable string, $size : int, $offset : int = 0);>

The byte order of the first $size bytes of the binary data $binary at the offset $offset are changed from system endian to little endian.

This method calls L</"change_endian"> method to change endian.

Exceptions:

Exceptions thrown by L</"change_endian"> method could be thrown.

=head2 pack

C<static method pack : string ($template : string, $objects : object...);>

Converts the objects $objects to a binary data according to the template $template, and returns it.

This method just creates a L<Packer|SPVM::Packer> object, calls L<Packer#pack|SPVM::Packer/"pack"> method, and returns its return value.

Examples:

  my $binary = Fn->pack("l", 3);

=head2 unpack

C<static method unpack : object[] ($template : string, $binary : string);>

Converts the binary data $binary to the objects $objects according to the template $template, and returns it.

This method just creates a L<Packer|SPVM::Packer> object, calls L<Packer#unpack|SPVM::Packer/"unpack"> method, and returns its return value.

=head2 no_free

C<static method no_free : int ($object : object);>

Calls L<no_free|SPVM::Document::NativeAPI/"no_free"> native API given $object, and retunrs its return value.

Excetpions:

The object $object must be defined. Otherwise an exception is thrown.

=head2 set_no_free

C<static method set_no_free : void ($object : object, $no_free : int);>

Calls L<set_no_free|SPVM::Document::NativeAPI/"set_no_free"> native API given $object, $no_free.

Excetpions:

The object $object must be defined. Otherwise an exception is thrown.

=head2 get_pointer

C<static method get_pointer : L<Address|SPVM::Address> ($object : object);>

Creates a new L<Address|SPVM::Address> object, sets its L<pointer value|SPVM::Document::NativeClass/"Pointer Value"> to the pointer value of the object $object, and returns the new object.

Exceptions:

The object $object must be defined. Otherwise an exception is thrown.

=head2 set_pointer

C<static method set_pointer : void ($object : object, $address : L<Address|SPVM::Address>);>

Sets the L<pointer value|SPVM::Document::NativeClass/"Pointer Value"> of the object $object to the pointer value of the address $address.

Exceptions:

The object $object must be defined. Otherwise an exception is thrown.

The address $address must be defined. Otherwise an exception is thrown.

=head2 has_null_pointer

C<static method has_null_pointer : int ($object : object);>

If the L<pointer value|SPVM::Document::NativeClass/"Pointer Value"> of the object $object is NULL, returns 1, otherwise returns 0.

Exceptions:

The object $object must be defined. Otherwise an exception is thrown.

=head2 eq_pointer

C<static method eq_pointer : int ($object1 : object, $object2 : object);>

If the L<pointer value|SPVM::Document::NativeClass/"Pointer Value"> of the object $object1 is equal to the pointer value of the object $object2, returns 1, otherwise returns 0.

Exceptions:

The object $object1 must be defined. Otherwise an exception is thrown.

The object $object2 must be defined. Otherwise an exception is thrown.

=head2 pointer_to_string

C<static method pointer_to_string : string ($object : object);>

Creates a new string that contains the hex address of the L<pointer value|SPVM::Document::NativeClass/"Pointer Value"> of the object $object, and returns the new string.

Exceptions:

The object $object must be defined. Otherwise an exception is thrown.

=head2 dump_object_internal

C<static method dump_object_internal : string ($object : object);>

Calls L<dump_object_internal|SPVM::Document::NativeAPI/"dump_object_internal"> native API, and returns its return value.

=head2 get_seed

C<static method get_seed : int ();>

Calls L<get_seed|SPVM::Document::NativeAPI/"get_seed"> native API, and retunrs its return value.

=head2 set_seed

C<static method set_seed : void ($seed : int);>

Calls L<get_seed|SPVM::Document::NativeAPI/"set_seed"> native API given $seed.

=head2 seed_initialized

C<static method seed_initialized : int ();>

Calls L<seed_initialized|SPVM::Document::NativeAPI/"seed_initialized"> native API, and retunrs its return value.

=head2 get_basic_type_name_in_version_from

C<static method get_basic_type_name_in_version_from : basic_type_name ($basic_type_name : basic_type_name);>

Returns the basic_type_name specified by L<version_from Statement|SPVM::Document::Language::Class/"version_from Statement"> of the class $basic_type_name. If it is not specified, returns undef.

=head2 destroy_cache_class_vars

C<static method destroy_cache_class_vars : void ();>

Sets all class variables of all classes that is a object type and C<cache> class variable attribute is specified to undef.

=head2 destroy_runtime_permanent_vars

C<method destroy_runtime_permanent_vars : void ();>

Sets all runtime permanent variables to undef.

Currently thie method calls L</"destroy_cache_class_vars> method and sets C<$@> to undef.

=head2 range

C<static method range : int[] ($begin : int, $end : int);>

Returns a new array of values counting (up by ones) from $begin to $end.

Exceptions:

$end must be greater than or equal to $begin.

=head2 to_hash

C<static method to_hash : Hash ($options : L<Hash|SPVM::Hash>|object[]);>

Converts the options $options to a L<Hash|SPVM::Hash> object, and returns it.

If $options is C<undef>, returns an empty L<Hash|SPVM::Hash> object.

If $options is a Hash object, returns it.

If $options is an C<object[]> object, it is converted to a L<Hash|SPVM::Hash> object, and returns it.

Exceptions:

If the type of the options \$options must be Hash or object[], an exception is thrown.

=head2 get_basic_type_name_by_id

C<static method get_basic_type_name_by_id : string ($basic_type_id : int);>

Gets the basic type name of the basic type ID $basic_type_id.

Exceptions:

If the basic type specified by $basic_type_id is not found, an exception is thrown.

=head2 get_current_basic_type_name

C<static method get_current_basic_type_name : string ($level : int = 0);>

Returns the basic type name at the specified caller stack level C<$level>.

The level 0 represents the currently executing method's basic type. The level 1 represents its caller's basic type, and so on.

Exceptions:

If the specified C<$level> is out of range of the caller stack, an exception is thrown.

=head2 get_current_basic_type_name

C<static method get_current_basic_type_name : string ();>

Returns the name of the basic type (class) that owns the method currently being executed.

This method calls the L<get_current_method|SPVM::Document::NativeAPI/"get_current_method"> native API.

Exceptions:

If the caller stack is empty, an exception is thrown.

=head2 get_current_method_abs_name

C<static method get_current_method_abs_name : string ($level : int = 0);>

Returns the absolute name of the method at the specified caller stack level C<$level>.

The absolute name is the basic type name and the method name joined with C<#>.

The level 0 represents the currently executing method. The level 1 represents its caller, and so on.

Exceptions:

If the specified C<$level> is out of range of the caller stack, an exception is thrown.

=head2 build_exception_message

C<static method build_exception_message : string ($level : int = 0);>

Reconstructs the full exception message, including a stack trace, using the metadata stored in the runtime stack.

The I<level> argument specifies the starting depth of the stack trace relative to the current call. For example, 0 starts from the caller of this method.

This method calls the L<build_exception_message|SPVM::Document::NativeAPI/"build_exception_message"> native API.

Returns the newly created string object.

Examples:

  eval {
    MyModule->do_something;
  };
  
  if ($@) {
    # Reconstruct the message with a stack trace
    my $full_message = Fn->build_exception_message;
    warn $full_message;
  }

=head2 get_call_depth

C<static method get_call_depth : int ();>

Returns the current call stack depth.

The base depth is -1. When the first method is called, the depth becomes 0.

=head2 is_utf8

C<static method is_utf8 : int ($string : string);>

Checks if the given string I<$string> is a valid UTF-8 sequence.

If the string is a valid UTF-8 sequence, returns 1, otherwise returns 0.

Notes:

This method calls the L<is_utf8|SPVM::Document::NativeAPI/"is_utf8"> native API.

Exceptions:

The string I<$string> must be defined. Otherwise an exception is thrown.

=head2 to_byte_object_unsigned

C<static method to_byte_object_unsigned : Byte ($string : string);>

Converts $string to a L<Byte|SPVM::Byte> object that is treated as an unsigned 8-bit integer.

The conversion is performed using L</"to_int"> with the C<$unsigned> argument set to 1.

The L<new_unsigned|SPVM::Byte/"new_unsigned"> method of the L<Byte|SPVM::Byte> class is used to create the object.

Exceptions:

Exceptions thrown by L</"to_int"> are thrown.

Examples:

  my $string = "255";
  my $obj = Fn->to_byte_object_unsigned($string);

=head2 to_short_object_unsigned

C<static method to_short_object_unsigned : Short ($string : string);>

Converts $string to a L<Short|SPVM::Short> object that is treated as an unsigned 16-bit integer.

The conversion is performed using L</"to_int"> with the C<$unsigned> argument set to 1.

The L<new_unsigned|SPVM::Short/"new_unsigned"> method of the L<Short|SPVM::Short> class is used to create the object.

Exceptions:

Exceptions thrown by L</"to_int"> are thrown.

Examples:

  my $string = "65535";
  my $obj = Fn->to_short_object_unsigned($string);

=head2 to_int_object_unsigned

C<static method to_int_object_unsigned : Int ($string : string);>

Converts $string to an L<Int|SPVM::Int> object that is treated as an unsigned 32-bit integer.

The conversion is performed using L</"to_int"> with the C<$unsigned> argument set to 1.

The L<new_unsigned|SPVM::Int/"new_unsigned"> method of the L<Int|SPVM::Int> class is used to create the object.

Exceptions:

Exceptions thrown by L</"to_int"> are thrown.

Examples:

  my $string = "4294967295";
  my $obj = Fn->to_int_object_unsigned($string);

=head2 to_long_object_unsigned

C<static method to_long_object_unsigned : Long ($string : string);>

Converts $string to a L<Long|SPVM::Long> object that is treated as an unsigned 64-bit integer.

The conversion is performed using L</"to_long"> with the C<$unsigned> argument set to 1.

The L<new_unsigned|SPVM::Long/"new_unsigned"> method of the L<Long|SPVM::Long> class is used to create the object.

Exceptions:

Exceptions thrown by L</"to_long"> are thrown.

Examples:

  my $string = "18446744073709551615";
  my $obj = Fn->to_long_object_unsigned($string);

=head2 getrandom

C<static method getrandom : string ($size : int);>

Gets OS-specific secure random bytes with the given size I<$size>.

The following APIs are used depending on the operating system:

=over 2

=item * Windows: L<BCryptGenRandom|https://learn.microsoft.com/en-us/windows/win32/api/bcrypt/nf-bcrypt-bcryptgenrandom>

=item * macOS, iOS, BSD: L<arc4random_buf|https://man.freebsd.org/cgi/man.cgi?query=arc4random_buf>

=item * Linux, Android: L<getrandom|https://man7.org/linux/man-pages/man2/getrandom.2.html>

=back

Returns a newly created string object filled with the random bytes.

Exceptions:

The size I<$size> must be non-negative. Otherwise an exception is thrown.

If the random bytes could not be retrieved from the OS, an exception is thrown.

Examples:

  # Get a 32-byte secure random key
  my $key = Fn->getrandom(32);

  # Get a 16-byte nonce for AES-GCM
  my $nonce = Fn->getrandom(12);

=head1 See Also

=over 2

=item * L<Types|SPVM::Document::Language::Types>

=item * L<Class Definition|SPVM::Document::Language::Class>

=item * L<Operators|SPVM::Document::Language::Operators>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
