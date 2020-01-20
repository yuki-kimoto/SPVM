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

=head2 print

  sub print($string : string)

Print string to stdout.
