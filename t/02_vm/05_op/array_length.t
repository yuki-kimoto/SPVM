use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::ArrayLength';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Array length
{
  ok(SPVM::TestCase::Operator::ArrayLength->array_length_atmark());
  ok(SPVM::TestCase::Operator::ArrayLength->array_length_atmark_brace());
  ok(SPVM::TestCase::Operator::ArrayLength->array_length_scalar_atmark());
  ok(SPVM::TestCase::Operator::ArrayLength->array_length_scalar_atmark_brace());
  ok(SPVM::TestCase::Operator::ArrayLength->array_length_undef());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
