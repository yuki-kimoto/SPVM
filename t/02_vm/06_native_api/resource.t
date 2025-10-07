use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::UseResource::Basic';
use SPVM 'TestCase::UseResource::Mylib1';
use SPVM 'TestCase::UseResource::Mylib2';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(SPVM::TestCase::UseResource::Basic->test);

{
  ok(SPVM::TestCase::UseResource::Mylib1->test);
  my $resource = $main::TEST_USE_RESOURCE_RET;
  is_deeply($resource->config->{_test_base_env}, ['args1', 'args2']);
  
  my $object_file = 't/02_vm/.spvm_build/work/object/SPVM/TestCase/UseResource/Basic.resource/SPVM/TestCase/Resource/Mylib1.native/mylib1_source1.o';
  ok (-f $object_file);
}

{
  ok(SPVM::TestCase::UseResource::Mylib2->test);
  my $config = $main::TEST_USE_RESOURCE_CONFIG;
  is_deeply($config->get_resource_names, ['TestCase::Resource::Mylib1', 'TestCase::Resource::Mylib2']);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
