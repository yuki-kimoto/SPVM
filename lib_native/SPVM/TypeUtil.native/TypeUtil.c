#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>

#include "spvm_api.h"

float SPVM__TypeUtil__FLT_MAX(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return FLT_MAX;
}

float SPVM__TypeUtil__FLT_MIN(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return FLT_MIN;
}

double SPVM__TypeUtil__DBL_MAX(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return DBL_MAX;
}

double SPVM__TypeUtil__DBL_MIN(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  return DBL_MIN;
}

