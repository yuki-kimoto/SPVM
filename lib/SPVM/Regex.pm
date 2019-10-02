package SPVM::Regex;

use SPVM 'SPVM::Regex';

1;

=head1 NAME

SPVM::Regex - Regular expression

=head1 SYNOPSYS
  
  use SPVM::Regex;
  
=head1 DESCRIPTION

L<SPVM::Regex> provides regular expression functions.

=head1 CLASS METHODS

  my $re = SPVM::Regex->new("^ab+c");

Create a new L<SPVM::Regex> object and compile the specific regex.

=head1 INSTANCE METHODS

=head2 caps

  sub caps : string[] ()

Get the strings captured by "match" method.

=head2  match_start

  sub match_start : int ()

Get the start byte offset of the string matched by "match" method or "match_offset" method.

=head2 match_length

  sub match_length : int ()

Get the byte length of the string matched by "match" method or "match_offset" method.

=head2 replace_count

  sub replace_count : int ();

Get the replace count of the strings replaced by "replace" or "replace_all" method.

=head2 match

  sub match : int ($self : self, $target : string)

Execute pattern matching to the specific string using.

If the pattern match succeeds, 1 is returned, otherwise 0 is returned.

You can get captured strings using "caps" method,
and get the byte offset using "match_start" method,
and get the length using "match_length" method.

=head2 match_offset

  sub match_offset : int ($self : self, $target : string, $byte_offset : int)

Execute pattern matching to the specific string and the start byte offset of the string.

If the pattern match succeeds, 1 is returned, otherwise 0 is returned.

You can get captured strings using "caps" method,
and get the byte offset of the matched whole string using "match_start" method,
and get the length of the matched whole string using "match_length" method.

=head2 replace

  sub replace  : string ($self : self, $target : string, $target_base_index : int, $replace_object : object)


=head2 replace_all

  sub replace_all  : string ($self : self, $target : string, $target_base_index : int, $replace_object : object)

