package SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

sub to_string {
  my $binary = SPVM::ExchangeAPI::to_binary(@_);
  
  my $string = decode('UTF-8', $binary);
  
  return $string;
}

sub new_byte_array_from_string {
  my ($env, $string) = @_;
  
  my $binary = encode('UTF-8', $string);
  
  return SPVM::ExchangeAPI::new_byte_array_from_binary($env, $binary);
}

sub new_string {
  my ($env, $string) = @_;
  
  my $binary = encode('UTF-8', $string);

  return SPVM::ExchangeAPI::new_string_from_binary($env, $binary);
}

# other functions is implemented in SPVM.xs

1;

=head1 NAME

SPVM::ExchangeAPI - Base class of Exchange API

