use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::MethodCall';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Module::Native::MethodCall->new_class_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->new_instance_method_static);
  ok(SPVM::TestCase::Module::Native::MethodCall->new_instance_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->call);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_class_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_instance_method_static);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_instance_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->new_proto);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
