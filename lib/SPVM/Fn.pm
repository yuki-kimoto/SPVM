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

B<Fn> module provides SPVM Starndard Functions. B<Fn> contains number, string and array utilities.

=head1 Enumerations

=head2 GET_CODE_POINT_ERROR_OVER_STRING_RANGE

  -1

=head2 GET_CODE_POINT_ERROR_INVALID_UTF8

  -2

=head1 Class Methods

=head2 BYTE_MAX

  static method BYTE_MAX : byte ()

Same as L</"INT8_MAX">.

=head2 BYTE_MIN

  static method BYTE_MIN : byte ()

Same as L</"INT8_MIN">.

=head2 DBL_MAX

  static method DBL_MAX : double ()

Return the value of C<DBL_MAX> macro defined in C<float.h> header of C<C language>.

=head2 DBL_MIN

  static method DBL_MIN : double ()

Return the value of C<DBL_MIN> macro defined in C<float.h> header of C<C language>.

=head2 DOUBLE_MAX

  static method DOUBLE_MAX : double ()

Same as L</"DBL_MAX">.

=head2 DOUBLE_MIN

  static method DOUBLE_MIN : double ()

Same as L</"DBL_MIN">.

=head2 FLOAT_MAX

  static method FLOAT_MAX : float ()

Same as L</"FLT_MAX">.

=head2 FLOAT_MIN

  static method FLOAT_MIN : float()

Same as L</"FLT_MIN">.

=head2 FLT_MAX

  static method FLT_MAX : float ()

Return the value of C<FLT_MAX> macro defined in C<float.h> header of C<C language>.

=head2 FLT_MIN

  static method FLT_MIN : float ()

Return the value of C<FLT_MIN> macro defined in C<float.h> header of C<C language>.

=head2 INT16_MAX

  static method INT16_MAX : short ()

Return C<32767>. The maximum value of the signed 16bit integer.

=head2 INT16_MIN

  static method INT16_MIN : short ()

Return C<-32768>. The minimal value of the signed 16bit integer. 

=head2 INT32_MAX

  static method INT32_MAX : int ()

Return C<2147483647>. The maximum value of the signed 32bit integer.

=head2 INT32_MIN

  static method INT32_MIN : int ()

Return C<-2147483648>. The minimal value of the signed 32bit integer.

=head2 INT64_MAX

  static method INT64_MAX : long ()

Return C<9223372036854775807>. The maximum value of the signed 64bit integer. 

=head2 INT64_MIN

  static method INT64_MIN : long ()

Return C<-9223372036854775808>. The minimal value of the signed 64bit integer.

=head2 INT8_MAX

  static method INT8_MAX : byte ()

Same as L</"INT8_MAX">.

=head2 INT8_MIN

  static method INT8_MIN : byte ()

Return C<-128>. The minimal value of the signed 8bit integer.

=head2 INT_MAX

  static method INT_MAX : int ()

Same as L</"INT32_MAX">.

=head2 INT_MIN

  static method INT_MIN : int ()

Same as L</"INT32_MIN">.

=head2 LONG_MAX

  static method LONG_MAX : long ()

Same as L</"INT64_MAX">.

=head2 LONG_MIN

  static method LONG_MIN : long ()

Same as L</"INT64_MIN">.

=head2 SHORT_MAX

  static method SHORT_MAX : short ()

Same as L</"INT16_MAX">.

=head2 SHORT_MIN
  
  static method SHORT_MIN : short ()

Same as L</"INT16_MIN">.

=head2 UBYTE_MAX

  static method UBYTE_MAX : byte ()

Same as L</"UINT8_MAX">.

=head2 UINT16_MAX

  static method UINT16_MAX : short ()

Return C<-1>. This represents C<0xFFFF> in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  static method UINT32_MAX : int ()

Return C<-1>. This represents C<0xFFFFFFFF> in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  static method UINT64_MAX : long ()

