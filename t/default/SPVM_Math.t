use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use POSIX();
use TestFile;
use Math::Complex;

use Math::Trig 'pi';


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

use SPVM 'TestCase::Lib::SPVM::Math';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# PI
{
  ok(TestCase::Lib::SPVM::Math->test_PI);
  if ($] >= 5.022) {
    is(SPVM::Math->PI, 0x1.921fb54442d18p+1);
  }
}

# E
{
  ok(TestCase::Lib::SPVM::Math->test_E);
  if ($] >= 5.022) {
    is(SPVM::Math->E, 0x1.5bf0a8b145769p+1);
  }
}

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

#absolute value functions
{
  ok(TestCase::Lib::SPVM::Math->test_abs);
  ok(TestCase::Lib::SPVM::Math->test_labs);
  ok(TestCase::Lib::SPVM::Math->test_fabs);
  ok(TestCase::Lib::SPVM::Math->test_fabsf);
}

# Power function
ok(TestCase::Lib::SPVM::Math->test_cbrt);
ok(TestCase::Lib::SPVM::Math->test_cbrtf);
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

# Complex Operations
{
  ok(TestCase::Lib::SPVM::Math->test_complexf);
  ok(TestCase::Lib::SPVM::Math->test_complex);
  ok(TestCase::Lib::SPVM::Math->test_caddf);
  ok(TestCase::Lib::SPVM::Math->test_cadd);
  ok(TestCase::Lib::SPVM::Math->test_csubf);
  ok(TestCase::Lib::SPVM::Math->test_csub);
  ok(TestCase::Lib::SPVM::Math->test_cmulf);
  ok(TestCase::Lib::SPVM::Math->test_cmul);
  ok(TestCase::Lib::SPVM::Math->test_cscamulf);
  ok(TestCase::Lib::SPVM::Math->test_cscamul);
  ok(TestCase::Lib::SPVM::Math->test_cdivf);
  ok(TestCase::Lib::SPVM::Math->test_cdiv);
}

# Complex Functions
{
  ok(TestCase::Lib::SPVM::Math->test_cacos);
  ok(TestCase::Lib::SPVM::Math->test_cacosf);

  ok(TestCase::Lib::SPVM::Math->test_casin);
  ok(TestCase::Lib::SPVM::Math->test_casinf);
  
  ok(TestCase::Lib::SPVM::Math->test_catan);
  ok(TestCase::Lib::SPVM::Math->test_catanf);

  ok(TestCase::Lib::SPVM::Math->test_ccos);
  ok(TestCase::Lib::SPVM::Math->test_ccosf);

  ok(TestCase::Lib::SPVM::Math->test_csin);
  ok(TestCase::Lib::SPVM::Math->test_csinf);

  ok(TestCase::Lib::SPVM::Math->test_ctan);
  ok(TestCase::Lib::SPVM::Math->test_ctanf);

  ok(TestCase::Lib::SPVM::Math->test_cacosh);
  ok(TestCase::Lib::SPVM::Math->test_cacoshf);

  ok(TestCase::Lib::SPVM::Math->test_casinh);
  ok(TestCase::Lib::SPVM::Math->test_casinhf);
  
  ok(TestCase::Lib::SPVM::Math->test_catanh);
  ok(TestCase::Lib::SPVM::Math->test_catanhf);

  ok(TestCase::Lib::SPVM::Math->test_ccosh);
  ok(TestCase::Lib::SPVM::Math->test_ccoshf);

  ok(TestCase::Lib::SPVM::Math->test_csinh);
  ok(TestCase::Lib::SPVM::Math->test_csinhf);

  ok(TestCase::Lib::SPVM::Math->test_ctanh);
  ok(TestCase::Lib::SPVM::Math->test_ctanhf);

  ok(TestCase::Lib::SPVM::Math->test_clog);
  ok(TestCase::Lib::SPVM::Math->test_clogf);

  ok(TestCase::Lib::SPVM::Math->test_cabs);
  ok(TestCase::Lib::SPVM::Math->test_cabsf);

  ok(TestCase::Lib::SPVM::Math->test_carg);
  ok(TestCase::Lib::SPVM::Math->test_cargf);

  ok(TestCase::Lib::SPVM::Math->test_conj);
  ok(TestCase::Lib::SPVM::Math->test_conjf);

  ok(TestCase::Lib::SPVM::Math->test_cexp);
  ok(TestCase::Lib::SPVM::Math->test_cexpf);

  ok(TestCase::Lib::SPVM::Math->test_cpow);
  ok(TestCase::Lib::SPVM::Math->test_cpowf);

  ok(TestCase::Lib::SPVM::Math->test_csqrt);
  ok(TestCase::Lib::SPVM::Math->test_csqrtf);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
