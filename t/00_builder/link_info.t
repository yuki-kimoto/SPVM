use strict;
use warnings;

use Test::More;

use SPVM::Builder::LinkInfo;

{
  my $object_file = SPVM::Builder::LinkInfo->new;
  is(ref $object_file, 'SPVM::Builder::LinkInfo');

  $object_file->output_file("test");
  is($object_file->output_file(), "test");
  
  $object_file->output_type("test");
  is($object_file->output_type(), "test");
  
  $object_file->ld_optimize("test");
  is($object_file->ld_optimize(), "test");
  
  $object_file->ldflags("test");
  is($object_file->ldflags(), "test");
  
  $object_file->dynamic_lib_ldflags("test");
  is($object_file->dynamic_lib_ldflags(), "test");
  
  $object_file->lib_dirs("test");
  is($object_file->lib_dirs(), "test");
  
  $object_file->object_file_infos("test");
  is($object_file->object_file_infos(), "test");
  
  $object_file->lib_infos("test");
  is($object_file->lib_infos(), "test");
  
  $object_file->class_name("test");
  is($object_file->class_name(), "test");
  
  $object_file->config("test");
  is($object_file->config(), "test");
}

done_testing;