Return C<-1>. This represents C<0xFFFFFFFFFFFFFFFF> in the unsigned 64bit integer in 2's complement.

=head2 UINT8_MAX

  static method UINT8_MAX : byte ()

Return C<-1>. The same bit expression of 0xFF in the unsigned 8bit integer in 2's complement.

=head2 UINT_MAX

  static method UINT_MAX : int ()

Same as L</"UINT32_MAX">.

=head2 ULONG_MAX

  static method ULONG_MAX : long

Same as L</"UINT64_MAX">.

=head2 USHORT_MAX

  static method USHORT_MAX : short ()

Same as L</"UINT16_MAX">.

=head2 abs

  static method abs : int ($value : int)

Return the absolute value of the input value.

=head2 chomp

  static method chomp : void ($string : mutable string)

Remove C<\n> of the end of the string.

If the string is C<undef> or the length is zero, nothing is performed.

=head2 chompr

  static method chompr : string ($string : string)

Copy the string and remove C<\n> of the end of the copied string and return it.

=head2 chr

  static method chr : string ($code_point : int)

Convert C<Unicode> code point to a C<UTF-8> character and return it.

If the C<Unicode> code point is not a L<Unicode scalar value|/"is_unicode_scalar_value">, return C<undef>.

=head2 contains

  static method contains : int ($string : string, $substring : string)

Search for the substring in the string. If the substring is found, return C<1>. Otherwise return C<0>.

The string must be defined. Otherwise an exception will be thrown.

The substring must be defined. Otherwise an exception will be thrown.

=head2 copy_string

  static method copy_string : string ($string : string)

The alias for the following code using L<copy operator|SPVM::Document::LanguageSpecification/"copy Operator">

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

=head2 get_next_code_point

  static method get_next_code_point : int ($string : string, $offset_ref : int*)

Same as L</"get_code_point">.

This method is depracated. Use L</"get_code_point"> instead.

=head2 get_code_point

  static method get_code_point : int ($string : string, $offset_ref : int*)

Parse the C<UTF-8> character at the offset of the string and return its Unicode code point.

The offset is updated to the position of the next C<UTF-8> character.

If the offset is greater than the length of the string, return the value of L</"GET_CODE_POINT_ERROR_OVER_STRING_RANGE">.

If the C<UTF-8> character is invalid, return the value of L</"GET_CODE_POINT_ERROR_INVALID_UTF8">.

The string must be defined. Otherwise an exception will occur.

The offset must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 hex

  static method hex : int ($hex_string : string)

Convert the hex string to the C<int> value and return it.

The hex string must be defined. Otherwise an exception will occur.

The length of the hex string must be C<1> to C<8>. Otherwise an exception will occur.

The hex string must contain only hex characters C<0-9a-zA-Z>. Otherwise an exception will occur.

=head2 index

  static method index : int ($string : string, $substring : string, $offset : int)

The alias for the following code using L</"index_len">.

  my $ret = &index_len($string, $substring, $offset, length $string - $offset);

=head2 index_len

  static method index_len : int ($string : string, $substring : string, $offset : int, $length : int)

Search for the substring in the string from the offset to the offset + the length.

If the substring is found, return the found offset. Otherwise return C<-1>.

The string must be defined. Otherwise an exception will occur.

The substring must be defined. Otherwise an exception will occur.

The offset must be greater than or equal to 0. Otherwise an exception will occur.

The max length must be greater than or equal to 0. Otherwise an exception will occur.

The offset + the length specified by the argument must be less than or equal to the length of the string. Otherwise an exception will occur.

=head2 is_alnum

  static method is_alnum : int ($code_point : int)

If the Unicode code point is an ASCII alphanumeric C<A-Za-z0-9>, return C<1>. Otherwise return C<0>.

=head2 is_alpha

  static method is_alpha : int ($code_point : int)

If the Unicode code point is an ASCII alphabetic C<A-Za-z>, return C<1>. Otherwise return C<0>.

