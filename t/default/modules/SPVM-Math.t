use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use POSIX();
use TestFile;

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

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp_replace_newline();

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::SPVM::Math';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Call subroutine
{
  ok(TestCase::Lib::SPVM::Math->test_sin);
  ok(TestCase::Lib::SPVM::Math->test_cos);
  ok(TestCase::Lib::SPVM::Math->test_tan);
}

# float
{
  ok(TestCase::Lib::SPVM::Math->test_float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::Lib::SPVM::Math->test_float_pass_nan($NaN));
  
  ok(TestCase::Lib::SPVM::Math->test_isinff);
  ok(TestCase::Lib::SPVM::Math->test_isfinitef);
  ok(TestCase::Lib::SPVM::Math->test_isnanf);
  
  is(SPVM::Math->INFINITYF(), $POSITIVE_INFINITY);
  
  like(SPVM::Math->NANF(), $nan_re);
}

# SPVM::Double
{
  ok(TestCase::Lib::SPVM::Math->test_double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::Lib::SPVM::Math->test_double_pass_nan($NaN));
  
  ok(TestCase::Lib::SPVM::Math->test_isinf);
  ok(TestCase::Lib::SPVM::Math->test_isfinite);
  ok(TestCase::Lib::SPVM::Math->test_isnan);
  
  is(SPVM::Math->INFINITY(), $POSITIVE_INFINITY);
  
  like(SPVM::Math->NAN(), $nan_re);
}

{
  ok(TestCase::Lib::SPVM::Math->add_float_plus_inf_minus_inf);
  ok(TestCase::Lib::SPVM::Math->add_double_plus_inf_minus_inf);
  ok(TestCase::Lib::SPVM::Math->add_float_inf_plus_value);
  ok(TestCase::Lib::SPVM::Math->add_double_inf_plus_value);
  ok(TestCase::Lib::SPVM::Math->add_float_minus_inf_minus_value);
  ok(TestCase::Lib::SPVM::Math->add_double_minus_inf_minus_value);
}

{
  ok(TestCase::Lib::SPVM::Math->add_float_nan_left);
  ok(TestCase::Lib::SPVM::Math->add_float_nan_right);
  ok(TestCase::Lib::SPVM::Math->add_double_nan_left);
  ok(TestCase::Lib::SPVM::Math->add_double_nan_right);
}

#
# Integral type overflow is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  is(TestCase::Lib::SPVM::Math->add_long_overflow(), -9223372036854775808);
  ok(TestCase::Lib::SPVM::Math->add_overflow);
}

#
# Nan, Inf, sign operation is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::Lib::SPVM::Math->add_float_plus_zero_minus_zero);
  ok(TestCase::Lib::SPVM::Math->add_double_plus_zero_minus_zero);
  ok(TestCase::Lib::SPVM::Math->add_float_same_sign_zero);
  ok(TestCase::Lib::SPVM::Math->add_double_same_sign_zero);
  ok(TestCase::Lib::SPVM::Math->add_float_over_max);
  ok(TestCase::Lib::SPVM::Math->add_double_over_max);
  ok(TestCase::Lib::SPVM::Math->add_float_over_min);
  ok(TestCase::Lib::SPVM::Math->add_double_over_min);
}

#
# Integral type overflow is not defined in C99
# If in some environment, these tests fail, please comment out
#
{

  ok(TestCase::Lib::SPVM::Math->subtract_overflow);
  is(TestCase::Lib::SPVM::Math->subtract_long_underflow(), 9223372036854775807);
}

#
# Nan, Inf, sign operation is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::Lib::SPVM::Math->subtract_float_nan_left);
  ok(TestCase::Lib::SPVM::Math->subtract_float_nan_right);
  ok(TestCase::Lib::SPVM::Math->subtract_double_nan_left);
  ok(TestCase::Lib::SPVM::Math->subtract_double_nan_right);
  ok(TestCase::Lib::SPVM::Math->subtract_float_plus_inf_minus_inf);
  ok(TestCase::Lib::SPVM::Math->subtract_double_plus_inf_minus_inf);
  ok(TestCase::Lib::SPVM::Math->subtract_float_inf_plus_value);
  ok(TestCase::Lib::SPVM::Math->subtract_double_inf_plus_value);
  ok(TestCase::Lib::SPVM::Math->subtract_float_minus_inf_minus_value);
  ok(TestCase::Lib::SPVM::Math->subtract_double_minus_inf_minus_value);
  ok(TestCase::Lib::SPVM::Math->subtract_float_plus_zero_minus_zero);
  ok(TestCase::Lib::SPVM::Math->subtract_double_plus_zero_minus_zero);
  ok(TestCase::Lib::SPVM::Math->subtract_float_over_max);
  ok(TestCase::Lib::SPVM::Math->subtract_double_over_max);
  ok(TestCase::Lib::SPVM::Math->subtract_float_over_min);
  ok(TestCase::Lib::SPVM::Math->subtract_double_over_min);
}


#
# Integral type overflow is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::Lib::SPVM::Math->unary_minus_int_overflow);
  ok(TestCase::Lib::SPVM::Math->unary_minus_long_overflow);
}

#
# Nan, Inf, sign operation is not defined in C99
# If in some environment, these tests fail, please comment out
#
{
  ok(TestCase::Lib::SPVM::Math->unary_minus_double_inf);
  ok(TestCase::Lib::SPVM::Math->unary_minus_double_zero);
  ok(TestCase::Lib::SPVM::Math->unary_minus_double_nan);
  ok(TestCase::Lib::SPVM::Math->unary_minus_float_inf);
  ok(TestCase::Lib::SPVM::Math->unary_minus_float_zero);
  ok(TestCase::Lib::SPVM::Math->unary_minus_float_nan);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
