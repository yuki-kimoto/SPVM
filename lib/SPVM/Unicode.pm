package SPVM::Unicode;

1;

=head1 NAME

SPVM::Unicode - SPVM Unicode Utilities.

=head1 SYNOPSYS

  use Unicode;
  
  # Get Unicode codepoints from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position
  my $string = "あいうえお";
  my $pos = 0;
  while ((my $uchar = Unicode->uchar($string, \$pos)) >= 0) {
    # ...
  }

=head1 DESCRIPTION

L<Unicode|SPVM::Unicode> is L<SPVM> Unicode utilities. This module privides the methods to convert UTF-8 bytes to/from Unicode codepoints.

=head1 CLASS METHODS

=head2 ERROR_INVALID_UTF8

  static method INVALID_UTF8 : int ();

return -2. this means uchar function find invalid utf8.

=head2 uchar

  static method uchar : int ($string : string, $offset_ref : int*);
  
Get a Unicode codepoint from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position.

If offset is over the string length, this method returns -1.

If invalid UTF-8 character is found, this method returns -2. This is the same value of the return value of ERROR_INVALID_UTF8 method.

=head2 uchar_to_utf8

  static method uchar_to_utf8 : string ($unicode_code_point : int);

Convert a Unicode codepoint to a UTF-8 character.

If the argument value is invalid Unicode code point, this method returns undef.

=head2 utf8_to_utf16

  static method utf8_to_utf16 : short[] ($utf8_string : string) {

Convert a UTF-8 string to a UTF-16 string.

=head2 utf16_to_utf8

  static method utf16_to_utf8 : string ($utf16_string : short[]) {

Convert a UTF-16 string to a UTF-8 string.

=head2 utf32_to_utf16

  static method utf32_to_utf16 : short[] ($utf32_string : int[]);

Convert a UTF-32 string to a UTF-16 string.

=head2 utf16_to_utf32

  static method utf16_to_utf32 : int[] ($utf16_string : short[]);

Convert a UTF-16 string to UTF-32 string.

