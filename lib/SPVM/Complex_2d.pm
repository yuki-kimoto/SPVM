=head1 Name

SPVM::Complex_2d - double Complex Type

=head1 Usage

  my $z : Complex_2d;
  $z->{re} = 1;
  $z->{im} = 2;
  
=head1 Description

C<Complex_2d> is a multi-numeric type to represent the double complex type.

=head1 Fields

=head2 re

  has re : double;

Real number.

=head2 im

  has im : double;

Imaginary number.
