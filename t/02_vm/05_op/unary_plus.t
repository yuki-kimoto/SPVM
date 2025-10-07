use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::UnaryPlus';

use SPVM 'TestCase::Operator::NumericOperator';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Unary plus
{
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_byte);
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_short);
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_int);
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_long);
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_float);
  ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_double);
}

# Extra
{
  ok(SPVM::TestCase::Operator::NumericOperator->negate());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
