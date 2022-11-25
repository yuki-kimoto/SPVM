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

Returns C<-1>. The return type is the C<int> type.

=head2 GET_CODE_POINT_ERROR_INVALID_UTF8

Returns C<-2>. The return type is the C<int> type.

=head1 Class Methods

=head2 BYTE_MAX

  static method BYTE_MAX : int ()

The same as L</"INT8_MAX">.

=head2 BYTE_MIN

  static method BYTE_MIN : int ()

The same as L</"INT8_MIN">.

=head2 DBL_MAX

  static method DBL_MAX : double ()

Returns the value of C<DBL_MAX> macro defined in C<float.h> header of C<C language>.

=head2 DBL_MIN

  static method DBL_MIN : double ()

Returns the value of C<DBL_MIN> macro defined in C<float.h> header of C<C language>.

=head2 DOUBLE_MAX

  static method DOUBLE_MAX : double ()

The same as L</"DBL_MAX">.

=head2 DOUBLE_MIN

  static method DOUBLE_MIN : double ()

The same as L</"DBL_MIN">.

=head2 FLOAT_MAX

  static method FLOAT_MAX : float ()

The same as L</"FLT_MAX">.

=head2 FLOAT_MIN

  static method FLOAT_MIN : float()

The same as L</"FLT_MIN">.

=head2 FLT_MAX

  static method FLT_MAX : float ()

Returns the value of C<FLT_MAX> macro defined in C<float.h> header of C<C language>.

=head2 FLT_MIN

  static method FLT_MIN : float ()

Returns the value of C<FLT_MIN> macro defined in C<float.h> header of C<C language>.

=head2 INT16_MAX

  static method INT16_MAX : int ()

Returns C<32767>. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

  static method INT16_MIN : int ()

Returns C<-32768>. The minimal value of the signed 16bit integer. 

=head2 INT32_MAX

  static method INT32_MAX : int ()

Returns C<2147483647>. The maximum value of the signed 32bit integer.

=head2 INT32_MIN

  static method INT32_MIN : int ()

Returns C<-2147483648>. The minimal value of the signed 32bit integer.

=head2 INT64_MAX

  static method INT64_MAX : long ()

Returns C<9223372036854775807>. The maximum value of the signed 64bit integer. 

=head2 INT64_MIN

  static method INT64_MIN : long ()

Returns C<-9223372036854775808>. The minimal value of the signed 64bit integer.

=head2 INT8_MAX

  static method INT8_MAX : int ()

Returns C<127>. The maximum value of the signed 8bit integer.

=head2 INT8_MIN

  static method INT8_MIN : int ()

Returns C<-128>. The minimal value of the signed 8bit integer.

=head2 INT_MAX

  static method INT_MAX : int ()

The same as L</"INT32_MAX">.

=head2 INT_MIN

  static method INT_MIN : int ()

The same as L</"INT32_MIN">.

=head2 LONG_MAX

  static method LONG_MAX : long ()

The same as L</"INT64_MAX">.

=head2 LONG_MIN

  static method LONG_MIN : long ()

The same as L</"INT64_MIN">.

=head2 RAND_MAX

  static method RAND_MAX : int ()

Returns C<2147483647>.

=head2 SHORT_MAX

  static method SHORT_MAX : int ()

The same as L</"INT16_MAX">.

=head2 SHORT_MIN
  
  static method SHORT_MIN : int ()

The same as L</"INT16_MIN">.

=head2 UBYTE_MAX

  static method UBYTE_MAX : int ()

The same as L</"UINT8_MAX">.

=head2 UINT16_MAX

  static method UINT16_MAX : int ()

Returns C<-1>. This represents C<0xFFFF> in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  static method UINT32_MAX : int ()

Returns C<-1>. This represents C<0xFFFFFFFF> in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  static method UINT64_MAX : long ()

Returns C<-1>. This represents C<0xFFFFFFFFFFFFFFFF> in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

  static method UINT8_MAX : int ()

Returns C<-1>. This represents C<0xFF> in the unsigned 8bit integer in 2's complement.

=head2 UINT_MAX

  static method UINT_MAX : int ()

The same as L</"UINT32_MAX">.

=head2 ULONG_MAX

  static method ULONG_MAX : long

The same as L</"UINT64_MAX">.

