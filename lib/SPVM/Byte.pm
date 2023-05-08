package SPVM::Byte;

1;

=head1 Name

SPVM::Byte - The byte Object

=head1 Description

The Byte class has methods to manipulate an object that has a byte value.

This class is immutable.

This class is automatically loaded.

=head1 Usage
  
  my $byte_object = Byte->new(5);
  my $byte_value = $byte_object->value;

=head1 Fields

=head2 value

  has value : ro byte;

The value.

=head1 Class Methods

=head2 new

  static method new : Byte ($value : int);

Creates a new L<Byte|SPVM::Byte> object with a C<byte> $value.

=head1 See Also

=over 2

=item * L<Mutable::Byte|SPVM::Mutable::Byte> - Mutable Byte Object

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
