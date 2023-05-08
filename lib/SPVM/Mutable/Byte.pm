package SPVM::Mutable::Byte;

1;

=head1 Name

SPVM::Mutable::Byte - Mutable::Byte Class

=head1 Usage
  
  my $byte_object = Mutable::Byte->new(5);
  my $byte_value = $byte_object->value;
  $byte_object->set_value(10);

=head1 Description

C<Mutable::Byte> is the class to hold a value of the C<byte> type.

This class is automatically loaded.

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