=head2 USHORT_MAX

  static method USHORT_MAX : int ()

The same as L</"UINT16_MAX">.

=head2 abs

  static method abs : int ($value : int)

Returns the absolute value of the $value.

=head2 chomp

  static method chomp : void ($string : mutable string)

Removes C<\r\n> or C<\n> at the end of the $string.

The $string must be defined. Otherwise an exception will occur.

=head2 chompr

  static method chompr : string ($string : string)

Copies the $string and removes C<\r\n> or C<\n> at the end of the copied string and returns it.

The $string must be defined. Otherwise an exception will occur.

=head2 chr

  static method chr : string ($code_point : int)

Converts the $code_point to the C<UTF-8> character and return it.

If the $code_point is not a Unicode scalar value, return C<undef>.

=head2 contains

  static method contains : int ($string : string, $substring : string, $offset = 0 : int, $length = -1 : int)

The alias for the following code using L</"index>.

  my $ret = Fn->index($string, $substring, $offset, $length) >= 0;

=head2 copy_string

  static method copy_string : string ($string : string)

The alias for the following code using the L<copy operator|SPVM::Document::Language/"copy Operator">

  my $ret = copy $string;

=head2 crand

  static method crand : int ($seed : int*);

Create a random number from C<0> to L</"RAND_MAX"> using the seed and return it.

The seed is updated.

This method is thread safe.

B<Examples:>
  
  use Time;
  my $seed = (int)Time->time;
  my $crand0 = Fn->crand(\$seed);
  my $crand1 = Fn->crand(\$seed);

=head2 get_code_point

  static method get_code_point : int ($string : string, $offset_ref : int*)

Parses the C<UTF-8> character at the offset of the string and return its Unicode code point.

The offset is updated to the position of the next C<UTF-8> character.

If the offset is greater than the length of the string, return the value of L</"GET_CODE_POINT_ERROR_OVER_STRING_RANGE">.

If the C<UTF-8> character is invalid, return the value of L</"GET_CODE_POINT_ERROR_INVALID_UTF8">.

The $string must be defined. Otherwise an exception will occur.

The $offset must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 hex

  static method hex : int ($hex_string : string)

Converts the hex string to the C<int> value and return it.

The $hex string must be defined. Otherwise an exception will occur.

The length of the $hex string must be C<1> to C<8>. Otherwise an exception will occur.

The $hex string must contain only hex characters C<0-9a-zA-Z>. Otherwise an exception will occur.

=head2 index

  static method index : int ($string : string, $substring : string, $offset = 0 : int, $length = -1 : int)

Searches for the substring in the range of the string from the offset to the position proceeded by the length.

If the $substring is found, return the $found offset. Otherwise return C<-1>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the string and the offset.

The $string must be defined. Otherwise an exception will occur.

The $substring must be defined. Otherwise an exception will occur.

The $offset must be greater than or equal to C<0>. Otherwise an exception will occur.

The $offset + the $length must be less than or equal to the length of the $string. Otherwise an exception will occur.

=head2 is_alnum

  static method is_alnum : int ($code_point : int)

If the $Unicode code point is an ASCII alphanumeric C<A-Za-z0-9>, return C<1>. Otherwise return C<0>.

=head2 is_alpha

  static method is_alpha : int ($code_point : int)

If the $Unicode code point is an ASCII alphabetic C<A-Za-z>, return C<1>. Otherwise return C<0>.

=head2 is_array

  static method is_array : int ($object : object)

If the $object is defined and the type of the $object is the L<array type|SPVM::Document::Language/"Array Type">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_array"> is used to check the type.

=head2 is_blank

  static method is_blank : int ($code_point : int)

If the $Unicode code point is an ASCII blank C<0x20(SP, ' ')>, C<0x09(HT, '\t')>, return C<1>. Otherwise return C<0>.

=head2 is_class

  static method is_class : int ($object : object)

If the $object is defined and the type of the $object is the L<class type|SPVM::Document::Language/"Class Type">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_class"> is used to check the type.

=head2 is_cntrl

  static method is_cntrl : int ($code_point : int)

If the $Unicode code point is an ASCII control character C<0x00-0x1F>, C<0x7F>, return C<1>. Otherwise return C<0>.

