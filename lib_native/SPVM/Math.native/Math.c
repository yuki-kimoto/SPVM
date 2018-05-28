#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#include "spvm_api.h"

#define SPVM__MATH__PI 3.14159265358979323846
#define SPVM__MATH__E 2.7182818284590452354

int32_t SPVM__Math__isinff(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  float fval = args[0].fval;
  
  return isinf(fval);
}

int32_t SPVM__Math__isfinitef(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  float fval = args[0].fval;
  
  return isfinite(fval);
}

int32_t SPVM__Math__isnanf(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  float fval = args[0].fval;
  
  return isnan(fval);
}

float SPVM__Math__INFINITYF(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return (float)INFINITY;
}

float SPVM__Math__NANF(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return (float)NAN;
}

double SPVM__Math__INFINITY(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return (double)INFINITY;
}

double SPVM__Math__NAN(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return (double)NAN;
}

int32_t SPVM__Math__isinf(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  double dval = args[0].dval;
  
  return isinf(dval);
}

int32_t SPVM__Math__isnan(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  double dval = args[0].dval;
  
  return isnan(dval);
}

int32_t SPVM__Math__isfinite(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  double dval = args[0].dval;
  
  return isfinite(dval);
}

double SPVM__Math__sin(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = sin(args[0].dval);
  
  return value;
}

double SPVM__Math__cos(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = cos(args[0].dval);
  
  return value;
}

double SPVM__Math__tan(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = tan(args[0].dval);
  
  return value;
}

double SPVM__Math__asin(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = asin(args[0].dval);
  
  return value;
}

double SPVM__Math__acosh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = acosh(args[0].dval);
  
  return value;
}

double SPVM__Math__atanh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = atanh(args[0].dval);
  
  return value;
}

double SPVM__Math__asinh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = asinh(args[0].dval);
  
  return value;
}

double SPVM__Math__acos(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = acos(args[0].dval);
  
  return value;
}

double SPVM__Math__atan(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = atan(args[0].dval);
  
  return value;
}

double SPVM__Math__exp(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = exp(args[0].dval);
  
  return value;
}

double SPVM__Math__exp2(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = exp2(args[0].dval);
  
  return value;
}

double SPVM__Math__log(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = log(args[0].dval);
  
  return value;
}

double SPVM__Math__log10(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = log10(args[0].dval);
  
  return value;
}

double SPVM__Math__sqrt(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = sqrt(args[0].dval);
  
  return value;
}

double SPVM__Math__cbrt(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = cbrt(args[0].dval);
  
  return value;
}

double SPVM__Math__ceil(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = ceil(args[0].dval);
  
  return value;
}

double SPVM__Math__remainder(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  // x - Math.Round(x / y) * y
  double value = remainder(args[0].dval, args[1].dval);

  return value;
}

double SPVM__Math__floor(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = floor(args[0].dval);
  
  return value;
}

double SPVM__Math__nearbyint(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = nearbyint(args[0].dval);
  
  return value;
}

double SPVM__Math__atan2(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = atan2(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__Math__pow(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = pow(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__Math__round(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = round(args[0].dval);
  
  return value;
}

int32_t SPVM__Math__abs(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  int32_t value = (int32_t)labs(args[0].ival);
  
  return value;
}

int64_t SPVM__Math__labs(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  int64_t value = (int64_t)labs(args[0].lval);
  
  return value;
}

double SPVM__Math__fabs(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = fabs(args[0].dval);
  
  return value;
}

double SPVM__Math__erf(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = erf(args[0].dval);
  
  return value;
}

double SPVM__Math__erfc(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = erfc(args[0].dval);
  
  return value;
}

double SPVM__Math__lgamma(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = lgamma(args[0].dval);
  
  return value;
}

double SPVM__Math__tgamma(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = tgamma(args[0].dval);
  
  return value;
}

double SPVM__Math__sinh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = sinh(args[0].dval);
  
  return value;
}

double SPVM__Math__cosh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = cosh(args[0].dval);
  
  return value;
}

double SPVM__Math__tanh(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = tanh(args[0].dval);
  
  return value;
}

double SPVM__Math__hypot(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = hypot(args[0].dval, args[1].dval);
  
  return value;
}

double SPVM__Math__expm1(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = expm1(args[0].dval);
  
  return value;
}

double SPVM__Math__log1p(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = log1p(args[0].dval);
  
  return value;
}
