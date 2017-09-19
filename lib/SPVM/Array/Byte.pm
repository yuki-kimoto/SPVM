package SPVM::Array::Byte;

use base 'SPVM::Array';

use Encode 'decode';

sub to_string {
  my $self = shift;
  
  my $string = $self->to_data;
  
  $string = decode('UTF-8', $string);
  
  return $string;
}

1;
