package SPVM::Float;

1;

=head1 NAME

SPVM::Float - Float object

=head1 SYNOPSYS

  my $float_object = SPVM::Float->new(0.25);
  my $float_value = $float_object->val;

=head1 DESCRIPTION

Float object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Float ($value : float)

Create L<SPVM::Float> object with specified C<float> value.

=head1 METHODS

=head2 val

  sub val : float ($self : self)

Get C<float> value.
