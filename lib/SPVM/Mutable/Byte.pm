package SPVM::Mutable::Byte;

1;

=head1 Name

SPVM::Mutable::Byte - Mutable byte Object

=head1 Description

The Mutable::Byte class has methods to manipulate an object that has a byte value.

This class is mutable.

=head1 Usage
  
  my $byte_object = Mutable::Byte->new(5);
  my $byte_value = $byte_object->value;
  $byte_object->set_value(10);

=head1 Fields

=head2 value

  has value : rw byte;

The value.

=head1 Class Methods

=head2 new

  static method new : Mutable::Byte ($value : int);

Creates a new L<Mutable::Byte|SPVM::Mutable::Byte> object with a C<byte> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
