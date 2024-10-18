use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Field';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Field access
{
  ok(SPVM::TestCase::Operator::Field->get_and_set_field_same_name_as_keyword);
  ok(SPVM::TestCase::Operator::Field->get_field_chain);
  ok(SPVM::TestCase::Operator::Field->core_func_name_field_name);
  ok(SPVM::TestCase::Operator::Field->object_field_set_and_get);
  ok(SPVM::TestCase::Operator::Field->object_field_set_and_get);
  ok(SPVM::TestCase::Operator::Field->object_field_set_and_get_again);
  ok(SPVM::TestCase::Operator::Field->object_field_initialized_zero);
  ok(SPVM::TestCase::Operator::Field->exception);
}

# All objects are freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
