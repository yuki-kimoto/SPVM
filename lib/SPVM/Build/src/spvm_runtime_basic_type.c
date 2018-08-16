#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_basic_type.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_BASIC_TYPE* SPVM_RUNTIME_BASIC_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_BASIC_TYPE));
  
  return runtime_basic_type;
}
