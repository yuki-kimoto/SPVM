package SPVM::IO::Stderr;

1;

=head1 NAME

SPVM::IO::Stderr - Standard out

=head1 SYNOPSYS
  
  use SPVM::IO::Stderr;
  
  # Print string to stderr
  SPVM::IO::Stderr->print("Hello");
  
=head1 DESCRIPTION

L<SPVM::IO::Stderr> manipulate standard output stream.

=head1 STATIC METHODS

=head2 AUTO_FLUSH

  sub AUTO_FLUSH : byte ()

Get auto flash flag. Default auto flush flag is 1.

=head2 SET_AUTO_FLUSH

  sub SET_AUTO_FLUSH : void ($bool : byte)

Set auto flush flag.

=head2 print

  sub print : void ($string : string)

Print string to stderr.

If auto flush flag(AUTO_FLUSH) is true, flush buffered data to stderr after C<print> method call.

=head2 flush

  sub flush : void ()

Flush buffered data to stderr. If error, a exception occur.
