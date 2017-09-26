#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_api.h"

double SPVM__Double__POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t positive_infinity_bits = 0x7f800000;
  
  double positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(double));
  
  return positive_infinity;
}

double SPVM__Double__NEGATIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t negative_infinity_bits = 0xff800000;
  
  double negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(double));
  
  return negative_infinity;
}

double SPVM__Double__NaN(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t nan_bits = 0x7fc00000;
  
  double nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(double));
  
  return nan;
}

double SPVM__Double__MAX_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t max_value_bits = 0x7f7fffff;
  
  double max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(double));
  
  return max_value;
}

double SPVM__Double__MIN_NORMAL(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t min_normal_bits = 0x00800000;
  
  double min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(double));
  
  return min_normal;
}

double SPVM__Double__MIN_VALUE(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t min_value_bits = 0x1;
  
  double min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(double));
  
  return min_value;
}

double SPVM__Double__MAX_EXPONENT(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t max_exponent_bits = 0x1;
  
  double max_exponent;
  
  memcpy((void*)&max_exponent, (void*)&max_exponent_bits, sizeof(double));
  
  return max_exponent;
}

int32_t SPVM__Double__is_infinite(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  uint32_t int_bits;
  
  memcpy((void*)&int_bits, (void*)&double_value, sizeof(double));
  
  if (int_bits == 0x7f800000 || int_bits == 0xff800000) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Double__double_to_int_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;

  double double_value = args[0].double_value;
  
  if (isnan(double_value)) {
    uint32_t bits = 0x7fc00000;
    return (int32_t)bits;
  }
  else {
    uint32_t int_bits;
    
    memcpy((void*)&int_bits, (void*)&double_value, sizeof(double));
    
    return (int32_t)int_bits;
  }
}

int32_t SPVM__Double__double_to_raw_int_bits(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double double_value = args[0].double_value;
  
  uint32_t int_bits;
  
  memcpy((void*)&int_bits, (void*)&double_value, sizeof(double));
  
  return (int32_t)int_bits;
}

int32_t SPVM__Double__int_bits_to_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  uint32_t int_bits = (uint32_t)args[0].int_value;
  
  if ((int_bits >= 0x7f800001 && int_bits <= 0x7fffffff) || (int_bits >= 0xff800001 && int_bits <= 0xffffffff)) {
    int_bits = 0x7fc00000;
  }
  
  double double_value;
  
  memcpy((void*)&double_value, (void*)&int_bits, sizeof(double));
  
  return double_value;
}
