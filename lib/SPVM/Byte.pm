package SPVM::Byte;

1;

=head1 NAME

SPVM::Byte - Byte object

=head1 SYNOPSYS

  my $byte_object = SPVM::Byte->new(5);
  my $byte_value = $byte_object->val;

=head1 DESCRIPTION

Byte object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Byte ($value : byte)

Create L<SPVM::Byte> object with specified C<byte> value.

=head1 METHODS

=head2 val

  sub val : byte ($self : self)

Get C<byte> value.
