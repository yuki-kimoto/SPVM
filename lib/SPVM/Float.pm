package SPVM::Float;

use SPVM 'SPVM::Float';

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Float - Float object

=head1 SYNOPSYS

  use SPVM::Float;

  my $float_object = SPVM::Float->new(0.25f);
  my $float_value = $float_object->val;

=head1 DESCRIPTION

L<SPVM::Float> object stores a C<float> value.

This object is immutable.

=head1 CLASS METHODS

=head2 new

  sub new : SPVM::Float ($value : float)

Create a new L<SPVM::Float> object with specific C<float> value.

=head1 INSTANCE METHODS

=head2 val

  sub val : float ($self : self)

Get a C<float> value.
