package SPVM::Float;

1;

=head1 Name

SPVM::Float - Float Class

=head1 Usage
  
  my $float_object = Float->new(5);
  my $float_value = $float_object->value;
  $float_object->set_value(10);

=head1 Description

C<Float> is the class to hold a value of the C<float> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw float;

The value.

=head1 Class Methods

=head2 new

  static method new : Float ($value : float);

Creates a new L<Float|SPVM::Float> object with a C<float> $value.

=head1 Copyright & License

Copyright 2023 Yuki Kimoto. All Rights Reserved.

MIT License.
