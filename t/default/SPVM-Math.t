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
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(TestCase::Lib::SPVM::Math->test_pi);

# Trigonometric functions
ok(TestCase::Lib::SPVM::Math->test_cos);
ok(TestCase::Lib::SPVM::Math->test_cosf);
ok(TestCase::Lib::SPVM::Math->test_sin);
ok(TestCase::Lib::SPVM::Math->test_sinf);
ok(TestCase::Lib::SPVM::Math->test_tan);
ok(TestCase::Lib::SPVM::Math->test_tanf);
ok(TestCase::Lib::SPVM::Math->test_acos);
ok(TestCase::Lib::SPVM::Math->test_acosf);
ok(TestCase::Lib::SPVM::Math->test_asin);
ok(TestCase::Lib::SPVM::Math->test_asinf);
ok(TestCase::Lib::SPVM::Math->test_atan);
ok(TestCase::Lib::SPVM::Math->test_atanf);

# Hyperbolic functions
ok(TestCase::Lib::SPVM::Math->test_cosh);
ok(TestCase::Lib::SPVM::Math->test_coshf);
ok(TestCase::Lib::SPVM::Math->test_sinh);
ok(TestCase::Lib::SPVM::Math->test_sinhf);
ok(TestCase::Lib::SPVM::Math->test_tanh);
ok(TestCase::Lib::SPVM::Math->test_tanhf);
ok(TestCase::Lib::SPVM::Math->test_acosh);
ok(TestCase::Lib::SPVM::Math->test_acoshf);
ok(TestCase::Lib::SPVM::Math->test_asinh);
ok(TestCase::Lib::SPVM::Math->test_asinhf);
ok(TestCase::Lib::SPVM::Math->test_atanh);
ok(TestCase::Lib::SPVM::Math->test_atanhf);

# Exponential and logarithmic functions
ok(TestCase::Lib::SPVM::Math->test_exp);
ok(TestCase::Lib::SPVM::Math->test_expf);
ok(TestCase::Lib::SPVM::Math->test_exp2);
ok(TestCase::Lib::SPVM::Math->test_exp2f);
ok(TestCase::Lib::SPVM::Math->test_expm1);
ok(TestCase::Lib::SPVM::Math->test_expm1f);
ok(TestCase::Lib::SPVM::Math->test_frexp);
ok(TestCase::Lib::SPVM::Math->test_frexpf);
ok(TestCase::Lib::SPVM::Math->test_ilogb);
ok(TestCase::Lib::SPVM::Math->test_ilogbf);
ok(TestCase::Lib::SPVM::Math->test_ldexp);
ok(TestCase::Lib::SPVM::Math->test_ldexpf);
ok(TestCase::Lib::SPVM::Math->test_log);
ok(TestCase::Lib::SPVM::Math->test_logf);
ok(TestCase::Lib::SPVM::Math->test_log10);
ok(TestCase::Lib::SPVM::Math->test_log10f);
ok(TestCase::Lib::SPVM::Math->test_log1p);
ok(TestCase::Lib::SPVM::Math->test_log1pf);
ok(TestCase::Lib::SPVM::Math->test_log2);
ok(TestCase::Lib::SPVM::Math->test_log2f);
ok(TestCase::Lib::SPVM::Math->test_logb);
ok(TestCase::Lib::SPVM::Math->test_logbf);
ok(TestCase::Lib::SPVM::Math->test_modf);
ok(TestCase::Lib::SPVM::Math->test_modff);
ok(TestCase::Lib::SPVM::Math->test_scalbn);
ok(TestCase::Lib::SPVM::Math->test_scalbnf);
ok(TestCase::Lib::SPVM::Math->test_scalbln);
ok(TestCase::Lib::SPVM::Math->test_scalblnf);

# Power function and absolute value functions
ok(TestCase::Lib::SPVM::Math->test_cbrt);
ok(TestCase::Lib::SPVM::Math->test_cbrtf);
ok(TestCase::Lib::SPVM::Math->test_fabs);
ok(TestCase::Lib::SPVM::Math->test_fabsf);
ok(TestCase::Lib::SPVM::Math->test_hypot);
ok(TestCase::Lib::SPVM::Math->test_hypotf);
ok(TestCase::Lib::SPVM::Math->test_pow);
ok(TestCase::Lib::SPVM::Math->test_powf);
ok(TestCase::Lib::SPVM::Math->test_sqrt);
ok(TestCase::Lib::SPVM::Math->test_sqrtf);

