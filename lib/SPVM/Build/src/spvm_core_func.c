#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>
#include <math.h>
#include <time.h>

#include "spvm_native.h"

int32_t SPVM_CORE_FUNC_time(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  int64_t timer_value = (int64_t)time(NULL);
  
  args[0].lval = timer_value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_print(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* object = args[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
  
  return 0;
}

int32_t SPVM_CORE_FUNC_warn(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* object = args[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc((char)bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isinff(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  args[0].ival = isinf(fval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isfinitef(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  args[0].ival = isfinite(fval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isnanf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  args[0].ival = isnan(fval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INFINITYF(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].fval = (float)INFINITY;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_NANF(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].fval = (float)NAN;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INFINITY(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = (double)INFINITY;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_NAN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = (double)NAN;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isinf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  args[0].ival = isinf(dval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isnan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  args[0].ival = isnan(dval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_isfinite(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  args[0].ival = isfinite(dval);
  
  return 0;
}

int32_t SPVM_CORE_FUNC_sin(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sin(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_cos(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cos(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_tan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tan(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_asin(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = asin(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_acosh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = acosh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_atanh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atanh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_asinh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = asinh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_acos(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = acos(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_atan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atan(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_exp(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = exp(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_exp2(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = exp2(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_log(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_log10(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log10(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_sqrt(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sqrt(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_cbrt(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cbrt(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_ceil(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = ceil(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_remainder(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  // x - Math.Round(x / y) * y
  double value = remainder(args[0].dval, args[1].dval);

  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_floor(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = floor(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_nearbyint(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = nearbyint(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_atan2(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atan2(args[0].dval, args[1].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_pow(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = pow(args[0].dval, args[1].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_round(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = round(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_abs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t value = (int32_t)labs(args[0].ival);
  
  args[0].ival = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_labs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int64_t value = (int64_t)labs(args[0].lval);
  
  args[0].lval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_fabs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = fabs(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_erf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = erf(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_erfc(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = erfc(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_lgamma(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = lgamma(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_tgamma(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tgamma(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_sinh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sinh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_cosh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cosh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_tanh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tanh(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_hypot(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = hypot(args[0].dval, args[1].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_expm1(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = expm1(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_log1p(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log1p(args[0].dval);
  
  args[0].dval = value;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_FLT_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_FLT_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_DBL_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_DBL_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPVM__SPVM__Math__PI(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = 3.14159265358979323846;
  
  return 0;
}

int32_t SPVM__SPVM__Math__E(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = 2.7182818284590452354;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT8_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].bval = (int8_t)-128;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT8_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].bval = (int8_t)127;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT16_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].sval = (int16_t)-32768;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT16_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].sval = (int16_t)32767;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT32_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].ival = (int32_t)-2147483648UL;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT32_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].ival = (int32_t)2147483647L;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT64_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].lval = (int64_t)-9223372036854775808ULL;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_INT64_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].lval = (int64_t)9223372036854775807LL;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_PI(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = 3.14159265358979323846;
  
  return 0;
}

int32_t SPVM_CORE_FUNC_E(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  args[0].dval = 2.7182818284590452354;
  
  return 0;
}
