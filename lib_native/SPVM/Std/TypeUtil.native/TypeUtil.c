#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_api.h"

float SPVM__Std__TypeUtil__FLOAT_POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t positive_infinity_bits = 0x7f800000;
  
  float positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(float));
  
  return positive_infinity;
}

float SPVM__Std__TypeUtil__FLOAT_NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t negative_infinity_bits = 0xff800000;
  
  float negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(float));
  
  return negative_infinity;
}

float SPVM__Std__TypeUtil__FLOAT_NAN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t nan_bits = 0x7fc00000;
  
  float nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(float));
  
  return nan;
}

float SPVM__Std__TypeUtil__FLOAT_MAX(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t max_value_bits = 0x7f7fffff;
  
  float max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(float));
  
  return max_value;
}

float SPVM__Std__TypeUtil__FLOAT_MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t min_normal_bits = 0x00800000;
  
  float min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(float));
  
  return min_normal;
}

float SPVM__Std__TypeUtil__FLOAT_MIN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t min_value_bits = 0x1;
  
  float min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(float));
  
  return min_value;
}

float SPVM__Std__TypeUtil__FLOAT_MAX_EXPONENT(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t max_exponent_bits = 0x1;
  
  float max_exponent;
  
  memcpy((void*)&max_exponent, (void*)&max_exponent_bits, sizeof(float));
  
  return max_exponent;
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

double SPVM__Std__TypeUtil__DOUBLE_POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t positive_infinity_bits = 0x7ff0000000000000L;
  
  double positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(double));
  
  return positive_infinity;
}

double SPVM__Std__TypeUtil__DOUBLE_NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t negative_infinity_bits = 0xfff0000000000000L;
  
  double negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(double));
  
  return negative_infinity;
}

double SPVM__Std__TypeUtil__DOUBLE_NAN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t nan_bits = 0x7ff8000000000000L;
  
  double nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(double));
  
  return nan;
}

double SPVM__Std__TypeUtil__DOUBLE_MAX(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t max_value_bits = 0x7fefffffffffffffL;
  
  double max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(double));
  
  return max_value;
}

double SPVM__Std__TypeUtil__DOUBLE_MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t min_normal_bits = 0x0010000000000000L;
  
  double min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(double));
  
  return min_normal;
}

double SPVM__Std__TypeUtil__DOUBLE_MIN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t min_value_bits = 0x1L;
  
  double min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(double));
  
  return min_value;
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
