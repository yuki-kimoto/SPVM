use strict;
use warnings;

use Test::More;

use SPVM::Builder::LinkInfo;

{
  my $object_file = SPVM::Builder::LinkInfo->new;
  is(ref $object_file, 'SPVM::Builder::LinkInfo');
  
  $object_file->config("test");
  is($object_file->config(), "test");
  
  $object_file->object_files("test");
  is($object_file->object_files(), "test");
  
  $object_file->output_file("test");
  is($object_file->output_file(), "test");
}

done_testing;
