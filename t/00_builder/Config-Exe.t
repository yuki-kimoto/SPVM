use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config::Exe;

{
  my $config_global = SPVM::Builder::Config::Exe->new;
  isa_ok($config_global, 'SPVM::Builder::Config');
  is(ref $config_global, 'SPVM::Builder::Config::Exe');
}

done_testing;
