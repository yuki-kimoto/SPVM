package SPVM::Unistd;

use SPVM 'SPVM::Unistd';

1;

=head1 NAME

SPVM::Unistd - Unix standard library

=head1 SYNOPSYS
  
  use SPVM::Unistd;
  
  # Sleep 3 seconds
  SPVM::Unistd->sleep(3);

=head1 DESCRIPTION

Unix standard library.

=head1 CLASS METHODS

=head2 sleep

  sub sleep : void ($seconds : long)

Sleep specific seconds.
