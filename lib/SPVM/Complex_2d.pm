=head1 Name

SPVM::Complex_2d - double Complex Type

=head1 Usage
  
  use Complex_2d;
  
  my $z : Complex_2d;
  
  # Set
  $z->{re} = 1.5;
  $z->{im} = 2.5;
  
  # Get
  my $re = $z->{re};
  my $im = $z->{im};
  
=head1 Description

C<Complex_2d> is a L<multi-numeric type|SPVM::Document::Language/"Multi-Numeric Type"> to represent a double complex number.

=head1 Fields

=head2 re

  has re : double;

A real number.

=head2 im

  has im : double;

A imaginary number.

=head1 Copyright & License

Copyright 2023 Yuki Kimoto. All Rights Reserved.

MIT License.
