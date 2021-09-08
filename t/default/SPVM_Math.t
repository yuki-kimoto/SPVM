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

use SPVM 'SPVM::TestCase::Lib::Math';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# PI
{
  ok(SPVM::TestCase::Lib::Math->test_PI);
  if ($] >= 5.022) {
    my $val = eval "0x1.921fb54442d18p+1";
    cmp_ok(SPVM::Math->PI, '==', $val);
  }
}

# E
{
  ok(SPVM::TestCase::Lib::Math->test_E);
  if ($] >= 5.022) {
    my $val = eval "0x1.5bf0a8b145769p+1";
    cmp_ok(SPVM::Math->E, '==', $val);
  }
}

# Trigonometric functions
ok(SPVM::TestCase::Lib::Math->test_cos);
ok(SPVM::TestCase::Lib::Math->test_cosf);
ok(SPVM::TestCase::Lib::Math->test_sin);
ok(SPVM::TestCase::Lib::Math->test_sinf);
ok(SPVM::TestCase::Lib::Math->test_tan);
ok(SPVM::TestCase::Lib::Math->test_tanf);
ok(SPVM::TestCase::Lib::Math->test_acos);
ok(SPVM::TestCase::Lib::Math->test_acosf);
ok(SPVM::TestCase::Lib::Math->test_asin);
ok(SPVM::TestCase::Lib::Math->test_asinf);
ok(SPVM::TestCase::Lib::Math->test_atan);
ok(SPVM::TestCase::Lib::Math->test_atanf);

# Hyperbolic functions
ok(SPVM::TestCase::Lib::Math->test_cosh);
ok(SPVM::TestCase::Lib::Math->test_coshf);
ok(SPVM::TestCase::Lib::Math->test_sinh);
ok(SPVM::TestCase::Lib::Math->test_sinhf);
ok(SPVM::TestCase::Lib::Math->test_tanh);
ok(SPVM::TestCase::Lib::Math->test_tanhf);
ok(SPVM::TestCase::Lib::Math->test_acosh);
ok(SPVM::TestCase::Lib::Math->test_acoshf);
ok(SPVM::TestCase::Lib::Math->test_asinh);
ok(SPVM::TestCase::Lib::Math->test_asinhf);
ok(SPVM::TestCase::Lib::Math->test_atanh);
ok(SPVM::TestCase::Lib::Math->test_atanhf);

# Exponential and logarithmic functions
ok(SPVM::TestCase::Lib::Math->test_exp);
ok(SPVM::TestCase::Lib::Math->test_expf);
ok(SPVM::TestCase::Lib::Math->test_exp2);
ok(SPVM::TestCase::Lib::Math->test_exp2f);
ok(SPVM::TestCase::Lib::Math->test_expm1);
ok(SPVM::TestCase::Lib::Math->test_expm1f);
ok(SPVM::TestCase::Lib::Math->test_frexp);
ok(SPVM::TestCase::Lib::Math->test_frexpf);
ok(SPVM::TestCase::Lib::Math->test_ilogb);
ok(SPVM::TestCase::Lib::Math->test_ilogbf);
ok(SPVM::TestCase::Lib::Math->test_ldexp);
ok(SPVM::TestCase::Lib::Math->test_ldexpf);
ok(SPVM::TestCase::Lib::Math->test_log);
ok(SPVM::TestCase::Lib::Math->test_logf);
ok(SPVM::TestCase::Lib::Math->test_log10);
ok(SPVM::TestCase::Lib::Math->test_log10f);
ok(SPVM::TestCase::Lib::Math->test_log1p);
ok(SPVM::TestCase::Lib::Math->test_log1pf);
ok(SPVM::TestCase::Lib::Math->test_log2);
ok(SPVM::TestCase::Lib::Math->test_log2f);
ok(SPVM::TestCase::Lib::Math->test_logb);
ok(SPVM::TestCase::Lib::Math->test_logbf);
ok(SPVM::TestCase::Lib::Math->test_modf);
ok(SPVM::TestCase::Lib::Math->test_modff);
ok(SPVM::TestCase::Lib::Math->test_scalbn);
ok(SPVM::TestCase::Lib::Math->test_scalbnf);
ok(SPVM::TestCase::Lib::Math->test_scalbln);
ok(SPVM::TestCase::Lib::Math->test_scalblnf);

#absolute value functions
{
  ok(SPVM::TestCase::Lib::Math->test_abs);
  ok(SPVM::TestCase::Lib::Math->test_labs);
  ok(SPVM::TestCase::Lib::Math->test_fabs);
  ok(SPVM::TestCase::Lib::Math->test_fabsf);
}

