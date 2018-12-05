package SPVM::Double;

1;

=head1 NAME

SPVM::Double - Double object

=head1 SYNOPSYS

  my $double_object = SPVM::Double->new(5);
  my $double_value = $double_object->val;

=head1 DESCRIPTION

Double object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Double ($value : double)

Create L<SPVM::Double> object with specified C<double> value.

=head1 METHODS

=head2 val

  sub val : double ($self : self)

Get C<double> value.
