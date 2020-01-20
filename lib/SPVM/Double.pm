package SPVM::Double;

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Double - Double object

=head1 SYNOPSYS

  use SPVM::Double;
  
  my $double_object = SPVM::Double->new(0.25);
  my $double_value = $double_object->val;

=head1 DESCRIPTION

L<SPVM::Double> object stores a C<double> value.

This object is immutable.

=head1 CLASS METHODS

=head2 new

  sub new : SPVM::Double ($value : double)

Create a new L<SPVM::Double> object with specific C<double> value.

=head1 INSTANCE METHODS

=head2 val

  sub val : double ($self : self)

Get a C<double> value.
