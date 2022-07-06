package SPVM::Byte;

1;

=head1 Name

SPVM::Byte - Byte object

=head1 Usage
  
  use Byte;
  
  my $byte_object = Byte->new(5);
  my $byte_value = $byte_object->value;

=head1 Description

L<Byte|SPVM::Byte> object holds a byte type value.

This object is immutable and its value cannot be changed.

L<Byte|SPVM::Byte> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 new

  static method new : Byte ($value : byte)

Create a new L<Byte|SPVM::Byte> object with a C<byte> value.

=head1 Instance Methods

=head2 value

  method value : byte ()

Get a C<byte> value.
