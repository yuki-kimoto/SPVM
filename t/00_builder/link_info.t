use strict;
use warnings;

use Test::More;

use SPVM::Builder::LinkInfo;

{
  my $object_file = SPVM::Builder::LinkInfo->new;
  is(ref $object_file, 'SPVM::Builder::LinkInfo');
  
  $object_file->class_name("test");
  is($object_file->class_name(), "test");
  
  $object_file->config("test");
  is($object_file->config(), "test");
  
  $object_file->object_file_infos("test");
  is($object_file->object_file_infos(), "test");
  
  $object_file->output_file("test");
  is($object_file->output_file(), "test");
  
  $object_file->lib_infos("test");
  is($object_file->lib_infos(), "test");
}

done_testing;
