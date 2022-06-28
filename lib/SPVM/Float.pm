package SPVM::Float;

1;

=head1 Name

SPVM::Float - Float object

=head1 Synopsys

  use Float;

  my $float_object = Float->new(0.25f);
  my $float_value = $float_object->value;

=head1 Description

L<Float|SPVM::Float> object stores a C<float> value.

This object is immutable and its value cannot be changed.

L<Float|SPVM::Float> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 new

  static method new : Float ($value : float)

Create a new L<Float|SPVM::Float> object with a C<float> value.

=head1 Instance Methods

=head2 value

  method value : float ()

Get a C<float> value.
