#include "spvm_field_access.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_FIELD_ACCESS* SPVM_FIELD_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, sizeof(SPVM_FIELD_ACCESS));
}
