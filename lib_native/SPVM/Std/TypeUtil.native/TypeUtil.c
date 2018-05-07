#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <float.h>

#include "spvm_api.h"

float SPVM__Std__TypeUtil__INFINITYF(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return (float)INFINITY;
}

float SPVM__Std__TypeUtil__NANF(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return (float)NAN;
}

float SPVM__Std__TypeUtil__FLT_MAX(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return FLT_MAX;
}

float SPVM__Std__TypeUtil__FLT_MIN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return FLT_MIN;
}

int32_t SPVM__Std__TypeUtil__isinff(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  return isinf(float_value);
}

int32_t SPVM__Std__TypeUtil__isfinitef(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  return isfinite(float_value);
}

int32_t SPVM__Std__TypeUtil__isnanf(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  return isnan(float_value);
}

double SPVM__Std__TypeUtil__INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return (double)INFINITY;
}

double SPVM__Std__TypeUtil__NAN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return (double)NAN;
}

double SPVM__Std__TypeUtil__DBL_MAX(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return DBL_MAX;
}

double SPVM__Std__TypeUtil__DBL_MIN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  return DBL_MIN;
}

int32_t SPVM__Std__TypeUtil__isinf(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  return isinf(double_value);
}

int32_t SPVM__Std__TypeUtil__isnan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  return isnan(double_value);
}

int32_t SPVM__Std__TypeUtil__isfinite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  return isfinite(double_value);
}
