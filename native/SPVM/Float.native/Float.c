#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>

#include "spvm_api.h"

float SPVM__Float__POSITIVE_INFINITY(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t positive_infinity_bits = 0x7f800000;
  
  float positive_infinity;
  
  memcpy((void*)&positive_infinity, (void*)&positive_infinity_bits, sizeof(float));
  
  return positive_infinity;
}