=head2 is_array

  static method is_array : int ($object : object)

If the object is defined and the type of the object is the array type, return C<1>. Otherwise return C<0>.

=head2 is_blank

  static method is_blank : int ($code_point : int)

If the Unicode code point is an ASCII blank C<0x20(SP)>, C<0x9(HT)>, return C<1>. Otherwise return C<0>.

=head2 is_cntrl

  static method is_cntrl : int ($code_point : int)

If the Unicode code point is an ASCII control character C<0x00-0x1F>, C<0x7F>, return C<1>. Otherwise return C<0>.

=head2 is_digit

  static method is_digit : int ($code_point : int)

If the Unicode code point is an ASCII decimal digit C<0-9>, return C<1>. Otherwise return C<0>.

=head2 is_graph

  static method is_graph : int ($code_point : int)

If character has graphical representation C<0x21-0x7E>, return C<1>. Otherwise return C<0>.

=head2 is_hex_digit

  static method is_hex_digit : int ($code_point : int)

If the character is hexadecimal digit C<0-9a-fA-F>, return C<1>. Otherwise return C<0>.

=head2 is_lower

  static method is_lower : int ($code_point : int)

If the Unicode code point is an ASCII lowercase character C<a-z>, return C<1>. Otherwise return C<0>.

=head2 is_mulnum_array

  static method is_mulnum_array : int ($object : object)

If the object is defined and the type of the object is the multi-numeric array type, returns C<1>. Otherwise return C<0>.

=head2 is_numeric_array

  static method is_numeric_array : int ($object : object)

If the object is defined and the type of the object is the numeric array type, returns C<1>. Otherwise return C<0>.

=head2 is_object_array

  static method is_object_array : int ($object : object)

If he object is defined and the object is a object array, returns C<1>. Otherwise return C<0>.

=head2 is_perl_space

  static method is_perl_space : int ($code_point : int)

If the Unicode code point is an Perl ASCII space character C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')>,  return C<1>. Otherwise return C<0>.

Note that prior to Perl v5.18, C<\s> in ASCII mode did not match the vertical tab C<0x0B(VT)>. C<is_perl_space> is the same as this behavior.

Current Perl C<\s> in ASCII mode is the same as L</"is_space">.

=head2 is_perl_word

  static method is_perl_word : int ($code_point : int)

If the Unicode code point is an Perl ASCII word character C<a-zA-Z_0-9>, return C<1>. Otherwise return C<0>.

=head2 is_print

  static method is_print : int ($code_point : int)

If the Unicode code point is an ASCII printable C<0x20-0x7E>, return C<1>. Otherwise return C<0>.

=head2 is_punct

  static method is_punct : int ($code_point : int)

If the Unicode code point is an ASCII a punctuation character C<0x21-0x2f>, C<0x3a-0x40>, C<0x5b-0x60>, C<0x7b-0x7e>, return C<1>. Otherwise return C<0>.

=head2 is_space

  static method is_space : int ($code_point : int)

If the Unicode code point is an ASCII a white-space C<0x09(HT, '\t')>, C<0x0A(LF, '\n')>, C<0x0B(VT)>, C<0x0C(FF, '\f')>, C<0x0D(CR, '\r')>, C<0x20(SP, ' ')> return C<1>. Otherwise return C<0>.

=head2 is_upper

  static method is_upper : int ($code_point : int)

If the Unicode code point is an ASCII uppercase character C<A-Z>, return C<1>. Otherwise return C<0>.

=head2 is_xdigit

  static method is_xdigit : int ($code_point : int)

If the Unicode code point is an ASCII hexadecimal digit C<0-9A-Fa-f>, return C<1>. Otherwise return C<0>.

=head2 join

  static method join : string ($sep : string, $strings : string[])
  
Join a string array with separater and return it.

If separater is undef, an exception occurs.

If string array is undef, an exception occurs.

=head2 labs

  static method labs : long ($value : long)

