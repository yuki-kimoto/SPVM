#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_arg.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_ARG* SPVM_RUNTIME_ARG_new() {
  SPVM_RUNTIME_ARG* runtime_arg = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_ARG));
  
  return runtime_arg;
}
