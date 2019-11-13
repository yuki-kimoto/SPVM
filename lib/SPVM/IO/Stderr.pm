package SPVM::IO::File;

use SPVM 'SPVM::IO::Stderr';

1;

=head1 NAME

SPVM::IO::Stderr - Standard out

=head1 SYNOPSYS
  
  use SPVM::IO::Stderr;
  
  # Print string to stdout
  SPVM::IO::Stderr->print("Hello");
  
  # Set stdout to binary mode
  SPVM::IO::Stderr->set_binmode(1);

  # Set stdout to text mode
  SPVM::IO::Stderr->set_binmode(0);

=head1 DESCRIPTION

L<SPVM::IO::Stderr> manipulate standard output stream.

=head1 CLASS METHODS

=head2 print

  sub print($string : string)

Print string to stdout.

=head2 set_binmode

  sub set_binmode : void ($binmode : int)

Set binnary mode of stdout. If binmode is not 0, stdout become binary mode. If binmode is 0, stdout become text mode.

This method has only the meaning on Windows OS.