Return the absolute value.

=head2 lc

  static method lc : string ($string : string)

Convert uppercase string to lowercase string.

=head2 lcfirst

  static method lcfirst : string ($string : string)

Convert first chracter of string from uppercase to lowercase.

=head2 look_next_code_point

  static method look_next_code_point : int ($string : string, $offset_ref : int*)

Same as L</"get_next_code_point">, but the offset is not updated.

This method is depracated. Use L</"look_code_point"> instead.

=head2 look_code_point

  static method look_code_point : int ($string : string, $offset_ref : int*)

Same as L</"get_code_point">, but the offset is not updated.

=head2 memcpy

  static method memcpy : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

The destination must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

If the destination is a read-only string, an exception is thrown.

The source must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

Copy the source to the destination with the given each offset and the given length by byte unit.

If source data range and destination data overlap, the result is not guaranteed.

The destination must be defined. Otherwise an exception will occur.

The source must be defined. Otherwise an exception will occur.

The length must be more than or equals to 0. Otherwise an exception will occur.

The destination offset + length must be within the range of the destination. Otherwise an exception will occur.

The source offset + length must be within the range of the source. Otherwise an exception will occur.

If source data range and destination data overlap, the result is not guaranteed.

=head2 memmove

  static method memmove : void ($dest : object, $dest_offset : int, $source : object, $source_offset : int, $length : int);

The destination must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

If the destination is a read-only string, an exception is thrown.

The source must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

Copy the source to the destination with the given each offset and the given length by byte unit.

If source data range and destination data overlap, the result is not guaranteed.

The destination must be defined. Otherwise an exception will occur.

The source must be defined. Otherwise an exception will occur.

The length must be more than or equals to 0. Otherwise an exception will occur.

The destination offset + length must be within the range of the destination. Otherwise an exception will occur.

The source offset + length must be within the range of the source. Otherwise an exception will occur.

=head2 ord

  static method ord : int ($utf8_char : string)

Gets the Unicode code point from the first character of the specified <C<UTF-8>> string.

If the specified C<UTF-8> character is C<undef>, returns a negative value.

If the length of the specified C<UTF-8> string is C<0>, returns a negative value.

If the specified C<UTF-8> character is invalid C<UTF-8> character, returns a negative value.

=head2 powi

  static method powi : int ($base : int, $exponant : int)

Calculate the exponentiation.

=head2 powl

  static method powl : long ($base : long, $exponant : long)

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

Get the repeat string.

If the string is not defined, an exception will be thrown.

If the repeat is not more than C<0>, an exception will be thrown.

B<Examples:>
  
  # "abcabcabc"
  my $repeat_string = Fn->repeat("abc", 3);

=head2 rindex

  static method rindex : int ($string : string, $substring : string, $offset : int)

The alias for the following code using L</"rindex_len">.

  my $ret = &rindex_len($string, $substring, $offset, length $string - $offset);

=head2 rindex_len

  static method rindex_len : int ($string : string, $substring : string, $offset : int, $length : int)

Search for the substring in the string from the offset to the offset + the length in the direction from back to front.

If the substring is found, return the found offset. Otherwise return C<-1>.

The string must be defined. Otherwise an exception will occur.

The substring must be defined. Otherwise an exception will occur.

The offset must be greater than or equal to 0. Otherwise an exception will occur.

The max length must be greater than or equal to 0. Otherwise an exception will occur.

The offset + the length specified by the argument must be less than or equal to the length of the string. Otherwise an exception will occur.

=head2 shorten

    static method shorten : void ($string : mutable string, $length : int32_t)

Shorten the string to the given length.

If the string is null, does nothing.

If the given length is greater than the length of the string, does nothing.

If the given length is lower than C<0>, the given length become C<0>.

In the level of native APIs, the charaters of the after the given length are filled with C<\0>.

=head2 split

  static method split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

=head2 sprintf

  static method sprintf : string ($format : string, $args : object[]...)

