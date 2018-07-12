#include "spvm_var.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_VAR* SPVM_VAR_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_VAR));
}
