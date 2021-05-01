#include "spvm_native.h"

#include <math.h>
#include <fenv.h>
#include <complex.h>

static const char* MFILE = "SPVM/Math.c";

int32_t SPNATIVE__SPVM__Math__acos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = acos(stack[0].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__acosf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = acosf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__acosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__acoshf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = acoshf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__asin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asin(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__asinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = asinf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__asinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__asinhf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = asinhf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__atan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__atan2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan2(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__atanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = atanf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__atanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__atanhf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = atanhf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__cabs(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double z_out = cabs(z);

  stack[0].dval = z_out;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cabsf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float z_out = cabsf(z);

  stack[0].fval = z_out;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cacos(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = cacos(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cacosf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = cacosf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cacosh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = cacosh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cacoshf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = cacoshf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__carg(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double z_out = carg(z);

  stack[0].dval = creal(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cargf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float z_out = cargf(z);

  stack[0].fval = z_out;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__casin(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = casin(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__casinf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = casinf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__casinh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = casinh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__casinhf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = casinhf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__catan(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = catan(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__catanf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = catanf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__catanh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = catanh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__catanhf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = catanhf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cbrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cbrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__cbrtf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = cbrtf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ccos(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = ccos(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ccosf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = ccosf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ccosh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = ccosh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ccoshf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = ccoshf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ceil(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = ceil(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__ceilf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = ceilf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cexp(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = cexp(z);
  
  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cexpf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = cexpf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__clog(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = clog(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__clogf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = clogf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__conj(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = conj(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__conjf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = conjf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}
int32_t SPNATIVE__SPVM__Math__copysign(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = copysign(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__copysignf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = copysignf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cos(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__cosf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = cosf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__cosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__coshf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = coshf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__cpow(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double x_pow = stack[2].dval;
  double y_pow = stack[3].dval;

  double complex z = re + im * _Complex_I;

  double complex z_pow = x_pow + y_pow * _Complex_I;

  double complex z_out = cpow(z, z_pow);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__cpowf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float x_pow = stack[2].fval;
  float y_pow = stack[3].fval;

  float complex z = re + im * _Complex_I;

  float complex z_pow = x_pow + y_pow * _Complex_I;

  float complex z_out = cpowf(z, z_pow);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csin(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = csin(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csinf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = csinf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csinh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = csinh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csinhf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = csinhf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csqrt(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = csqrt(z);
  
  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__csqrtf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = csqrtf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ctan(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;

  double complex z_out = ctan(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ctanf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  float complex z_out = ctanf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ctanh(SPVM_ENV* env, SPVM_VALUE* stack) {

  double re = stack[0].dval;
  double im = stack[1].dval;

  double complex z = re + im * _Complex_I;
  
  // In some mac OS, ctanh can't right value, so I calcurate from definition
  double complex z_out = csinh(z) / ccosh(z);

  stack[0].dval = creal(z_out);
  stack[1].dval = cimag(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ctanhf(SPVM_ENV* env, SPVM_VALUE* stack) {

  float re = stack[0].fval;
  float im = stack[1].fval;

  float complex z = re + im * _Complex_I;

  // In some mac OS, ctanh can't right value, so I calcurate from definition
  float complex z_out = csinhf(z) / ccoshf(z);

  stack[0].fval = crealf(z_out);
  stack[1].fval = cimagf(z_out);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__erf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erf(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__erfc(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erfc(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__erfcf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = erfcf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__erff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = erff(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__exp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__exp2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp2(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__exp2f(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = exp2f(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__expf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = expf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__expm1(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = expm1(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__expm1f(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = expm1(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fabs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = fabs(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__fabsf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fabsf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fdim(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = fdim(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fdimf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fdimf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FE_DOWNWARD(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FE_DOWNWARD;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FE_TONEAREST(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FE_TONEAREST;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FE_TOWARDZERO(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FE_TOWARDZERO;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FE_UPWARD(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FE_UPWARD;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fesetround(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t ival = stack[0].ival;

  stack[0].ival = fesetround(ival);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__floor(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = floor(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__floorf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = floor(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = fma(stack[0].dval, stack[1].dval, stack[2].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmaf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fmaf(stack[0].fval, stack[1].fval, stack[2].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmax(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = fmax(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmaxf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fmaxf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = fmin(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fminf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fminf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmod(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = fmod(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fmodf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = fmodf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FP_ILOGB0(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FP_ILOGB0;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FP_ILOGBNAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FP_ILOGBNAN;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FP_INFINITE(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FP_INFINITE;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FP_NAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FP_NAN;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__FP_ZERO(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].ival = FP_ZERO;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__fpclassify(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = fpclassify(dval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__fpclassifyf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  float fval = stack[0].fval;

  stack[0].ival = fpclassify(fval);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__frexp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = frexp(stack[0].dval, stack[1].iref);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__frexpf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = frexpf(stack[0].fval, stack[1].iref);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__HUGE_VAL(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)HUGE_VAL;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__HUGE_VALF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)HUGE_VALF;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__hypot(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = hypot(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__hypotf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = hypotf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ilogb(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = ilogb(stack[0].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ilogbf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = ilogbf(stack[0].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__INFINITY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].dval = (double)INFINITY;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__INFINITYF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  stack[0].fval = (float)INFINITY;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isfinite(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  double dval = stack[0].dval;

  stack[0].ival = isfinite(dval);

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isfinitef(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isfinite(fval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__isgreater(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isgreater(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isgreaterequal(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isgreaterequal(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isgreaterequalf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isgreaterequal(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isgreaterf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isgreater(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isinf(dval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__isinff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isinf(fval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__isless(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isless(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__islessequal(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = islessequal(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__islessequalf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = islessequal(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__islessf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isless(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__islessgreater(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = islessgreater(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__islessgreaterf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = islessgreater(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isnan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isnan(dval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__isnanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isnan(fval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__isunordered(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isunordered(stack[0].dval, stack[1].dval);

  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__isunorderedf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int32_t value = isunordered(stack[0].fval, stack[1].fval);

  stack[0].ival = value;

  return 0;
}




int32_t SPNATIVE__SPVM__Math__ldexp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = ldexp(stack[0].dval, stack[1].ival);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__ldexpf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = ldexpf(stack[0].fval, stack[1].ival);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__lgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = lgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__lgammaf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = lgammaf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__log(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__log10(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log10(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__log10f(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = log10(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__log1p(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log1p(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__log1pf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = log1pf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__log2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = log2(stack[0].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__log2f(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = log2f(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__logb(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = logb(stack[0].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__logbf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = logbf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__logf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = logf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__lround(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int64_t value = llround(stack[0].dval);

  stack[0].lval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__lroundf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  int64_t value = llroundf(stack[0].fval);

  stack[0].lval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__modf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = modf(stack[0].dval, stack[1].dref);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__modff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = modff(stack[0].fval, stack[1].fref);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__nan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  if (string == NULL) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }

  const char* tagp = env->get_chars(env, string);
  double value = nan(tagp);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__NAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)NAN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__nanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  if (string == NULL) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }

  const char* tagp = env->get_chars(env, string);
  float value = nanf(tagp);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__NANF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)NAN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__nearbyint(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = nearbyint(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__nearbyintf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = nearbyintf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__nextafter(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = nextafter(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__nextafterf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = nextafterf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__nexttoward(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = nexttoward(stack[0].dval, stack[1].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__nexttowardf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = nexttowardf(stack[0].fval, stack[1].dval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__pow(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = pow(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__powf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = powf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__remainder(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  // re - Math.Round(re / im) * im
  double value = remainder(stack[0].dval, stack[1].dval);

  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__remainderf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  // re - Math.Round(re / im) * im
  float value = remainderf(stack[0].fval, stack[1].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__remquo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = remquo(stack[0].dval, stack[1].dval, stack[2].iref);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__remquof(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = remquof(stack[0].fval, stack[1].fval, stack[2].iref);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__round(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = round(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__roundf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = roundf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__scalbln(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = scalbln(stack[0].dval, stack[1].lval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__scalblnf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = scalblnf(stack[0].fval, stack[1].lval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__scalbn(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = scalbn(stack[0].dval, stack[1].ival);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__scalbnf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = scalbnf(stack[0].fval, stack[1].ival);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__signbit(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = signbit(dval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__signbitf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = signbit(fval);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sin(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = sinf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sinhf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = sinhf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sqrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sqrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__sqrtf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = sqrtf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__tan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tan(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__tanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = tanf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__tanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__tanhf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  float value = tanhf(stack[0].fval);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__tgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Math__tgammaf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = tgammaf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__trunc(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  double value = trunc(stack[0].dval);

  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__SPVM__Math__truncf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  float value = truncf(stack[0].fval);

  stack[0].fval = value;

  return 0;
}