# Error function and gamma functions
ok(TestCase::Lib::SPVM::Math->test_erf);
ok(TestCase::Lib::SPVM::Math->test_erff);
ok(TestCase::Lib::SPVM::Math->test_erfc);
ok(TestCase::Lib::SPVM::Math->test_erfcf);
ok(TestCase::Lib::SPVM::Math->test_lgamma);
ok(TestCase::Lib::SPVM::Math->test_lgammaf);
ok(TestCase::Lib::SPVM::Math->test_tgamma);
ok(TestCase::Lib::SPVM::Math->test_tgammaf);

# Nearest integer functions
ok(TestCase::Lib::SPVM::Math->test_ceil);
ok(TestCase::Lib::SPVM::Math->test_ceilf);
ok(TestCase::Lib::SPVM::Math->test_floor);
ok(TestCase::Lib::SPVM::Math->test_floorf);
ok(TestCase::Lib::SPVM::Math->test_nearbyint);
ok(TestCase::Lib::SPVM::Math->test_nearbyintf);
ok(TestCase::Lib::SPVM::Math->test_round);
ok(TestCase::Lib::SPVM::Math->test_roundf);
ok(TestCase::Lib::SPVM::Math->test_lround);
ok(TestCase::Lib::SPVM::Math->test_lroundf);
ok(TestCase::Lib::SPVM::Math->test_trunc);
ok(TestCase::Lib::SPVM::Math->test_truncf);

# Surplus functions
ok(TestCase::Lib::SPVM::Math->test_fmod);
ok(TestCase::Lib::SPVM::Math->test_fmodf);
ok(TestCase::Lib::SPVM::Math->test_remainder);
ok(TestCase::Lib::SPVM::Math->test_remainderf);
ok(TestCase::Lib::SPVM::Math->test_remquo);
ok(TestCase::Lib::SPVM::Math->test_remquof);

# Real number operation functions
ok(TestCase::Lib::SPVM::Math->test_copysign);
ok(TestCase::Lib::SPVM::Math->test_copysignf);
ok(TestCase::Lib::SPVM::Math->test_nan);
ok(TestCase::Lib::SPVM::Math->test_nanf);
ok(TestCase::Lib::SPVM::Math->test_nextafter);
ok(TestCase::Lib::SPVM::Math->test_nextafterf);
ok(TestCase::Lib::SPVM::Math->test_nexttoward);
ok(TestCase::Lib::SPVM::Math->test_nexttowardf);

# Maximum, minimum and positive difference functions
ok(TestCase::Lib::SPVM::Math->test_fdim);
ok(TestCase::Lib::SPVM::Math->test_fdimf);
ok(TestCase::Lib::SPVM::Math->test_fmax);
ok(TestCase::Lib::SPVM::Math->test_fmaxf);
ok(TestCase::Lib::SPVM::Math->test_fmin);
ok(TestCase::Lib::SPVM::Math->test_fminf);

# Floating point multiplication and additions
ok(TestCase::Lib::SPVM::Math->test_fma);
ok(TestCase::Lib::SPVM::Math->test_fmaf);

# Classification
ok(TestCase::Lib::SPVM::Math->test_fpclassify);
ok(TestCase::Lib::SPVM::Math->test_fpclassifyf);
ok(TestCase::Lib::SPVM::Math->test_isfinite);
ok(TestCase::Lib::SPVM::Math->test_isfinitef);
ok(TestCase::Lib::SPVM::Math->test_isinf);
ok(TestCase::Lib::SPVM::Math->test_isinff);
ok(TestCase::Lib::SPVM::Math->test_isnan);
ok(TestCase::Lib::SPVM::Math->test_isnanf);
ok(TestCase::Lib::SPVM::Math->test_signbit);
ok(TestCase::Lib::SPVM::Math->test_signbitf);

# Comparison
ok(TestCase::Lib::SPVM::Math->test_isgreater);
ok(TestCase::Lib::SPVM::Math->test_isgreaterf);
ok(TestCase::Lib::SPVM::Math->test_isgreaterequal);
ok(TestCase::Lib::SPVM::Math->test_isgreaterequalf);
ok(TestCase::Lib::SPVM::Math->test_isless);
ok(TestCase::Lib::SPVM::Math->test_islessf);
ok(TestCase::Lib::SPVM::Math->test_islessequal);
ok(TestCase::Lib::SPVM::Math->test_islessequalf);
ok(TestCase::Lib::SPVM::Math->test_islessgreater);
ok(TestCase::Lib::SPVM::Math->test_islessgreaterf);
ok(TestCase::Lib::SPVM::Math->test_isunordered);
ok(TestCase::Lib::SPVM::Math->test_isunorderedf);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

__END__

# Call subroutine
{
  ok(TestCase::Lib::SPVM::Math->test_pi);
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
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
