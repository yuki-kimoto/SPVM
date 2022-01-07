use strict;
use warnings;

use Test::More 'no_plan';

use SPVM::Builder::Config;

{
  my $config = SPVM::Builder::Config->new;
  is(ref $config, 'SPVM::Builder::Config');
}

# cc
{
  my $config = SPVM::Builder::Config->new;
  $config->cc('cc_foo');
  is($config->cc, 'cc_foo');
}

# ld
{
  my $config = SPVM::Builder::Config->new;
  $config->ld('ld_foo');
  is($config->ld, 'ld_foo');
}

# resources
{
  my $config = SPVM::Builder::Config->new;
  $config->resources(['SPVM::Resource::X1', 'SPVM::Resource::X2']);
  is_deeply($config->resources, ['SPVM::Resource::X1', 'SPVM::Resource::X2']);
}

# add_resources
{
  my $config = SPVM::Builder::Config->new;
  $config->add_resources('SPVM::Resource::X1', 'SPVM::Resource::X2');
  is_deeply($config->resources, ['SPVM::Resource::X1', 'SPVM::Resource::X2']);
}

# use
{
  my $config = SPVM::Builder::Config->new;
  $config->use('SPVM::Resource::X1', 'SPVM::Resource::X2');
  is_deeply($config->resources, ['SPVM::Resource::X1', 'SPVM::Resource::X2']);
}
