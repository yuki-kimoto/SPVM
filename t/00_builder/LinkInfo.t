use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config;
use SPVM::Builder::LinkInfo;

{
  my $config = SPVM::Builder::Config->new;
  
  my $object_file_info = SPVM::Builder::LinkInfo->new(config => $config);
  
  is(ref $object_file_info, 'SPVM::Builder::LinkInfo');
  
  $object_file_info->config("test");
  is($object_file_info->config(), "test");
  
  $object_file_info->object_file_infos("test");
  is($object_file_info->object_file_infos(), "test");
}

done_testing;
