package SPVM::StringUtil;

1;

=head1 NAME

SPVM::StringUtil - String Utilities

=head1 SYNOPSYS
  
  use SPVM::StringUtil;

  # Cut a newline LF
  {
    my $ret = SPVM::StringUtil->chompr("abc\n");
  }
  
  # Copy a string
  {
    my $string = "abc";
    my $string_copy = SPVM::StringUtil->copy_string ($string);
  }

  # Search substr
  {
    my $found_offset = SPVM::StringUtil->index("pppabcde", "bcd", 2);
  }

  # split a string by the specific separator
  my $string = "foo,bar,baz";
  my $splited_strs = SPVM::StringUtil->split(",", $string);

=head1 DESCRIPTION

String Utilities

=head1 STATIC METHODS

=head2 chompr

  sub chompr : string ($string : string)

Copy the string and remove "\n" of the end of line and return it.

=head2 copy_string

  sub copy_string : string ($string : string)

Copy a string.

If the array is undefined, a exception occurs.

=head2 index

  sub index : int ($string : string, $sub_string : string, $position : int)

index function searches for one string within another.
It returns the position of the first occurrence of $sub_string in $string at or after $position. If $position is omitted, starts
searching from the beginning of the string. $position before the
beginning of the string or after its end is treated as if it were
the beginning or the end, respectively. $position and the return
value are based at zero. If the substring is not found, "index"
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

=head2 replace

  sub replace : string ($string : string, $sub_string : string, $replace : string, $start_offset : int, $found_offset_ref : int&)

Replace the sub string in the string with a replace string and return the result string.

You can specify a byte offset of the string.

You can get the found byte offset by int reference.

  my $string = "abcde";
  my $sub_string = "bcd";
  my $replace = "AB";
  my $found_offset = 0;
  my $result_str = replace($string, $sub_string, $replace, 0, \$found_offset);

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

=head2 rindex

  sub rindex : int ($string : string, $sub_string : string, $offset : int)

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

