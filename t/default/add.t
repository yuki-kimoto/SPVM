use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Add';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Spec tests
{
  # Add - Operation
  {
    ok(TestCase::Add->add_byte_byte);
    ok(TestCase::Add->add_short_short);
    ok(TestCase::Add->add_int_byte);
    ok(TestCase::Add->add_int_short);
    ok(TestCase::Add->add_byte_int);
    ok(TestCase::Add->add_short_int);
    ok(TestCase::Add->add_int_int);
    ok(TestCase::Add->add_int_float);
    ok(TestCase::Add->add_int_double);
    ok(TestCase::Add->add_overflow);
    ok(TestCase::Add->add_minus);
    ok(TestCase::Add->add_zero_minus);

    ok(TestCase::Add->add_float_nan_left);
    ok(TestCase::Add->add_float_nan_right);
    ok(TestCase::Add->add_double_nan_left);
    ok(TestCase::Add->add_double_nan_right);
    ok(TestCase::Add->add_float_plus_inf_minus_inf);
    ok(TestCase::Add->add_double_plus_inf_minus_inf);
    ok(TestCase::Add->add_float_inf_plus_value);
    ok(TestCase::Add->add_double_inf_plus_value);
    ok(TestCase::Add->add_float_minus_inf_minus_value);
    ok(TestCase::Add->add_double_minus_inf_minus_value);
    ok(TestCase::Add->add_float_plus_zero_minus_zero);
    ok(TestCase::Add->add_double_plus_zero_minus_zero);
    ok(TestCase::Add->add_float_same_sign_zero);
    ok(TestCase::Add->add_double_same_sign_zero);
    ok(TestCase::Add->add_float_over_max);
    ok(TestCase::Add->add_double_over_max);
    ok(TestCase::Add->add_float_over_min);
    ok(TestCase::Add->add_double_over_min);
  }

  # Add - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Add::LeftIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Add::RightIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(TestCase::Add->add);
  is(TestCase::Add->add_int_max(), 2147483647);
  is(TestCase::Add->add_int_min(), -2147483647);
  is(TestCase::Add->add_long_max(), 9223372036854775807);
  is(TestCase::Add->add_long_min(), -9223372036854775807);
  is(TestCase::Add->add_long_overflow(), -9223372036854775808);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

