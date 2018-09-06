#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_package.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_PACKAGE* SPVM_RUNTIME_PACKAGE_new() {
  SPVM_RUNTIME_PACKAGE* runtime_package = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_PACKAGE));
  
  return runtime_package;
}
