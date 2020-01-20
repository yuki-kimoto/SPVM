package SPVM::IO::Stdout;

1;

=head1 NAME

SPVM::IO::Stdout - Standard out

=head1 SYNOPSYS
  
  use SPVM::IO::Stdout;
  
  # Print string to stdout
  SPVM::IO::Stdout->print("Hello");
  
=head1 DESCRIPTION

L<SPVM::IO::Stdout> manipulate standard output stream.

=head1 CLASS METHODS

=head2 AUTO_FLUSH

  sub AUTO_FLUSH : byte ()

Get auto flash flag. Default auto flush flag is 0.

=head2 SET_AUTO_FLUSH

  sub SET_AUTO_FLUSH : void ($bool : byte)

Set auto flush flag.

=head2 print

  sub print : void ($string : string)

Print string to stdout.

If auto flush flag(AUTO_FLUSH) is true, flush buffered data to stdout after C<print> method call.

=head2 flush

  sub flush : void ()

Flush buffered data to stdout. If error, a exception occur.
