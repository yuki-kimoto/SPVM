package SPVM::StringUtil;

1;

=head1 NAME

SPVM::StringUtil - String Utilities

=head1 SYNOPSYS
  
  use SPVM::StringUtil;

  # Cut a newline LF
  {
    my $ret = SPVM::StringUtil->chomp_lf("abc\n");
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

=head2 chomp_lf

  sub chomp_lf : string ($string : string)

Copy the string and remove the newline "\n" from the end of string and return it.

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
            
=head2 isalnum

  sub isalnum : int ($code_point : int)

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return 1. If not, return 0.

=head2 isalpha

  sub isalpha : int ($code_point : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return 1. If not, return 0.

=head2 isblank

  sub isblank : int ($code_point : int)

If character is blank(' ', '\t'), return 1. If not, return 0.

=head2 iscntrl

  sub iscntrl : int ($code_point : int)

If character is a control character(0x00-0x1F, 0x7F), return 1. If not, return 0.

=head2 isdigit

  sub isdigit : int ($code_point : int)

If character is decimal digit ('0'～'9'), return 1. If not, return 0.

=head2 isgraph

  sub isgraph : int ($code_point : int)

If character has graphical representation(0x21-0x7E), return 1. If not, return 0.

=head2 islower

  sub islower : int ($code_point : int)

If character is lowercase letter('a'-'z'), return 1. If not, return 0.

=head2 isprint

  sub isprint : int ($code_point : int)

If character is printable(0x20-0x7E), return 1. If not, return 0.

=head2 ispunct

  sub ispunct : int ($code_point : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return 1. If not, return 0.

=head2 isspace

  sub isspace : int ($code_point : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return 1. If not, return 0.

=head2 isupper

  sub isupper : int ($code_point : int)

If character is uppercase letter('A'-'Z'), return 1. If not, return 0.

=head2 isxdigit

  sub isxdigit : int ($code_point : int)

If character is hexadecimal digit('0'-'9', 'A'-'F', 'a'-'f'), return 1. If not, return 0.

=head2 tolower

  sub tolower : int ($code_point : int)

Convert uppercase letter('A'-'Z') to lowercase. If the character is not uppercase letter, return the character.

=head2 toupper

  sub toupper : int ($code_point : int)

Convert lowercase letter('a'-'z') to lowercase. If the character is not uppercase letter, return the character.

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

=head2 strtoi

  sub strtoi : int ($string : string, $digit : int);

Convert the string to a int value with a digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][one more than 0-9]. Internal of [] is optional.

If convertion fails, a exception occuer.

  my $string = "-2147483648";
  my $num = strtoi($string, 10);

=head2 strtol

  sub strtol : long ($string : string, $digit : int);

Convert the string to long value with digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "-9223372036854775808";
  my $num = strtol($string, 10);

=head2 strtof

  sub strtof : float ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = strtof($string);

=head2 strtod

  sub strtod : double ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = strtod($string);

=head2 uc

  sub uc : string ($string : string)

Convert a lowercase string to a uppercase string.

If the string is undef, a exception occur.

=head2 ucfirst

  sub ucfirst : string ($string : string)

Convert the first character of a string to a uppercase character.

If the string is undef, a exception occur.

=head2 rindex

  sub rindex : int ($string : string, $sub_string : string, $offset : int)

Same as "index" function except that the search is the last of the string.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

