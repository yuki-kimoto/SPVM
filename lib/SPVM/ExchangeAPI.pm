package SPVM::ExchangeAPI;

use strict;
use warnings;

use Carp 'croak', 'confess';
use Encode 'decode';

sub new_object {
  my ($env, $package_name) = @_;
  
  my $object = SPVM::Data::Package->new($package_name);
  
  return $object;
}

1;
