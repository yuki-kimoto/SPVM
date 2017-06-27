#include "spvm_env.h"
#include "spvm_api.h"
#include "spvm_util_allocator.h"

SPVM_ENV* SPVM_ENV_new() {
  SPVM_ENV* env = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_ENV));
  
  env->constant_pool = NULL;
  
  void** functions = {
    &SPVM_API_get_array_length
  };
  
  env->functions = functions;
  
  return env;
}
