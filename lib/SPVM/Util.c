#include "spvm_native.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>
#include <complex.h>
#include <memory.h>
#include <ctype.h>
#include <errno.h>

static const char* MFILE = "SPVM/Util.c";

int32_t SPNATIVE__SPVM__Util__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return 0;
}

int32_t SPNATIVE__SPVM__Util__srand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int64_t seed = stack[0].lval;
  
  srand((unsigned)seed);

  return 0;
}

int32_t SPNATIVE__SPVM__Util__crand(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = rand();

  return 0;
}

int32_t SPNATIVE__SPVM__Util__RAND_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = RAND_MAX;

  return 0;
}
