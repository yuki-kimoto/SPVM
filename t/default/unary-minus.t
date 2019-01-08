use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::UnaryMinus';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Spec tests
{
  # Unary minus - Operation
  {
    ok(TestCase::UnaryMinus->unary_minus_byte);
    ok(TestCase::UnaryMinus->unary_minus_short);
    ok(TestCase::UnaryMinus->unary_minus_int);
    ok(TestCase::UnaryMinus->unary_minus_long);
    ok(TestCase::UnaryMinus->unary_minus_float);
    ok(TestCase::UnaryMinus->unary_minus_float_inf);
    ok(TestCase::UnaryMinus->unary_minus_float_zero);
    ok(TestCase::UnaryMinus->unary_minus_float_nan);
    ok(TestCase::UnaryMinus->unary_minus_double);
  }

  # Unary minus - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::UnaryMinus::NotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

#
# Integral type overflow is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::UnaryMinus->unary_minus_int_overflow);
  ok(TestCase::UnaryMinus->unary_minus_long_overflow);
}

#
# Nan, Inf, sign operation is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::UnaryMinus->unary_minus_double_inf);
  ok(TestCase::UnaryMinus->unary_minus_double_zero);
  ok(TestCase::UnaryMinus->unary_minus_double_nan);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
