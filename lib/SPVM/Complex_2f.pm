=head1 Name

SPVM::Complex_2f - float Complex Type

=head1 Usage
  
  use Complex_2f;
  
  my $z : Complex_2f;
  
  # Set
  $z->{re} = 1.5f;
  $z->{im} = 2.5f;
  
  # Get
  my $re = $z->{re};
  my $im = $z->{im};
  
=head1 Description

C<Complex_2f> is a L<multi-numeric type|SPVM::Document::LanguageSpecification/"Multi-Numeric Type"> to represent a float complex number.

=head1 Fields

=head2 re

  has re : float;

A real number.

=head2 im

  has im : float;

A imaginary number.
