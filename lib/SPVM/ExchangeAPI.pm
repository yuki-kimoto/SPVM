package SPVM::ExchangeAPI;

use Encode 'decode';

sub to_string {
  my $binary = SPVM::ExchangeAPI::to_binary(@_);
  
  my $string = decode('UTF-8', $binary);
  
  return $string;
}

# other functions is implemented in SPVM.xs

1;

=head1 NAME

SPVM::ExchangeAPI - Base class of Exchange API

