#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

#include "spvm_native.h"

double SPVM__SPVM__Example__PI(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return 3.14159265358979323846;
}

double SPVM__SPVM__Example__E(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return 2.7182818284590452354;
}

int8_t SPVM__SPVM__Example__INT8_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int8_t)-128;
}

int8_t SPVM__SPVM__Example__INT8_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int8_t)127;
}

int16_t SPVM__SPVM__Example__INT16_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int16_t)-32768;
}

int16_t SPVM__SPVM__Example__INT16_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int16_t)32767;
}

int32_t SPVM__SPVM__Example__INT32_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int32_t)-2147483648L;
}

int32_t SPVM__SPVM__Example__INT32_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int32_t)2147483647L;
}

int64_t SPVM__SPVM__Example__INT64_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int64_t)-9223372036854775808LL;
}

int64_t SPVM__SPVM__Example__INT64_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (int64_t)9223372036854775807LL;
}

int32_t SPVM__SPVM__Example__isinff(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  return isinf(fval);
}

int32_t SPVM__SPVM__Example__isfinitef(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  return isfinite(fval);
}

int32_t SPVM__SPVM__Example__isnanf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  float fval = args[0].fval;
  
  return isnan(fval);
}

float SPVM__SPVM__Example__INFINITYF(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (float)INFINITY;
}

float SPVM__SPVM__Example__NANF(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (float)NAN;
}

double SPVM__SPVM__Example__INFINITY(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (double)INFINITY;
}

double SPVM__SPVM__Example__NAN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return (double)NAN;
}

int32_t SPVM__SPVM__Example__isinf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  return isinf(dval);
}

int32_t SPVM__SPVM__Example__isnan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  return isnan(dval);
}

int32_t SPVM__SPVM__Example__isfinite(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  double dval = args[0].dval;
  
  return isfinite(dval);
}

double SPVM__SPVM__Example__sin(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sin(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__cos(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cos(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__tan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tan(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__asin(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = asin(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__acosh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = acosh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__atanh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atanh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__asinh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = asinh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__acos(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = acos(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__atan(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atan(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__exp(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = exp(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__exp2(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = exp2(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__log(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__log10(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log10(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__sqrt(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sqrt(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__cbrt(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cbrt(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__ceil(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = ceil(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__remainder(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  // x - Example.Round(x / y) * y
  double value = remainder(args[0].dval, args[1].dval);

  return value;
}

double SPVM__SPVM__Example__floor(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = floor(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__nearbyint(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = nearbyint(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__atan2(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = atan2(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__SPVM__Example__pow(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = pow(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__SPVM__Example__round(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = round(args[0].dval);
  
  return value;
}

int32_t SPVM__SPVM__Example__abs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t value = (int32_t)labs(args[0].ival);
  
  return value;
}

int64_t SPVM__SPVM__Example__labs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int64_t value = (int64_t)labs(args[0].lval);
  
  return value;
}

double SPVM__SPVM__Example__fabs(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = fabs(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__erf(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = erf(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__erfc(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = erfc(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__lgamma(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = lgamma(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__tgamma(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tgamma(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__sinh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = sinh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__cosh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = cosh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__tanh(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = tanh(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__hypot(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = hypot(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__SPVM__Example__expm1(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = expm1(args[0].dval);
  
  return value;
}

double SPVM__SPVM__Example__log1p(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = log1p(args[0].dval);
  
  return value;
}

float SPVM__SPVM__Example__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return FLT_MAX;
}

float SPVM__SPVM__Example__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return FLT_MIN;
}

double SPVM__SPVM__Example__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return DBL_MAX;
}

double SPVM__SPVM__Example__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return DBL_MIN;
}

