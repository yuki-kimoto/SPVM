#include "spvm_native.h"

#include <math.h>

int32_t SPNATIVE__SPVM__Math__isinff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isinf(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__isfinitef(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isfinite(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__isnanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isnan(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__INFINITYF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__NANF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__INFINITY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__NAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__signbitf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double fval = stack[0].fval;
  
  stack[0].ival = signbit(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__signbit(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = signbit(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__isinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isinf(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__isnan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isnan(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__isfinite(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isfinite(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__sin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__cos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__tan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__asin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__acosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__atanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__asinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__acos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__atan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__exp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__exp2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp2(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__log(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__log10(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log10(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__sqrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sqrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__cbrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cbrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__ceil(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = ceil(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__remainder(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  // x - Math.Round(x / y) * y
  double value = remainder(stack[0].dval, stack[1].dval);

  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__floor(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = floor(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__nearbyint(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = nearbyint(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__atan2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan2(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__pow(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = pow(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__round(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = round(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__fabs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = fabs(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__erf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erf(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__erfc(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erfc(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__lgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = lgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__tgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__sinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__cosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__tanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__hypot(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = hypot(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__expm1(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = expm1(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPNATIVE__SPVM__Math__log1p(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log1p(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}
