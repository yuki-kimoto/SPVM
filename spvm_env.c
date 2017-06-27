#include "spvm_env.h"
#include "spvm_util_allocator.h"

SPVM_ENV* SPVM_ENV_new() {
  SPVM_ENV* env = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_ENV));
  
  return env;
}
