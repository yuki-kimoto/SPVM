use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::FieldAccess';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Field access
{
  ok(SPVM::TestCase::Operator::FieldAccess->get_and_set_field_same_name_as_keyword);
  ok(SPVM::TestCase::Operator::FieldAccess->get_field_chain);
  ok(SPVM::TestCase::Operator::FieldAccess->core_func_name_field_name);
  ok(SPVM::TestCase::Operator::FieldAccess->object_field);
  ok(SPVM::TestCase::Operator::FieldAccess->object_field_again);
  ok(SPVM::TestCase::Operator::FieldAccess->object_field_initialized_zero);
  ok(SPVM::TestCase::Operator::FieldAccess->exception);
}

# All objects are freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
