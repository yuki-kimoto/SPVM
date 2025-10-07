use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::New::Array';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Array
{
  ok(SPVM::TestCase::Operator::New::Array->array_store_undef);
}

# Array default
{
  ok(SPVM::TestCase::Operator::New::Array->array_default_zero_memory_pool);
  ok(SPVM::TestCase::Operator::New::Array->array_default_zero_not_memory_pool);
}

# any object array
{
  ok(SPVM::TestCase::Operator::New::Array->any_object_array);
}

ok(SPVM::TestCase::Operator::New::Array->extra);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
