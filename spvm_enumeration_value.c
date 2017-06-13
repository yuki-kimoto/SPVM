#include "spvm_enumeration_value.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_ENUMERATION_VALUE* SPVM_ENUMERATION_VALUE_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_ENUMERATION_VALUE));
}
