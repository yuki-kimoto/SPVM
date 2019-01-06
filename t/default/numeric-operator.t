use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::NumericOperator';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Multiply
{
  ok(TestCase::NumericOperator->multiply());

  is(TestCase::NumericOperator->multiply_int_plus(), 1073741824);
  is(TestCase::NumericOperator->multiply_int_minus(), -1073741824);
  is(TestCase::NumericOperator->multiply_int_overflow(), -2147483648);
  is(TestCase::NumericOperator->multiply_long_plus(), 4611686018427387904);
  is(TestCase::NumericOperator->multiply_long_minus(), -4611686018427387904);
  is(TestCase::NumericOperator->multiply_long_overflow(), -9223372036854775808);
}

# Divide
{
  ok(TestCase::NumericOperator->divide());
}

# Remainder
{
  ok(TestCase::NumericOperator->remainder());
}

# Plus
{
  ok(TestCase::NumericOperator->plus());
}

# Negate
{
  ok(TestCase::NumericOperator->negate());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

