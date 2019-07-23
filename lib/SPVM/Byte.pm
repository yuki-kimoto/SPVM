package SPVM::Byte;

use SPVM 'SPVM::Byte';

1;

# Check document 2019/07/03 almost ok.

=head1 NAME

SPVM::Byte - Byte object

=head1 SYNOPSYS

  my $byte_object = SPVM::Byte->new(5);
  my $byte_value = $byte_object->val;

=head1 DESCRIPTION

L<SPVM::Byte> object stores a byte value.

This object is immutable.

=head1 METHODS

=head2 new

  sub new : SPVM::Byte ($value : byte)

Create a new L<SPVM::Byte> object with specific C<byte> value.

=head2 val

  sub val : byte ($self : self)

Get C<byte> value.
