package SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

sub to_string {
  my $bin = SPVM::ExchangeAPI::to_bin(@_);
  
  my $string = decode('UTF-8', $bin);
  
  return $string;
}

sub new_barray_from_string {
  my ($env, $string) = @_;
  
  my $bin = encode('UTF-8', $string);
  
  return SPVM::ExchangeAPI::new_barray_from_bin($env, $bin);
}

sub new_string {
  my ($env, $string) = @_;
  
  my $bin = encode('UTF-8', $string);

  return SPVM::ExchangeAPI::new_string_from_bin($env, $bin);
}

# other functions is implemented in SPVM.xs

1;

=head1 NAME

SPVM::ExchangeAPI - Base class of Exchange API

