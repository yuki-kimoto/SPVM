#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_api.h"

double SPVM__Double__POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t positive_infinity_bits = 0x7ff0000000000000L;
  
  double positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(double));
  
  return positive_infinity;
}

double SPVM__Double__NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t negative_infinity_bits = 0xfff0000000000000L;
  
  double negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(double));
  
  return negative_infinity;
}

double SPVM__Double__NaN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t nan_bits = 0x7ff8000000000000L;
  
  double nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(double));
  
  return nan;
}

double SPVM__Double__MAX_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t max_value_bits = 0x7fefffffffffffffL;
  
  double max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(double));
  
  return max_value;
}

double SPVM__Double__MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t min_normal_bits = 0x0010000000000000L;
  
  double min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(double));
  
  return min_normal;
}

double SPVM__Double__MIN_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t min_value_bits = 0x1L;
  
  double min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(double));
  
  return min_value;
}

int32_t SPVM__Double__is_infinite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  if (isinf(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Double__is_nan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  if (isnan(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Double__is_finite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  if (isfinite(double_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int64_t SPVM__Double__double_to_long_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
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

int64_t SPVM__Double__double_to_raw_long_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  uint64_t long_bits;
  
  memcpy((void*)&long_bits, (void*)&double_value, sizeof(double));
  
  return (int64_t)long_bits;
}

int64_t SPVM__Double__long_bits_to_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint64_t long_bits = (uint64_t)args[0].long_value;
  
  if ((long_bits >= 0x7ff0000000000001L && long_bits <= 0x7fffffffffffffffL) || (long_bits >= 0xfff0000000000001L && long_bits <= 0xffffffffffffffffL)) {
    long_bits = 0x7ff8000000000000L;
  }
  
  double double_value;
  
  memcpy((void*)&double_value, (void*)&long_bits, sizeof(double));
  
  return double_value;
}
