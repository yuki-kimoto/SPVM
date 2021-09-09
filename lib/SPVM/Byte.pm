package SPVM::Byte;

1;

=head1 NAME

SPVM::Byte - Byte object

=head1 SYNOPSYS
  
  use SPVM::Byte;
  
  my $byte_object = SPVM::Byte->new(5);
  my $byte_value = $byte_object->value;

=head1 DESCRIPTION

L<Byte|SPVM::Byte> object holds a byte type value.

This object is immutable and its value cannot be changed.

L<Byte|SPVM::Byte> is automatically loaded just after the program starts.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Byte ($value : byte)

Create a new L<Byte|SPVM::Byte> object with a C<byte> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : byte ($self : self)

Get a C<byte> value.
