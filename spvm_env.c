#include "spvm_env.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime_api.h"

SPVM_ENV* SPVM_ENV_new() {
  SPVM_ENV* env = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_ENV));
  
  env->get_array_length = SPVM_RUNTIME_API_get_array_length;
  
  return env;
}
