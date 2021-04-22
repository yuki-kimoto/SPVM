package SPVM::Int;

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Int - Int object

=head1 SYNOPSYS

  use SPVM::Int;

  my $int_object = SPVM::Int->new(5);
  my $int_value = $int_object->value;

=head1 DESCRIPTION

L<SPVM::Int> object stores a C<int> value.

This object is immutable.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Int ($value : int)

Create a new L<SPVM::Int> object with specific C<int> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : int ($self : self)

Get a C<int> value.
