package SPVM::IO::File;

1;

=head1 NAME

SPVM::IO::Stdin - Standard out

=head1 SYNOPSYS
  
  use SPVM::IO::Stdin;
  
  # Print string to stdin
  SPVM::IO::Stdin->print("Hello");
  
  # Set stdin to binary mode
  SPVM::IO::Stdin->set_binmode(1);

  # Set stdin to text mode
  SPVM::IO::Stdin->set_binmode(0);

=head1 DESCRIPTION

L<SPVM::IO::Stdin> manipulate standard output stream.

=head1 CLASS METHODS

=head2 print

  sub print($string : string)

Print string to stdin.

=head2 set_binmode

  sub set_binmode : void ($binmode : int)

Set binnary mode of stdin. If binmode is not 0, stdin become binary mode. If binmode is 0, stdin become text mode.

This method has only the meaning on Windows OS.
