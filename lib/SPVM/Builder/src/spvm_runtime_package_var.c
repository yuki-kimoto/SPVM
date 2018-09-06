#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_runtime_package_var.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME_PACKAGE_VAR* SPVM_RUNTIME_PACKAGE_VAR_new() {
  SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_PACKAGE_VAR));
  
  return runtime_package_var;
}
