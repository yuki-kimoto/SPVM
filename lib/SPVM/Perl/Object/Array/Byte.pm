package SPVM::Perl::Object::Array::Byte;

use base 'SPVM::Perl::Object::Array';

use Encode 'decode';

sub to_string {
  my $self = shift;
  
  my $bin = $self->to_bin;
  
  my $string = decode('UTF-8', $bin);
  
  return $string;
}

1;

=head1 NAME

SPVM::Perl::Object::Array::Byte - Byte Array Object

=head1 METHODS

Method List:

=over 2

=item * new_len

=item * set_elements

=item * set_elements_range

=item * set_bin

=item * set_bin_range

=item * set_string

=item * set

=item * get

=item * to_elements

=item * to_elements_range

=item * to_bin

=item * to_bin_range

=item * to_string

=back

If you know Method Detail, see L<SPVM::Document::PerlAPI>.

