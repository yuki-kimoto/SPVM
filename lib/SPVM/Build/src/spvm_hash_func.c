#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_hash_func.h"

int32_t SPVM_HASH_FUNC_calc_hash_for_index(const char* str, int32_t len) {
  
  assert(len >= 0);
  
  const char* str_tmp = str;
  int32_t hash = 5381;
  while (len--) {
    hash = ((hash << 5) + hash) + (uint8_t) *str_tmp++;
  }
  
  if (hash < 0) {
    hash = ~hash;
  }
  
  return hash;
}
