package SPVM::Object::Array::Byte;

use base 'SPVM::Object::Array';

use Encode 'decode';

sub to_string {
  my $self = shift;
  
  my $data = $self->to_data;
  
  my $string = decode('UTF-8', $data);
  
  return $string;
}

1;

=head1 NAME

SPVM::Object::Array::Byte - Byte Array Object

=head1 METHODS

Method List:

=over 2

=item * new_len

=item * set_elements

=item * set_elements_range

=item * set_data

=item * set_data_range

=item * set_string

=item * set

=item * get

=item * to_array

=item * to_array_range

=item * to_data

=item * to_data_range

=item * to_string

=back

If you know Method Detail, see L<SPVM::Document::Function>.

