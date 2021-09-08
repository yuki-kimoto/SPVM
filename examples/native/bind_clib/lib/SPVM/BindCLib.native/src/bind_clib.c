#include "bind_clib.h"

int32_t bind_clib_sum(int32_t* nums, int32_t length) {
  
  int32_t total = 0;
  for (int32_t i = 0; i < length; i++) {
    total += nums[i];
  }
  
  return total;
}
