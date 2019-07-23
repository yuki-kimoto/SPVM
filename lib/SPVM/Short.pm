package SPVM::Short;

use SPVM 'SPVM::Short';

1;

# Check document 2019/07/23 almost ok.

=head1 NAME

SPVM::Short - Short object

=head1 SYNOPSYS
  
  use SPVM::Short;
  
  my $short_object = SPVM::Short->new(5);
  my $short_value = $short_object->val;

=head1 DESCRIPTION

L<SPVM::Short> object stores a C<short> value.

This object is immutable.

=head1 CLASS METHODS

=head2 new

  sub new : SPVM::Short ($value : short)

Create a new L<SPVM::Short> object with specific C<short> value.

=head1 INSTANCE METHODS

=head2 val

  sub val : short ($self : self)

Get a C<short> value.
