package SPVM::Object::Package::String;

use base 'SPVM::Object::Package';

use Encode 'decode';

sub to_string {
  my $self = shift;
  
  my $data = $self->to_data;
  
  my $string = decode('UTF-8', $data);
  
  return $string;
}

1;

=head1 NAME

SPVM::Object::Package::String - String Object

=head1 METHODS

Method List:

=over 2

=item * new

=item * to_data

=item * to_string

=back

If you know Method Detail, see L<SPVM::Document::Function>.

