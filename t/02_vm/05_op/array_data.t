use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Array';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Array
{
  ok(SPVM::TestCase::Operator::Array->array());
  ok(SPVM::TestCase::Operator::Array->array_store_undef());
}

# Array default
{
  ok(SPVM::TestCase::Operator::Array->array_default_zero_memory_pool());
  ok(SPVM::TestCase::Operator::Array->array_default_zero_not_memory_pool());
}

# array - culcurate sum by for
{
  my $total = SPVM::TestCase::Operator::Array->array_culcurate_sum_by_for();
  is($total, 6);
}

# any object array
{
  ok(SPVM::TestCase::Operator::Array->any_object_array);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
