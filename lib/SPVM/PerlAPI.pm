package SPVM::PerlAPI;

use strict;
use warnings;

use Carp 'croak', 'confess';
use Encode 'decode';

sub new_value_array {
  my ($env, $package_name, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_value_array_len($env, $package_name, $length);

  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_object {
  my ($env, $package_name) = @_;
  
  my $object = SPVM::Data::Package->new($package_name);
  
  return $object;
}

1;
