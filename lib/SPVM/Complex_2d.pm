=head1 Name

SPVM::Complex_2d - double complex type

=head1 Usage

  my $z : Complex_2d;
  $z->{re} = 1;
  $z->{im} = 2;
  
=head1 Description

Complex_2d is double complex type.

This module is multi numeric type.

  class Complex_2d : mulnum_t {
    has re : double;
    has im : double;
  }

=head1 Field Methods

=head2 re

  has re : double;

Real number.

=head2 im

  has im : double;

Imaginary number.
