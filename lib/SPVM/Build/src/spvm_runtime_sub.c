#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_sub.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_SUB* SPVM_RUNTIME_SUB_new() {
  SPVM_RUNTIME_SUB* runtime_sub = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_SUB));
  
  return runtime_sub;
}
