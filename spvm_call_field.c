#include "spvm_call_field.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_CALL_FIELD* SPVM_CALL_FIELD_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_CALL_FIELD));
}
