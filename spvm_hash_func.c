#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm.h"
#include "spvm_hash_func.h"

uint32_t SPVM_HASH_FUNC_calc_hash(SPVM* spvm, const char* str, int32_t len) {
  (void)spvm;
  
  assert(len > 0);
  
  const char* str_tmp = str;
  uint32_t hash = 5381;
  while (len--) {
    hash = ((hash << 5) + hash) + (uint8_t) *str_tmp++;
  }
  
  return hash;
}
