package SPVM::Float;

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Float - Float object

=head1 SYNOPSYS

  use SPVM::Float;

  my $float_object = SPVM::Float->new(0.25f);
  my $float_value = $float_object->value;

=head1 DESCRIPTION

L<SPVM::Float> object stores a C<float> value.

This object is immutable.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::Float ($value : float)

Create a new L<SPVM::Float> object with specific C<float> value.

=head1 INSTANCE METHODS

=head2 value

  sub value : float ($self : self)

Get a C<float> value.
