package SPVM::String;

use base 'SPVM::BaseObject';

use Encode 'decode';

sub get_string {
  my $self = shift;
  
  my $string = $self->get_string_bytes;
  
  $string = decode('UTF-8', $string);
  
  return $string;
}

1;

=head1 NAME

SPVM::String - SPVM string object

=head1 METHODS

=head2 get_string

Get decoded string.

  my $string = $spvm_string->get_string;

=head2 get_string_bytes

Get bytes string.

  my $bytes_string = $spvm_string->get_string_bytes;
