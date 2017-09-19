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
