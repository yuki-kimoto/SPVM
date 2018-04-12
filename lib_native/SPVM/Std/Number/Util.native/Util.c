#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_api.h"

float SPVM__Std__Number__Util__FLOAT_POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t positive_infinity_bits = 0x7f800000;
  
  float positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(float));
  
  return positive_infinity;
}

float SPVM__Std__Number__Util__FLOAT_NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t negative_infinity_bits = 0xff800000;
  
  float negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(float));
  
  return negative_infinity;
}

float SPVM__Std__Number__Util__FLOAT_NAN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t nan_bits = 0x7fc00000;
  
  float nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(float));
  
  return nan;
}

float SPVM__Std__Number__Util__FLOAT_MAX_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t max_value_bits = 0x7f7fffff;
  
  float max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(float));
  
  return max_value;
}

float SPVM__Std__Number__Util__FLOAT_MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t min_normal_bits = 0x00800000;
  
  float min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(float));
  
  return min_normal;
}

float SPVM__Std__Number__Util__FLOAT_MIN_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t min_value_bits = 0x1;
  
  float min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(float));
  
  return min_value;
}

float SPVM__Std__Number__Util__FLOAT_MAX_EXPONENT(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t max_exponent_bits = 0x1;
  
  float max_exponent;
  
  memcpy((void*)&max_exponent, (void*)&max_exponent_bits, sizeof(float));
  
  return max_exponent;
}

int32_t SPVM__Std__Number__Util__float_is_infinite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  if (isinf(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Std__Number__Util__float_is_finite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  if (isfinite(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Std__Number__Util__float_is_nan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  if (isnan(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Std__Number__Util__float_float_to_int_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;

  float float_value = args[0].float_value;
  
  if (isnan(float_value)) {
    uint32_t bits = 0x7fc00000;
    return (int32_t)bits;
  }
  else {
    uint32_t int_bits;
    
    memcpy((void*)&int_bits, (void*)&float_value, sizeof(float));
    
    return (int32_t)int_bits;
  }
}

int32_t SPVM__Std__Number__Util__float_float_to_raw_int_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  float float_value = args[0].float_value;
  
  uint32_t int_bits;
  
  memcpy((void*)&int_bits, (void*)&float_value, sizeof(float));
  
  return (int32_t)int_bits;
}

float SPVM__Std__Number__Util__float_int_bits_to_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint32_t int_bits = (uint32_t)args[0].int_value;
  
  if ((int_bits >= 0x7f800001 && int_bits <= 0x7fffffff) || (int_bits >= 0xff800001 && int_bits <= 0xffffffff)) {
    int_bits = 0x7fc00000;
  }
  
  float float_value;
  
  memcpy((void*)&float_value, (void*)&int_bits, sizeof(float));
  
  return float_value;
}

double SPVM__Std__Number__Util__DOUBLE_POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t positive_infinity_bits = 0x7ff0000000000000L;
  
  double positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(double));
  
  return positive_infinity;
}

double SPVM__Std__Number__Util__DOUBLE_NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t negative_infinity_bits = 0xfff0000000000000L;
  
  double negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(double));
  
  return negative_infinity;
}

double SPVM__Std__Number__Util__DOUBLE_NAN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t nan_bits = 0x7ff8000000000000L;
  
  double nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(double));
  
  return nan;
}

double SPVM__Std__Number__Util__DOUBLE_MAX_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t max_value_bits = 0x7fefffffffffffffL;
  
  double max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(double));
  
  return max_value;
}

double SPVM__Std__Number__Util__DOUBLE_MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t min_normal_bits = 0x0010000000000000L;
  
  double min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(double));
  
  return min_normal;
}

double SPVM__Std__Number__Util__DOUBLE_MIN_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t min_value_bits = 0x1L;
  
  double min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(double));
  
  return min_value;
}

int32_t SPVM__Std__Number__Util__double_is_infinite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  if (isinf(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Std__Number__Util__double_is_nan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  if (isnan(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Std__Number__Util__double_is_finite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  if (isfinite(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int64_t SPVM__Std__Number__Util__double_double_to_long_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  if (isnan(double_value)) {
    uint64_t bits = 0x7ff8000000000000L;
    return (int64_t)bits;
  }
  else {
    uint64_t long_bits;
    
    memcpy((void*)&long_bits, (void*)&double_value, sizeof(double));
    
    return (int64_t)long_bits;
  }
}

int64_t SPVM__Std__Number__Util__double_double_to_raw_long_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  double double_value = args[0].double_value;
  
  uint64_t long_bits;
  
  memcpy((void*)&long_bits, (void*)&double_value, sizeof(double));
  
  return (int64_t)long_bits;
}

double SPVM__Std__Number__Util__double_long_bits_to_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  uint64_t long_bits = (uint64_t)args[0].long_value;
  
  if ((long_bits >= 0x7ff0000000000001L && long_bits <= 0x7fffffffffffffffL) || (long_bits >= 0xfff0000000000001L && long_bits <= 0xffffffffffffffffL)) {
    long_bits = 0x7ff8000000000000L;
  }
  
  double double_value;
  
  memcpy((void*)&double_value, (void*)&long_bits, sizeof(double));
  
  return double_value;
}
