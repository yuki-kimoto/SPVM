package SPVM::Int;

1;

=head1 NAME

SPVM::Int - Int object

=head1 SYNOPSYS

  my $int_object = SPVM::Int->new(5);
  my $int_value = $int_object->val;

=head1 DESCRIPTION

Int object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Int ($value : int)

Create L<SPVM::Int> object with specified C<int> value.

=head1 METHODS

=head2 val

  sub val : int ($self : self)

Get C<int> value.
