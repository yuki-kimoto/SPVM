use strict;
use warnings;

use Test::More;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Builder::Config;
use SPVM::MyClass::ConfigBuilder;

{
  my $config_builder = SPVM::MyClass::ConfigBuilder->new(x => 1);
  
  is(ref $config_builder, 'SPVM::MyClass::ConfigBuilder');
  
  my $config = SPVM::Builder::Config->new;
  
  $config_builder->build_config($config);
  
  is_deeply($config->ccflags, ['foo']);
}

done_testing;
