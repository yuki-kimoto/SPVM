=head1 NAME

SPVM::Complex_2f - Complex_2f in SPVM | float complex type

=head1 SYNOPSYS

  my $z : Complex_2f;
  $z->{re} = 1;
  $z->{im} = 2;
  
=head1 DESCRIPTION

Complex_2f is float complex type.

This module is multi numeric type.

  class Complex_2f : mulnum_t {
    has re : float;
    has im : float;
  }

=head1 FIELDS

=head2 re

  has re : float;

Real number.

=head2 im

  has im : float;

Imaginary number.
