package SPVM::Byte;

1;

=head1 Name

SPVM::Byte - Byte Class

=head1 Usage
  
  my $byte_object = Byte->new(5);
  my $byte_value = $byte_object->value;
  $byte_object->set_value(10);

=head1 Description

C<Byte> is the class to hold a value of the C<byte> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw byte;

The value.

=head1 Class Methods

=head2 new

  static method new : Byte ($value : int);

Create a new L<Byte|SPVM::Byte> object with a C<byte> value.
