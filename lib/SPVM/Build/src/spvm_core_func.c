#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>
#include <math.h>
#include <time.h>

#include "spvm_native.h"

int32_t SPVM_CORE_FUNC_time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* object = stack[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_warn(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* object = stack[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc((char)bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isinff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isinf(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isfinitef(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isfinite(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isnanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isnan(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INFINITYF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_NANF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INFINITY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_NAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isinf(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isnan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isnan(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_isfinite(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isfinite(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_sin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_cos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_tan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_asin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_acosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_atanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_asinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_acos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_atan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_exp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_exp2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp2(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_log(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_log10(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log10(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_sqrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sqrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_cbrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cbrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_ceil(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = ceil(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_remainder(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  // x - Math.Round(x / y) * y
  double value = remainder(stack[0].dval, stack[1].dval);

  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_floor(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = floor(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_nearbyint(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = nearbyint(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_atan2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan2(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_pow(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = pow(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_round(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = round(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_abs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t value = (int32_t)labs(stack[0].ival);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_labs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int64_t value = (int64_t)labs(stack[0].lval);
  
  stack[0].lval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_fabs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = fabs(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_erf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erf(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_erfc(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erfc(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_lgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = lgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_tgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_sinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_cosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_tanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_hypot(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = hypot(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_expm1(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = expm1(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_log1p(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log1p(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM__SPVM__Math__PI(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 3.14159265358979323846;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM__SPVM__Math__E(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 2.7182818284590452354;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT8_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)-128;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT8_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)127;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT16_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)-32768;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT16_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)32767;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT32_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)-2147483648UL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT32_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)2147483647L;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT64_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)-9223372036854775808ULL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_INT64_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)9223372036854775807LL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_PI(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 3.14159265358979323846;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_CORE_FUNC_E(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 2.7182818284590452354;
  
  return SPVM_SUCCESS;;
}
