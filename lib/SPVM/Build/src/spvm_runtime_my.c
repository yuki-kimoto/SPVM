#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_my.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_MY* SPVM_RUNTIME_MY_new() {
  SPVM_RUNTIME_MY* runtime_my = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_MY));
  
  return runtime_my;
}
