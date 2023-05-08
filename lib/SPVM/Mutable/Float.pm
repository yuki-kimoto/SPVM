package SPVM::Mutable::Float;

1;

=head1 Name

SPVM::Mutable::Float - Mutable float Object

=head1 Description

The Mutable::Float class has methods to manipulate an object that has a float value.

This class is mutable.

=head1 Usage
  
  my $float_object = Mutable::Float->new(5);
  my $float_value = $float_object->value;
  $float_object->set_value(10);

=head1 Fields

=head2 value

  has value : rw float;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Float ($value : float);

Creates a new L<Mutable::Float|SPVM::Mutable::Float> object with a C<float> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
