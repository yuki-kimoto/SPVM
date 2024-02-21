use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::MethodCall';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Module::Native::MethodCall->new_class_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->new_instance_method_static);
  ok(SPVM::TestCase::Module::Native::MethodCall->new_instance_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->call);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_callback);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_class_method_for_env);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_class_method);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_instance_method_static);
  ok(SPVM::TestCase::Module::Native::MethodCall->call_instance_method);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
