package SPVM::Unistd;

use SPVM 'SPVM::Unistd';

=head1 NAME

SPVM::Unistd - Unix standard library

=head1 SYNOPSYS
  
  use SPVM::Unistd (sleep);
  
  # Sleep 3 seconds
  sleep(3);

=head1 DESCRIPTION

Unix standard library.

=head1 METHODS

=head2 sleep

  sub sleep : void ($seconds : long)

Sleep specific seconds.
