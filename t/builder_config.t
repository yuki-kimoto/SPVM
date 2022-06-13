use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config;

{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
  is(ref $config, 'SPVM::Builder::Config');
}

# cc
{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
  $config->cc('cc_foo');
  is($config->cc, 'cc_foo');
}

# ld
{
  my $config = SPVM::Builder::Config->new(file_optional => 1);
  $config->ld('ld_foo');
  is($config->ld, 'ld_foo');
}

done_testing;