=head2 is_digit

  static method is_digit : int ($code_point : int)

If the $Unicode code point is an ASCII decimal digit C<0-9>, return C<1>. Otherwise return C<0>.

=head2 is_graph

  static method is_graph : int ($code_point : int)

If the $character is an ASCII graphical character C<0x21-0x7E>, return C<1>. Otherwise return C<0>.

=head2 is_hex_digit

  static method is_hex_digit : int ($code_point : int)

If the $character is a hexadecimal digit C<0-9a-fA-F>, return C<1>. Otherwise return C<0>.

=head2 is_lower

  static method is_lower : int ($code_point : int)

If the $Unicode code point is an ASCII lowercase character C<a-z>, return C<1>. Otherwise return C<0>.

=head2 is_mulnum_array

  static method is_mulnum_array : int ($object : object)

If the $object is defined and the type of the $object is the L<multi-numeric array type|SPVM::Document::Language/"Multi-Numeric Array Type">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_mulnum_array"> is used to check the type.

=head2 is_numeric_array

  static method is_numeric_array : int ($object : object)

If the $object is defined and the type of the $object is the L<numeric array type|SPVM::Document::Language/"Numeric Array Type">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_numeric_array"> is used to check the type.

=head2 is_object_array

  static method is_object_array : int ($object : object)

If the $object is defined and the type of the $object is an L<object array type|SPVM::Document::Language/"Object Array Type">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_object_array"> is used to check the type.

=head2 is_perl_space

  static method is_perl_space : int ($code_point : int)

If the $Unicode code point is an Perl ASCII space character C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')>,  return C<1>. Otherwise return C<0>.

Note that prior to Perl v5.18, C<\s> in ASCII mode did not match the vertical tab C<0x0B(VT)>. C<is_perl_space> is the same as this behavior.

Current Perl C<\s> in ASCII mode is the same as L</"is_space">.

=head2 is_perl_word

  static method is_perl_word : int ($code_point : int)

If the $Unicode code point is an Perl ASCII word character C<a-zA-Z0-9_>, return C<1>. Otherwise return C<0>.

=head2 is_pointer_class

  static method is_pointer_class : int ($object : object)

If the $object is defined and the $object is a L<pointer class|SPVM::Document::Language/"Pointer Class">, return C<1>. Otherwise return C<0>.

L<SPVM::Document::NativeAPI/"is_pointer_class"> is used to check the type.

=head2 is_print

  static method is_print : int ($code_point : int)

If the $Unicode code point is an ASCII printable character C<0x20-0x7E>, return C<1>. Otherwise return C<0>.

=head2 is_punct

  static method is_punct : int ($code_point : int)

If the $Unicode code point is an ASCII a punctuation character C<0x21-0x2F>, C<0x3A-0x40>, C<0x5B-0x60>, C<0x7B-0x7E>, return C<1>. Otherwise return C<0>.

=head2 is_space

  static method is_space : int ($code_point : int)

If the $Unicode code point is an ASCII a white-space C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0B(VT)>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')> return C<1>. Otherwise return C<0>.

=head2 is_upper

  static method is_upper : int ($code_point : int)

If the $code_point is an ASCII uppercase character C<A-Z>, return C<1>. Otherwise return C<0>.

=head2 is_xdigit

  static method is_xdigit : int ($code_point : int)

If the $code_point is an ASCII hexadecimal digit C<0-9A-Fa-f>, return C<1>. Otherwise return C<0>.

=head2 join

  static method join : string ($separator : string, $strings : string[])

Concatenates the strings with the separater and return it.

The $strings must be defined. Otherwise an exception will occur.

The $separator must be defined. Otherwise an exception will occur.

=head2 labs

  static method labs : long ($value : long)

Returns the absolute value of the input value.

=head2 lc

  static method lc : string ($string : string)

Converts the ASCII uppercase characters C<A-Z> in the string to the corresponding ASCII lowercase characters C<a-z>. And return it.

The $string must be defined. Otherwise an exception will occur.

=head2 lcfirst

  static method lcfirst : string ($string : string)

If the first character of the string is an ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase characters C<a-z>. And return the converted string.

The $string must be defined. Otherwise an exception will occur.

=head2 look_code_point

  static method look_code_point : int ($string : string, $offset_ref : int*)

