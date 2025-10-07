use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::ArrayInit';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# [] Array initialization
{
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_empty());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_byte());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_short());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_int());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_long());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_float());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_double());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_object());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_fatcamma);
}

# {} Array initialization
{
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_key_values_empty());
  ok(SPVM::TestCase::Operator::ArrayInit->array_init_key_values());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
