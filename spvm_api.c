#include "spvm_api.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime_api.h"

SPVM_API* SPVM_API_new() {
  SPVM_API* api = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_API));
  
  api->get_array_length = SPVM_RUNTIME_API_get_array_length;
  
  return api;
}
