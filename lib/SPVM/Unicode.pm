package SPVM::Unicode;

1;

=head1 NAME

SPVM::Unicode - SPVM Unicode Utilities.

=head1 SYNOPSYS

=head2 SPVM

  use Unicode;
  
  # Get Unicode codepoints from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position
  my $str = "あいうえお";
  my $pos = 0;
  while ((my $uchar = Unicode->uchar($str, \$pos)) >= 0) {
    # ...
  }

=head2 Perl

  use SPVM 'Unicode';
  
  # Get Unicode codepoints from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position
  my $str = "あいうえお";
  my $pos = 0;
  while ((my $uchar = SPVM::Unicode->uchar($str, \$pos)) >= 0) {
    # ...
  }

=head1 DESCRIPTION

L<Unicode|SPVM::Unicode> is L<SPVM> Unicode utilities. This module privides the methods to convert UTF-8 bytes to/from Unicode codepoints.

=head1 CLASS METHODS

=head2 ERROR_INVALID_UTF8

  static method INVALID_UTF8 : int ();

return -2. this means uchar function find invalid utf8.

=head2 uchar

  static method uchar : int ($str : string, $offset_ref : int*);
  
Get a Unicode codepoint from UTF-8 string with the byte offset and proceed the offset to next UTF-8 character position.

If offset is over the string length, this method returns -1.

If invalid UTF-8 character is found, this method returns -2. This is the same value of the return value of ERROR_INVALID_UTF8 method.

=head2 uchar_to_utf8

  static method uchar_to_utf8 : string ($uchar : int);

Convert a Unicode codepoint to a UTF-8 character.

If the argument value is invalid Unicode code point, this method returns undef.