The same as L</"get_code_point">, but the offset is not updated.

=head2 memcpy

  static method memcpy : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

Copies the range of the source to the the range of the destination.

The range of the destination is from the offset to the position proceeded by the length of the destination.

The range of the source is from the offset to the position proceeded by the length of the source.

The unit of the offset and the length is C<byte> size.

If the range of the source and the range of the destination overlap, the result is B<not> guaranteed.

dest must be defined. Otherwise an exception will occur.

The type of the $dest must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception will occur.

The $source must be defined. Otherwise an exception will occur.

The type of the $source must be the C<string> type, the numeric array type, or the multi-numeric array type. Otherwise an exception will occur.

The $dest must not be a read-only string. Otherwise an exception will occur.

The $length must be greater than or equal to C<0>. Otherwise an exception will occur.

The $dest_offset + the $length must be less than or equal to the length of the $dest. Otherwise an exception will occur.

The $source_offset + the $length must be less than or equal to the length of the $source. Otherwise an exception will occur.

=head2 memmove

  static method memmove : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

The same as L</"memcpy">, but even if the range of the source and the range of the destination overlap, the result is guaranteed.

=head2 ord

  static method ord : int ($string : string);

The alias for the following code using L</"get_code_point">.

  my $offset = 0;
  my $code_point = Fn->get_code_point($string, \$offset);

=head2 powi

  static method powi : int ($base : int, $exponant : int)

Calculates the exponentiation from the base number and the exponant number.

The $exponant number must be greater than or equal to C<0>. Otherwise an exception will occur.

If the $base number is C<0>, the $exponant number can't be C<0>. Otherwise an exception will occur.

=head2 powl

  static method powl : long ($base : long, $exponant : long)

Calculates the exponentiation from the base number and the exponant number.

The $exponant number must be greater than or equal to C<0>. Otherwise an exception will occur.

If the $base number is C<0>, the $exponant number can't be C<0>. Otherwise an exception will occur.

=head2 rand

  static method rand : double ($seed : int*)

Gets a 64bit floating point random number that is greater than or equal to C<0> and less than C<1> using the seed.

The seed is updated.

This method is thread safe.

B<Examples:>

  use Time;
  my $seed = (int)Time->time;
  my $rand0 = Fn->rand(\$seed);
  my $rand1 = Fn->rand(\$seed);

=head2 repeat

  static method repeat : double ($string : string, $count : int)

Concatenates the string the number of times specified in the count and return it.

The $string must be defined. Otherwise an exception will occur.

The $repeat count must be greater than or equal to C<0>. Otherwise an exception will occur.

B<Examples:>
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

=head2 replace_chars

  static method replace_chars : void ($string : mutable string, $from_ch : int, $to_ch : int)

Replaces all characters specified by the second argument in the string with the characters specified by the third argument.

The $string must be defined. Otherwise an exception will occur.

=head2 rindex

  static method rindex : int ($string : string, $substring : string, $offset = 0 : int, $length = -1 : int)

Searches for the substring in the range of the string from the offset to the position proceeded by the length in the direction from back to front.

If the $substring is found, return the $found offset. Otherwise return C<-1>.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the string and the offset.

The $string must be defined. Otherwise an exception will occur.

The $substring must be defined. Otherwise an exception will occur.

The $offset must be greater than or equal to C<0>. Otherwise an exception will occur.

The $offset + the $length must be less than or equal to the length of the $string. Otherwise an exception will occur.

=head2 sizeof_native_int

  static method sizeof_native_int : int ();

Returns the native C<int> size. This is the same value as C<sizeof(int)> in C<C language>.

=head2 sizeof_native_pointer

  static method sizeof_native_pointer : int ();

Returns the native pointer size. This is the same value as C<sizeof(void*)> in C<C language>.

=head2 shorten

    static method shorten : void ($string : mutable string, $length : int32_t)

Shortens the string to the length specified by the argument using L<SPVM::Document::NativeAPI/"shorten">.

If the length specified by the argument is greater than or equal to the length of the string, nothing is performed.

The $string must be defined. Otherwise an exception will occur.

The $length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 shorten_null_char

  static method shorten_null_char : void ($string : mutable string)

Shortens the string just before the first null character C<\0>.

If null characters is not found, do nothing.

