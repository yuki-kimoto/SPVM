package SPVM::Object::Array;

use base 'SPVM::Object';

use Encode 'decode';

sub to_string {
  my $self = shift;
  
  my $bin = $self->to_bin;
  
  my $string = decode('UTF-8', $bin);
  
  return $string;
}

1;

=head1 NAME

SPVM::Object::Array - Array object

=head1 METHODS

Method List:

=over 2

=item * new_len

=item * set_elements

=item * set_bin

=item * set_string

=item * set_element

=item * get_element

=item * to_elements

=item * to_bin

=item * to_string

=back

If you know Method Detail, see L<SPVM::Document::PerlAPI>.