Create a formatted string with the format and the values.

=begin html

<table>
  <tr><th>Specifiers</th><th>Descriptions</th><th>Acceptable Types</th></tr>
  <tr><td>%c</td><td>An <code>UTF-8</code> character</td><td><a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>, <a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%d</td><td>Signed 32bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%u</td><td>Unsigned 32bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%x</td><td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%X</td><td>Unsiged 32 bit integer to a hexadecimal string using <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Int">Int</a></td></tr>
  <tr><td>%ld</td><td>Signed 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lu</td><td>Unsigned 64bit integer</td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lx</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9a-z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%lX</td><td>Unsiged 64 bit integer to a hexadecimal string using <code>0-9A-Z</code></td><td><a href="https://metacpan.org/pod/SPVM::Long">Long</a></td></tr>
  <tr><td>%f</td><td>64bit floating point</td><td><a href="https://metacpan.org/pod/SPVM::Double">Double</a>, <a href="https://metacpan.org/pod/SPVM::Float">Float</a></td></tr>
  <tr><td>%s</td><td>String</td><td>string</td></tr>
  <tr><td>%U</td><td>Unicode Code Point to a UTF-8 character</td><td></td></tr>
</table>

=end html

B<Specifier Options:>

Specifier options can be written between C<%> and the character of specifier such as C<d>, C<f>.

=begin html

<table>
  <tr><th>Specifier options</th><th>Descriptions</th></tr>
  <tr><td>0[DECIMAL_NUMBERS]</td><td>Zero padding</td></tr>
  <tr><td>+</td><td>Adding a plus sign</td></tr>
  <tr><td>-</td><td>Left justified</td></tr>
  <tr><td>.[DECIMAL_NUMBERS]</td><td>Precision</td></tr>
</table>

=end html

B<Examples:>
    
  # %d - "123"
  my $formatted_string = Fn->sprintf("%d", 123);
  
  # %5d - "  123"
  my $formatted_string = Fn->sprintf("%5d", 123);

  # %05d - "00123"
  my $formatted_string = Fn->sprintf("%05d", 123);
  
  # %+d - "+123"
  my $formatted_string = Fn->sprintf("%+d", 123);
  
  # %-5d - "123  "
  my $formatted_string = Fn->sprintf("%-5d", 123);
  
  # %d - "x"
  my $formatted_string = Fn->sprintf("%c", 'x');
  
  # %c - "あ"
  my $formatted_string = Fn->sprintf("%c", Fn->ord("あ"));

  # %s - "ABC"
  my $formatted_string = Fn->sprintf("%s", "ABC") eq "ABC");
  
  # %u - "4294967295"
  my $formatted_string = Fn->sprintf("%u", -1) eq "4294967295");
  
  # %f - "3.141500"
  my $formatted_string = Fn->sprintf("%f", 3.1415) eq "3.141500");
  
  # %.2f - "3.14"
  my $formatted_string = Fn->sprintf("%.2f", 3.1415) eq "3.14");
  
  # %g - "3.14"
  my $formatted_string = Fn->sprintf("%g", 3.14) eq "3.14");
  
  # %x - "ff"
  my $formatted_string = Fn->sprintf("%x", 255) eq "ff");
    
  # %x - "ffffffff"
  my $formatted_string = Fn->sprintf("%x", -1) eq "ffffffff");

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

Convert uppercase character('A'-'Z') to lowercase. If the character is not uppercase character, return the character.

=head2 to_upper

  static method to_upper : int ($code_point : int)

Convert lowercase character('a'-'z') to lowercase. If the character is not uppercase character, return the character.

=head2 trim_ascii_space

  static method trim_ascii_space : string ($string : string)

Remove right and left spaces of the string. These spaces is ascii standard spaces which can be checked by C<is_space> method.

If the argument string is undef, return undef.

This method is deprecated. Use trim instead.

=head2 trim

  static method trim : string ($string : string)

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
