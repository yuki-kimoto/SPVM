package SPVM::Debug;

sub import {
  $ENV{SPVM_DEBUG} = 1;
}

1;

=head1 NAME

SPVM::Debug - Turn on debug mode

=head1 SYNOPSYS
  
  # Turn on debug mode
  use SPVM::Debug;

=head1 DESCRIPTION

L<SPVM::Debug> turn on debug mode.

In debug mode, line number is printed in exception message.
It is useful to know the line of exception.
