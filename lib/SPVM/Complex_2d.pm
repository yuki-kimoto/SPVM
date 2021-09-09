=head1 NAME

SPVM::Complex_2d - Complex_2d in SPVM | double complex type

=head1 SYNOPSYS

  my $z : Complex_2d;
  $z->{re} = 1;
  $z->{im} = 2;
  
=head1 DESCRIPTION

Complex_2d is double complex type.

This module is multi numeric type.

  class Complex_2d : mulnum_t {
    has re : double;
    has im : double;
  }

=head1 FIELDS

=head2 re

  has re : double;

Real number.

=head2 im

  has im : double;

Imaginary number.
