package SPVM::Long;

1;

=head1 NAME

SPVM::Long - Long object

=head1 SYNOPSYS

  my $long_object = SPVM::Long->new(5L);
  my $long_value = $long_object->val;

=head1 DESCRIPTION

Long object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Long ($value : long)

Create L<SPVM::Long> object with specified C<long> value.

=head1 METHODS

=head2 val

  sub val : long ($self : self)

Get C<long> value.
