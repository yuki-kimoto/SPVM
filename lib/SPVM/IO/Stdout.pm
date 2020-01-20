package SPVM::IO::File;

1;

=head1 NAME

SPVM::IO::Stdout - Standard out

=head1 SYNOPSYS
  
  use SPVM::IO::Stdout;
  
  # Print string to stdout
  SPVM::IO::Stdout->print("Hello");
  
  # Set stdout to binary mode
  SPVM::IO::Stdout->set_binmode(1);

  # Set stdout to text mode
  SPVM::IO::Stdout->set_binmode(0);

=head1 DESCRIPTION

L<SPVM::IO::Stdout> manipulate standard output stream.

=head1 CLASS METHODS

=head2 print

  sub print($string : string)

Print string to stdout.

=head2 set_binmode

  sub set_binmode : void ($binmode : int)

Set binnary mode of stdout. If binmode is not 0, stdout become binary mode. If binmode is 0, stdout become text mode.

This method has only the meaning on Windows OS.
