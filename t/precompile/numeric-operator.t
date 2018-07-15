use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::NumericOperator';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Add
{
  ok(TestCase::NumericOperator->add());

  is(TestCase::NumericOperator->add_int_max(), 2147483647);
  is(TestCase::NumericOperator->add_int_min(), -2147483647);
  is(TestCase::NumericOperator->add_int_overflow(), -2147483648);
  is(TestCase::NumericOperator->add_long_max(), 9223372036854775807);
  is(TestCase::NumericOperator->add_long_min(), -9223372036854775807);
  is(TestCase::NumericOperator->add_long_overflow(), -9223372036854775808);
}

# Subtract
{
  ok(TestCase::NumericOperator->subtract());

  is(TestCase::NumericOperator->subtract_int_max(), 2147483646);
  is(TestCase::NumericOperator->subtract_int_min(), -2147483648);
  is(TestCase::NumericOperator->subtract_int_underflow(), 2147483647);
  is(TestCase::NumericOperator->subtract_long_max(), 9223372036854775806);
  is(TestCase::NumericOperator->subtract_long_min(), -9223372036854775808);
  is(TestCase::NumericOperator->subtract_long_underflow(), 9223372036854775807);
}

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
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