The $string must be defined. Otherwise an exception will occur.

B<Example:>
  
  my $message = (mutable string)copy "foo\0bar";
  
  # "foo"
  my $message_shoten = Fn->shorten_null_char($message);
  
=head2 split

  static method split : string[] ($separator : string, $string : string, $limit = -1 : int)

If the limit is less than C<0>, split a string by the specific separator and convert them to an string array and return it.

If the limit is greater than than C<0>, the limit becomes the length of the maximam separated elements.

The $separator must be defined. Otherwise an exception will occur.

The $string must be defined. Otherwise an exception will occur.

The $limit can't be C<0>. Otherwise an exception will occur.

=head2 substr

  static method substr : string ($string : string, $offset : int, $length = -1 : int)

Gets the substring from the string. The extracting range of the string is from the offset to the position proceeded by the length.

If the length is less than C<0>, the length to the end of the string is calculated from the length of the string and the offset.

=head2 to_double

  static method to_double : double ($string : string);

Converts the string to the C<double> value using C<strtod> in C<C language>.

The $string must be defined. Otherwise an exception will occur.

The $string must be the string that can be parsed as a double number. Otherwise an exception will occur.

The $string must be a double number in the $correct range. Otherwise an exception will occur.

B<Examples:>

  my $string = "1.25";
  my $num = Fn->to_double($string);

=head2 to_float

  static method to_float : float ($string : string);

Converts the string to the C<double> value using C<strtof> in C<C language>.

The $string must be defined. Otherwise an exception will occur.

The $string must be the string that can be parsed as a float number. Otherwise an exception will occur.

The $string must be a float number in the $correct range. Otherwise an exception will occur.

B<Examples:>

  my $string = "1.25";
  my $num = Fn->to_float($string);

=head2 to_int

  static method to_int : int ($string : string, $digit : int);

The alias for the following code using L</"to_int_with_base">.

  my $ret = Fn->to_int_with_base($string, 10);

=head2 to_int_with_base

Converts the string to the C<int> value using C<strtol> in C<C language>.

The $string must be defined. Otherwise an exception will occur.

The $string must be the string that can be parsed as an int number. Otherwise an exception will occur.

The $string must be an int number in the $correct range. Otherwise an exception will occur.

B<Examples:>

  my $string = "-2147483648";
  my $num = Fn->to_int_with_base($string, 10);

=head2 to_long

  static method to_long : long ($string : string);

The alias for the following code using L</"to_long_with_base">.

  my $ret = Fn->to_long_with_base($string, 10);

=head2 to_long_with_base

  static method to_long_with_base : long ($string : string, $digit : int);

Converts the string to the C<long> value using C<strtoll> in C<C language>.

The $string must be defined. Otherwise an exception will occur.

The digit must be one of C<2>, C<8>, C<10>, or C<16>.

The $string must be the string that can be parsed as a long number. Otherwise an exception will occur.

The $string must be a long number in the $correct range. Otherwise an exception will occur.

B<Examples:>

  my $string = "-9223372036854775808";
  my $num = Fn->to_long_with_base($string, 10);

=head2 to_lower

  static method to_lower : int ($code_point : int)

If the code point is the ASCII uppercase character C<A-Z>, it is converted to the corresponding ASCII lowercase character C<a-z>.

If the code point is not an ASCII uppercase character, return the code point specified by the argument.

=head2 to_upper

  static method to_upper : int ($code_point : int)

If the code point is the ASCII lowercase character C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>.

If the code point is not an ASCII lowercase character, return the code point specified by the argument.

=head2 trim

  static method trim : string ($string : string)

Removes the right and left spaces of the string and return it.

The removed spaces is the same as the spaces L</"is_space"> method returns C<1>.

The $string must be defined. Otherwise an exception will occur.

=head2 uc

  static method uc : string ($string : string)

Converts the ASCII lowercase characters C<a-z> in the string to the corresponding ASCII uppercase characters C<A-Z>. And return it.

The $string must be defined. Otherwise an exception will occur.

=head2 ucfirst

  static method ucfirst : string ($string : string)

If the first character of the string is an ASCII lowercase characters C<a-z>, it is converted to the corresponding ASCII uppercase character C<A-Z>. And return the converted string.

The $string must be defined. Otherwise an exception will occur.
