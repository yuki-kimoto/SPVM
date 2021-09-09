package SPVM::Unicode;

1;

=head1 NAME

SPVM::Unicode - Unicode in SPVM | Unicode utilities.

=head1 SYNOPSYS

  use Unicode;
  
  # Get a UTF-32(Unicode) codepoint from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position
  my $str = "あいうえお";
  my $pos = 0;
  while ((my $uchar = Unicode->uchar($str, \$pos)) >= 0) {
    # ...
  }
  
=head1 DESCRIPTION

L<Unicode|SPVM::Unicode> is Unicode utilities. This module privides the methods to convert UTF-8, UTF-16, UTF-32, Unicode codepoint each others.

=head1 STATIC METHODS

=head2 ERROR_INVALID_UTF8

  sub INVALID_UTF8 : int ();

return -2. this means uchar function find invalid utf8.

=head2 uchar

  sub uchar : int ($str : string, $offset_ref : int&);
  
Get a UTF-32(Unicode) codepoint from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position.

If offset is over the string length, this method returns -1.

If invalid UTF-8 character is found, this method returns -2. This is the same value of the return value of ERROR_INVALID_UTF8 method.

=head2 uchar_to_utf8

  sub uchar_to_utf8 : string ($uchar : int);

Convert a UTF-32(Unicode) codepoint to a UTF-8 character.

If the argument value is invalid UTF-32(Unicode) code point, this method returns undef.

=head2 utf8_to_utf16

  sub utf16_to_utf8 : string ($utf16_chars : short[]);

Convert big-endian UTF-16 code points to UTF-8 string.

=head2 utf32_to_utf16

  sub utf32_to_utf16 : short[] ($utf32_characters : int[]);

Convert UTF-32(Unicode) code points to big-endian UTF-16 code points.

=head2 utf16_to_utf32

  sub utf16_to_utf32 : int[] ($utf16_characters : short[]);

Convert big-endian UTF-16 code points to UTF-32(Unicode) code points.
