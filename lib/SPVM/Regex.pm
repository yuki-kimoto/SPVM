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

Get the replace count of the strings replaced by "replace_all" method.
