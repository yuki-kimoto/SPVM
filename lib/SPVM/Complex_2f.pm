=head1 Name

SPVM::Complex_2f - float Complex Type

=head1 Usage
  
  use Complex_2f;
  
  my $z : Complex_2f;
  
  # Set
  $z->{re} = 1.5;
  $z->{im} = 2.5;
  
  # Get
  my $re = $z->{re};
  my $im = $z->{im};

=head1 Description

C<Complex_2f> is a multi-numeric type to represent a float complex number.

See L<SPVM::Document::Language::Types> about multi-numeric types.

=head1 Fields

=head2 re

  has re : float;

A real number.

=head2 im

  has im : float;

A imaginary number.

=head2 Class Methods

=head2 new

C<static method new : L<Complex_2f|SPVM::Complex_2f> ($re : float = 0, $im : float = 0);>

Creates a new L<Complex_2f|SPVM::Complex_2f> multi-numeric value given the real number $re and the imaginary number $im and returns it.

=head2 new_array_from_pairs

C<static method new_array_from_pairs : L<Complex_2f|SPVM::Complex_2f>[] ($pairs : float[]);>

Creates a new L<Complex_2f|SPVM::Complex_2f> array given the pairs of a real number and an imaginary number $pairs, and returns the new array.

Examples of Input:
  
  # Input Data
  [1, 2, 3, 4]
  
  # Data of a new array
  [{re => 1, im => 2}, {re => 3, im => 4}]

=head2 new_array_from_re_array

C<static method new_array_from_re_array : L<Complex_2f|SPVM::Complex_2f>[] ($re_array : float[]);>

Creates a new L<Complex_2f|SPVM::Complex_2f> array given real numbers $re_array, and returns the new array.

=head2 new_array_from_im_array

C<static method new_array_from_im_array : L<Complex_2f|SPVM::Complex_2f>[] ($im_array : float[]);>

Creates a new L<Complex_2f|SPVM::Complex_2f> array given imaginary numbers $im_array, and returns the new array.

=head2 to_re_array

C<static method to_re_array : float[] ($array : L<Complex_2f|SPVM::Complex_2f>[]);>

Converts the L<Complex_2f|SPVM::Complex_2f> array $array to the array of real numbers, and returns it.

=head2 to_im_array

C<static method to_im_array : float[] ($array : L<Complex_2f|SPVM::Complex_2f>[]);>

Converts the L<Complex_2f|SPVM::Complex_2f> array $array to the array of imaginary numbers, and returns it.

=head2 to_pairs

C<static method to_pairs : float[] ($array : L<Complex_2f|SPVM::Complex_2f>[]);>

Converts the L<Complex_2f|SPVM::Complex_2f> array $array to the pairs of a real number and an imaginary number, and returns it.

Examples of Output:
  
  # Input Data
  [{re => 1, im => 2}, {re => 3, im => 4}]
  
  # Output
  [1, 2, 3, 4]

=head2 to_string

C<static method to_string : string ($z : L<Complex_2f|SPVM::Complex_2f>);>

Converts the L<Complex_2f|SPVM::Complex_2f> multi-numeric value to a string, such as C<1+2i>.

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

=item * L<Complex_2d|SPVM::Complex_2d>

=item * L<SPVM::Document::Language::Types>

=back


=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
