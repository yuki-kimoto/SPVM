package SPVM::Float;

1;

=head1 Name

SPVM::Float - A float value as An Object

=head1 Description

The Float class in L<SPVM> represents a float value as an object.

=head1 Usage
  
  my $float_object = Float->new(5);
  my $float_value = $float_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Fields

=head2 value

C<has value : ro float;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Float|SPVM::Float> ($value : float);>

Creates a new L<Float|SPVM::Float> object with a C<float> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
