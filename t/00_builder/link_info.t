use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config;
use SPVM::Builder::LinkInfo;

{
  my $config = SPVM::Builder::Config->new(file => __FILE__);
  
  my $object_file = SPVM::Builder::LinkInfo->new(config => $config);
  
  is(ref $object_file, 'SPVM::Builder::LinkInfo');
  
  $object_file->config("test");
  is($object_file->config(), "test");
  
  $object_file->object_files("test");
  is($object_file->object_files(), "test");
}

done_testing;
