#include "spvm_native.h"

int32_t SPNATIVE__MyMath__spvm_sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t loop_count = stack[0].ival;

  int32_t total = 0;
  for (int32_t i = 0; i < loop_count; i++) {
    total += i;
  }
  
  stack[0].ival = total;
  
  return 0;
}
