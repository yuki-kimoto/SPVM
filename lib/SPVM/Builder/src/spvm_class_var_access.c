#include "spvm_class_var_access.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_CLASS_VAR_ACCESS* SPVM_CLASS_VAR_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_CLASS_VAR_ACCESS));
}
