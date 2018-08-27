#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_info_type.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_INFO_TYPE* SPVM_RUNTIME_INFO_TYPE_new() {
  SPVM_RUNTIME_INFO_TYPE* runtime_info_type = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_INFO_TYPE));
  
  return runtime_info_type;
}