# Power function
ok(SPVM::TestCase::Lib::Math->test_cbrt);
ok(SPVM::TestCase::Lib::Math->test_cbrtf);
ok(SPVM::TestCase::Lib::Math->test_hypot);
ok(SPVM::TestCase::Lib::Math->test_hypotf);
ok(SPVM::TestCase::Lib::Math->test_pow);
ok(SPVM::TestCase::Lib::Math->test_powf);
ok(SPVM::TestCase::Lib::Math->test_sqrt);
ok(SPVM::TestCase::Lib::Math->test_sqrtf);

# Error function and gamma functions
ok(SPVM::TestCase::Lib::Math->test_erf);
ok(SPVM::TestCase::Lib::Math->test_erff);
ok(SPVM::TestCase::Lib::Math->test_erfc);
ok(SPVM::TestCase::Lib::Math->test_erfcf);
ok(SPVM::TestCase::Lib::Math->test_lgamma);
ok(SPVM::TestCase::Lib::Math->test_lgammaf);
ok(SPVM::TestCase::Lib::Math->test_tgamma);
ok(SPVM::TestCase::Lib::Math->test_tgammaf);

# Nearest integer functions
ok(SPVM::TestCase::Lib::Math->test_ceil);
ok(SPVM::TestCase::Lib::Math->test_ceilf);
ok(SPVM::TestCase::Lib::Math->test_floor);
ok(SPVM::TestCase::Lib::Math->test_floorf);
ok(SPVM::TestCase::Lib::Math->test_nearbyint);
ok(SPVM::TestCase::Lib::Math->test_nearbyintf);
ok(SPVM::TestCase::Lib::Math->test_round);
ok(SPVM::TestCase::Lib::Math->test_roundf);
ok(SPVM::TestCase::Lib::Math->test_lround);
ok(SPVM::TestCase::Lib::Math->test_lroundf);
ok(SPVM::TestCase::Lib::Math->test_trunc);
ok(SPVM::TestCase::Lib::Math->test_truncf);

# Surplus functions
ok(SPVM::TestCase::Lib::Math->test_fmod);
ok(SPVM::TestCase::Lib::Math->test_fmodf);
ok(SPVM::TestCase::Lib::Math->test_remainder);
ok(SPVM::TestCase::Lib::Math->test_remainderf);
ok(SPVM::TestCase::Lib::Math->test_remquo);
ok(SPVM::TestCase::Lib::Math->test_remquof);

# Real number operation functions
ok(SPVM::TestCase::Lib::Math->test_copysign);
ok(SPVM::TestCase::Lib::Math->test_copysignf);
ok(SPVM::TestCase::Lib::Math->test_nan);
ok(SPVM::TestCase::Lib::Math->test_nanf);
ok(SPVM::TestCase::Lib::Math->test_nextafter);
ok(SPVM::TestCase::Lib::Math->test_nextafterf);
ok(SPVM::TestCase::Lib::Math->test_nexttoward);
ok(SPVM::TestCase::Lib::Math->test_nexttowardf);

# Maximum, minimum and positive difference functions
ok(SPVM::TestCase::Lib::Math->test_fdim);
ok(SPVM::TestCase::Lib::Math->test_fdimf);
ok(SPVM::TestCase::Lib::Math->test_fmax);
ok(SPVM::TestCase::Lib::Math->test_fmaxf);
ok(SPVM::TestCase::Lib::Math->test_fmin);
ok(SPVM::TestCase::Lib::Math->test_fminf);

# Floating point multiplication and additions
ok(SPVM::TestCase::Lib::Math->test_fma);
ok(SPVM::TestCase::Lib::Math->test_fmaf);

# Classification
ok(SPVM::TestCase::Lib::Math->test_fpclassify);
ok(SPVM::TestCase::Lib::Math->test_fpclassifyf);
ok(SPVM::TestCase::Lib::Math->test_isfinite);
ok(SPVM::TestCase::Lib::Math->test_isfinitef);
ok(SPVM::TestCase::Lib::Math->test_isinf);
ok(SPVM::TestCase::Lib::Math->test_isinff);
ok(SPVM::TestCase::Lib::Math->test_isnan);
ok(SPVM::TestCase::Lib::Math->test_isnanf);
ok(SPVM::TestCase::Lib::Math->test_signbit);
ok(SPVM::TestCase::Lib::Math->test_signbitf);

