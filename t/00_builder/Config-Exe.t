use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config::Exe;

{
  my $config_exe = SPVM::Builder::Config::Exe->new;
  isa_ok($config_exe, 'SPVM::Builder::Config');
  is(ref $config_exe, 'SPVM::Builder::Config::Exe');
}

done_testing;
