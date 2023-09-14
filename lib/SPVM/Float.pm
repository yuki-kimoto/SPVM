package SPVM::Float;

1;

=head1 Name

SPVM::Float - The float Object

=head1 Description

The Float class has methods to manipulate an object that has a float value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $float_object = Float->new(5);
  my $float_value = $float_object->value;

=head1 Fields

=head2 value

  has value : ro float;

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Float|SPVM::Float> ($value : float);>

Creates a new L<Float|SPVM::Float> object with a C<float> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
