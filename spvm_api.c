#include "spvm_api.h"
#include "spvm_runtime.h"
#include "spvm_util_allocator.h"

SPVM_API* SPVM_API_new() {
  SPVM_API* api = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_API));
  
  return api;
}
