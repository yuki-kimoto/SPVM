use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Subtract';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Spec tests
{
  # Subtract - Operation
  {
    ok(TestCase::Subtract->subtract_byte_byte);
    ok(TestCase::Subtract->subtract_short_short);
    ok(TestCase::Subtract->subtract_int_byte);
    ok(TestCase::Subtract->subtract_int_short);
    ok(TestCase::Subtract->subtract_byte_int);
    ok(TestCase::Subtract->subtract_short_int);
    ok(TestCase::Subtract->subtract_int_int);
    ok(TestCase::Subtract->subtract_long_long);
    ok(TestCase::Subtract->subtract_int_float);
    ok(TestCase::Subtract->subtract_int_double);
    ok(TestCase::Subtract->subtract_minus);
    ok(TestCase::Subtract->subtract_zero_minus);
    ok(TestCase::Subtract->subtract_float_float);
    ok(TestCase::Subtract->subtract_double_double);
    ok(TestCase::Subtract->subtract_double_double_big);
  }

  # Subtract - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Subtract::LeftIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Subtract::RightIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(TestCase::Subtract->subtract());

  is(TestCase::Subtract->subtract_int_max(), 2147483646);
  is(TestCase::Subtract->subtract_int_min(), -2147483648);
  is(TestCase::Subtract->subtract_int_underflow(), 2147483647);
  is(TestCase::Subtract->subtract_long_max(), 9223372036854775806);
  is(TestCase::Subtract->subtract_long_min(), -9223372036854775808);
}

#
# Integral type overflow is not defined in C99
# If in some environment, these tests fail, please comment out
#
{

  ok(TestCase::Subtract->subtract_overflow);
  is(TestCase::Subtract->subtract_long_underflow(), 9223372036854775807);
}

#
# Nan, Inf, sign operation is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::Subtract->subtract_float_nan_left);
  ok(TestCase::Subtract->subtract_float_nan_right);
  ok(TestCase::Subtract->subtract_double_nan_left);
  ok(TestCase::Subtract->subtract_double_nan_right);
  ok(TestCase::Subtract->subtract_float_plus_inf_minus_inf);
  ok(TestCase::Subtract->subtract_double_plus_inf_minus_inf);
  ok(TestCase::Subtract->subtract_float_inf_plus_value);
  ok(TestCase::Subtract->subtract_double_inf_plus_value);
  ok(TestCase::Subtract->subtract_float_minus_inf_minus_value);
  ok(TestCase::Subtract->subtract_double_minus_inf_minus_value);
  ok(TestCase::Subtract->subtract_float_plus_zero_minus_zero);
  ok(TestCase::Subtract->subtract_double_plus_zero_minus_zero);
  ok(TestCase::Subtract->subtract_float_over_max);
  ok(TestCase::Subtract->subtract_double_over_max);
  ok(TestCase::Subtract->subtract_float_over_min);
  ok(TestCase::Subtract->subtract_double_over_min);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

