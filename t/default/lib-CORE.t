use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM;

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::CoreFunc::Basic';
use SPVM 'TestCase::CoreFunc::Math';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(TestCase::CoreFunc::Math->test_join());

# Copy
{
  ok(TestCase::CoreFunc::Basic->test_copy_string());
  ok(TestCase::CoreFunc::Basic->test_copy_byte_array());
  ok(TestCase::CoreFunc::Basic->test_copy_short_array());
  ok(TestCase::CoreFunc::Basic->test_copy_int_array());
  ok(TestCase::CoreFunc::Basic->test_copy_long_array());
  ok(TestCase::CoreFunc::Basic->test_copy_float_array());
  ok(TestCase::CoreFunc::Basic->test_copy_float_array());
  ok(TestCase::CoreFunc::Basic->test_copy_object_array());
}

# Constant integral functions
{
  is(SPVM::CORE->INT8_MAX, 127);
  is(SPVM::CORE->INT8_MIN, -128);
  is(SPVM::CORE->INT16_MAX, 32767);
  is(SPVM::CORE->INT16_MIN, -32768);
  is(SPVM::CORE->INT32_MAX, 2147483647);
  is(SPVM::CORE->INT32_MIN, -2147483648);
  is(SPVM::CORE->INT64_MAX, 9223372036854775807);
  is(SPVM::CORE->INT64_MIN, -9223372036854775808);
}

# Constant floating point number functions
{
  is(SPVM::CORE->FLT_MAX, POSIX::FLT_MAX());
  is(SPVM::CORE->FLT_MIN, POSIX::FLT_MIN());
  is(SPVM::CORE->DBL_MAX, POSIX::DBL_MAX());
  is(SPVM::CORE->DBL_MIN, POSIX::DBL_MIN());
}

# Call subroutine
{
  ok(TestCase::CoreFunc::Math->test_sin());
  ok(TestCase::CoreFunc::Math->test_cos());
  ok(TestCase::CoreFunc::Math->test_tan());
}

# float
{
  ok(TestCase::CoreFunc::Math->test_float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::CoreFunc::Math->test_float_pass_nan($NaN));
  
  ok(TestCase::CoreFunc::Math->test_isinff());
  ok(TestCase::CoreFunc::Math->test_isfinitef());
  ok(TestCase::CoreFunc::Math->test_isnanf());
  
  is(SPVM::CORE->INFINITYF(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NANF(), $nan_re);
}

# SPVM::Double
{
  ok(TestCase::CoreFunc::Math->test_double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::CoreFunc::Math->test_double_pass_nan($NaN));
  
  ok(TestCase::CoreFunc::Math->test_isinf());
  ok(TestCase::CoreFunc::Math->test_isfinite());
  ok(TestCase::CoreFunc::Math->test_isnan());
  
  is(SPVM::CORE->INFINITY(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NAN(), $nan_re);
}

{
  ok(TestCase::CoreFunc::Math->test_byte_constant());
  ok(TestCase::CoreFunc::Math->test_short_constant());
  ok(TestCase::CoreFunc::Math->test_int_constant());
}

{
  is(SPVM::CORE->INT8_MAX, $BYTE_MAX);
  is(SPVM::CORE->INT8_MIN, $BYTE_MIN);
  is(SPVM::CORE->INT16_MAX, $SHORT_MAX);
  is(SPVM::CORE->INT16_MIN, $SHORT_MIN);
  is(SPVM::CORE->INT32_MAX, $INT_MAX);
  is(SPVM::CORE->INT32_MIN, $INT_MIN);
  is(SPVM::CORE->INT64_MAX, $LONG_MAX);
  is(SPVM::CORE->INT64_MIN, $LONG_MIN);
}
{
  # Check not Inf or NaN in Perl value
  like(SPVM::CORE->FLT_MAX(), qr/[0-9]/);
  like(SPVM::CORE->FLT_MIN(), qr/[0-9]/);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
