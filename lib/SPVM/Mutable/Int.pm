package SPVM::Mutable::Int;

1;

=head1 Name

SPVM::Mutable::Int - Mutable int Object

=head1 Description

The Mutable::Int class has methods to manipulate an object that has an int value.

This class is mutable.

=head1 Usage
  
  my $int_object = Mutable::Int->new(5);
  my $int_value = $int_object->value;
  $int_object->set_value(10);

=head1 Fields

=head2 value

  has value : rw int;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Int ($value : int);

Creates a new L<Mutable::Int|SPVM::Mutable::Int> object with a C<int> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
