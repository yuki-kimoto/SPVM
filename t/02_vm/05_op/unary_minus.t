use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::UnaryMinus';

use SPVM 'TestCase::Operator::NumericOperator';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Unary minus
{
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_byte);
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_short);
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_int);
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_long);
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_float);
  ok(SPVM::TestCase::Operator::UnaryMinus->unary_minus_double);
}

# Extra
{
  ok(SPVM::TestCase::Operator::NumericOperator->plus());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
