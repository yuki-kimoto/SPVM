package SPVM::Byte;

1;

=head1 Name

SPVM::Byte - A byte Value as An Object

=head1 Description

The Byte class in L<SPVM> represents a byte value as an object.

=head1 Usage
  
  my $byte_object = Byte->new(5);
  my $byte_value = $byte_object->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

=head1 Fields

=head2 value

C<has value : ro byte;>

The value.

=head1 Class Methods

=head2 new

C<static method new : L<Byte|SPVM::Byte> ($value : int);>

Creates a new L<Byte|SPVM::Byte> object with a C<byte> $value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
