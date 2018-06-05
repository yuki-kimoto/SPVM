#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>

#include "spvm_native.h"

float SPVM__SPVM__TypeUtil__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return FLT_MAX;
}

float SPVM__SPVM__TypeUtil__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return FLT_MIN;
}

double SPVM__SPVM__TypeUtil__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return DBL_MAX;
}

double SPVM__SPVM__TypeUtil__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  return DBL_MIN;
}