# Comparison
ok(SPVM::TestCase::Lib::Math->test_isgreater);
ok(SPVM::TestCase::Lib::Math->test_isgreaterf);
ok(SPVM::TestCase::Lib::Math->test_isgreaterequal);
ok(SPVM::TestCase::Lib::Math->test_isgreaterequalf);
ok(SPVM::TestCase::Lib::Math->test_isless);
ok(SPVM::TestCase::Lib::Math->test_islessf);
ok(SPVM::TestCase::Lib::Math->test_islessequal);
ok(SPVM::TestCase::Lib::Math->test_islessequalf);
ok(SPVM::TestCase::Lib::Math->test_islessgreater);
ok(SPVM::TestCase::Lib::Math->test_islessgreaterf);
ok(SPVM::TestCase::Lib::Math->test_isunordered);
ok(SPVM::TestCase::Lib::Math->test_isunorderedf);

# Complex Operations
{
  ok(SPVM::TestCase::Lib::Math->test_complexf);
  ok(SPVM::TestCase::Lib::Math->test_complex);
  ok(SPVM::TestCase::Lib::Math->test_caddf);
  ok(SPVM::TestCase::Lib::Math->test_cadd);
  ok(SPVM::TestCase::Lib::Math->test_csubf);
  ok(SPVM::TestCase::Lib::Math->test_csub);
  ok(SPVM::TestCase::Lib::Math->test_cmulf);
  ok(SPVM::TestCase::Lib::Math->test_cmul);
  ok(SPVM::TestCase::Lib::Math->test_cscamulf);
  ok(SPVM::TestCase::Lib::Math->test_cscamul);
  ok(SPVM::TestCase::Lib::Math->test_cdivf);
  ok(SPVM::TestCase::Lib::Math->test_cdiv);
}

# Complex Functions
{
  ok(SPVM::TestCase::Lib::Math->test_cacos);
  ok(SPVM::TestCase::Lib::Math->test_cacosf);

  ok(SPVM::TestCase::Lib::Math->test_casin);
  ok(SPVM::TestCase::Lib::Math->test_casinf);
  
  ok(SPVM::TestCase::Lib::Math->test_catan);
  ok(SPVM::TestCase::Lib::Math->test_catanf);

  ok(SPVM::TestCase::Lib::Math->test_ccos);
  ok(SPVM::TestCase::Lib::Math->test_ccosf);

  ok(SPVM::TestCase::Lib::Math->test_csin);
  ok(SPVM::TestCase::Lib::Math->test_csinf);

  ok(SPVM::TestCase::Lib::Math->test_ctan);
  ok(SPVM::TestCase::Lib::Math->test_ctanf);

  ok(SPVM::TestCase::Lib::Math->test_cacosh);
  ok(SPVM::TestCase::Lib::Math->test_cacoshf);

  ok(SPVM::TestCase::Lib::Math->test_casinh);
  ok(SPVM::TestCase::Lib::Math->test_casinhf);
  
  ok(SPVM::TestCase::Lib::Math->test_catanh);
  ok(SPVM::TestCase::Lib::Math->test_catanhf);

  ok(SPVM::TestCase::Lib::Math->test_ccosh);
  ok(SPVM::TestCase::Lib::Math->test_ccoshf);

  ok(SPVM::TestCase::Lib::Math->test_csinh);
  ok(SPVM::TestCase::Lib::Math->test_csinhf);

  ok(SPVM::TestCase::Lib::Math->test_ctanh);
  ok(SPVM::TestCase::Lib::Math->test_ctanhf);

  ok(SPVM::TestCase::Lib::Math->test_clog);
  ok(SPVM::TestCase::Lib::Math->test_clogf);

  ok(SPVM::TestCase::Lib::Math->test_cabs);
  ok(SPVM::TestCase::Lib::Math->test_cabsf);

  ok(SPVM::TestCase::Lib::Math->test_carg);
  ok(SPVM::TestCase::Lib::Math->test_cargf);

  ok(SPVM::TestCase::Lib::Math->test_conj);
  ok(SPVM::TestCase::Lib::Math->test_conjf);

  ok(SPVM::TestCase::Lib::Math->test_cexp);
  ok(SPVM::TestCase::Lib::Math->test_cexpf);

  ok(SPVM::TestCase::Lib::Math->test_cpow);
  ok(SPVM::TestCase::Lib::Math->test_cpowf);

  ok(SPVM::TestCase::Lib::Math->test_csqrt);
  ok(SPVM::TestCase::Lib::Math->test_csqrtf);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
