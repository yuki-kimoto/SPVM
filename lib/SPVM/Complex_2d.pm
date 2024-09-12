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

C<Complex_2d> is a multi-numeric type to represent a double complex number.

See L<SPVM::Document::Language::Types> about multi-numeric types.

=head1 Fields

=head2 re

  has re : double;

A real number.

=head2 im

  has im : double;

A imaginary number.

=head2 Class Methods

=head2 new

C<static method new : L<Complex_2d|SPVM::Complex_2d> ($re : double = 0, $im : double = 0);>

Creates a new L<Complex_2d|SPVM::Complex_2d> multi-numeric value given the real number $re and the imaginary number $im and returns it.

=head2 new_array_from_pairs

C<static method new_array_from_pairs : L<Complex_2d|SPVM::Complex_2d>[] ($pairs : double[]);>

Creates a new L<Complex_2d|SPVM::Complex_2d> array given the pairs of a real number and an imaginary number $pairs, and returns the new array.

Examples of Input:
  
  # Input Data
  [1, 2, 3, 4]
  
  # Data of a new array
  [{re => 1, im => 2}, {re => 3, im => 4}]

=head2 new_array_from_re_array

C<static method new_array_from_re_array : L<Complex_2d|SPVM::Complex_2d>[] ($re_array : double[]);>

Creates a new L<Complex_2d|SPVM::Complex_2d> array given real numbers $re_array, and returns the new array.

=head2 new_array_from_im_array

C<static method new_array_from_im_array : L<Complex_2d|SPVM::Complex_2d>[] ($im_array : double[]);>

Creates a new L<Complex_2d|SPVM::Complex_2d> array given imaginary numbers $im_array, and returns the new array.

=head2 to_re_array

C<static method to_re_array : double[] ($array : L<Complex_2d|SPVM::Complex_2d>[]);>

Converts the L<Complex_2d|SPVM::Complex_2d> array $array to the array of real numbers, and returns it.

=head2 to_im_array

C<static method to_im_array : double[] ($array : L<Complex_2d|SPVM::Complex_2d>[]);>

Converts the L<Complex_2d|SPVM::Complex_2d> array $array to the array of imaginary numbers, and returns it.

=head2 to_pairs

C<static method to_pairs : double[] ($array : L<Complex_2d|SPVM::Complex_2d>[]);>

Converts the L<Complex_2d|SPVM::Complex_2d> array $array to the pairs of a real number and an imaginary number, and returns it.

Examples of Output:
  
  # Input Data
  [{re => 1, im => 2}, {re => 3, im => 4}]
  
  # Output
  [1, 2, 3, 4]

=head2 to_string

C<static method to_string : string ($z : L<Complex_2d|SPVM::Complex_2d>);>

Converts the L<Complex_2d|SPVM::Complex_2d> multi-numeric value to a string, such as C<1+2i>.

Implementation:

  my $string = (string)undef;
  if ($z->{im} < 0) {
    $string = "$z->{re}$z->{im}i";
  }
  else {
    $string = "$z->{re}+$z->{im}i";
  }

=head1 See Also

=over 2

=item * L<Complex_2f|SPVM::Complex_2f>

=item * L<SPVM::Document::Language::Types>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
