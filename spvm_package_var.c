#include "spvm_package_var.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_PACKAGE_VAR* SPVM_PACKAGE_VAR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_PACKAGE_VAR));
}
