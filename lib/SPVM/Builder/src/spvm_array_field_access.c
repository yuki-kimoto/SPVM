#include "spvm_array_field_access.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_ARRAY_FIELD_ACCESS* SPVM_ARRAY_FIELD_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_ARRAY_FIELD_ACCESS));
}
