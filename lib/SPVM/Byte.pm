package SPVM::Byte;

1;

=head1 NAME

SPVM::Byte - Byte object

=head1 SYNOPSYS
  
  use SPVM::Byte;
  
  my $byte_object = SPVM::Byte->new(5);
  my $byte_value = $byte_object->val;

=head1 DESCRIPTION

L<SPVM::Byte> object holds a byte type value.

This object is immutable and its value cannot be changed .

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Byte ($value : byte)

Create a new L<SPVM::Byte> object with specific C<byte> value.

=head1 INSTANCE METHODS

=head2 val

  sub val : byte ($self : self)

Get a C<byte> value.
