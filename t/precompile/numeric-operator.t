use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::NumericOperator';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

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

use SPVM 'TestCase';

# Complement
{
  ok(TestCase->complement());
}

# Increment
{
  ok(TestCase->pre_inc());
  ok(TestCase->pre_dec());
  ok(TestCase->post_inc());
  ok(TestCase->post_dec());
}

# Bit shift left
{
  ok(TestCase->bit_shift_left_int());
  ok(TestCase->bit_shift_left_int_max());
  ok(TestCase->bit_shift_left_int_overflow());
  ok(TestCase->bit_shift_left_long());
  ok(TestCase->bit_shift_left_long_max());
  ok(TestCase->bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(TestCase->bit_shift_right_logical_int());
  ok(TestCase->bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(TestCase->bit_shift_right_int());
  ok(TestCase->bit_shift_right_long());
}

# Bit and
{
  ok(TestCase->bit_and());
}

# Bit or
{
  ok(TestCase->bit_or());
}

# Bit xor
{
  ok(TestCase->bit_xor());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

