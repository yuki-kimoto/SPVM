package SPVM::Int;

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Int - Int object

=head1 SYNOPSYS

  use SPVM::Int;

  my $int_object = SPVM::Int->new(5);
  my $int_value = $int_object->val;

=head1 DESCRIPTION

L<SPVM::Int> object stores a C<int> value.

This object is immutable.

=head1 CLASS METHODS

=head2 new

  sub new : SPVM::Int ($value : int)

Create a new L<SPVM::Int> object with specific C<int> value.

=head1 INSTANCE METHODS

=head2 val

  sub val : int ($self : self)

Get a C<int> value.
