#include <assert.h>
#include <string.h>

#include "spvm_package_var.h"
#include "spvm_compiler.h"
#include "spvm_compiler_allocator.h"

SPVM_PACKAGE_VAR* SPVM_PACKAGE_VAR_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_PACKAGE_VAR));
}

