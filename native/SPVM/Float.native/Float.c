#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_interface.h"

float SPVM__Float__POSITIVE_INFINITY(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t positive_infinity_bits = 0x7f800000;
  
  float positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(float));
  
  return positive_infinity;
}

float SPVM__Float__NEGATIVE_INFINITY(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t negative_infinity_bits = 0xff800000;
  
  float negative_infinity;
  
  memcpy((void*)&negative_infinity, (void*)&negative_infinity_bits, sizeof(float));
  
  return negative_infinity;
}

float SPVM__Float__NaN(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t nan_bits = 0x7fc00000;
  
  float nan;
  
  memcpy((void*)&nan, (void*)&nan_bits, sizeof(float));
  
  return nan;
}

float SPVM__Float__MAX_VALUE(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t max_value_bits = 0x7f7fffff;
  
  float max_value;
  
  memcpy((void*)&max_value, (void*)&max_value_bits, sizeof(float));
  
  return max_value;
}

float SPVM__Float__MIN_NORMAL(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t min_normal_bits = 0x00800000;
  
  float min_normal;
  
  memcpy((void*)&min_normal, (void*)&min_normal_bits, sizeof(float));
  
  return min_normal;
}

float SPVM__Float__MIN_VALUE(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t min_value_bits = 0x1;
  
  float min_value;
  
  memcpy((void*)&min_value, (void*)&min_value_bits, sizeof(float));
  
  return min_value;
}

float SPVM__Float__MAX_EXPONENT(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t max_exponent_bits = 0x1;
  
  float max_exponent;
  
  memcpy((void*)&max_exponent, (void*)&max_exponent_bits, sizeof(float));
  
  return max_exponent;
}

int32_t SPVM__Float__is_infinite(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  float float_value = args[0].float_value;
  
  if (isinf(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Float__is_finite(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  float float_value = args[0].float_value;
  
  if (isfinite(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Float__is_nan(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  float float_value = args[0].float_value;
  
  if (isnan(float_value)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM__Float__float_to_int_bits(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;

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

int32_t SPVM__Float__float_to_raw_int_bits(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  float float_value = args[0].float_value;
  
  uint32_t int_bits;
  
  memcpy((void*)&int_bits, (void*)&float_value, sizeof(float));
  
  return (int32_t)int_bits;
}

float SPVM__Float__int_bits_to_float(SPVM_API* api, SPVM_VALUE* args) {
  (void)api;
  
  uint32_t int_bits = (uint32_t)args[0].int_value;
  
  if ((int_bits >= 0x7f800001 && int_bits <= 0x7fffffff) || (int_bits >= 0xff800001 && int_bits <= 0xffffffff)) {
    int_bits = 0x7fc00000;
  }
  
  float float_value;
  
  memcpy((void*)&float_value, (void*)&int_bits, sizeof(float));
  
  return float_value;
}
