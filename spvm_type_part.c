#include "spvm_type_part.h"

#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

const char* const SPVM_TYPE_PART_C_CODE_NAMES[] = {
  "sub",
  "name",
  "char"
};

SPVM_TYPE_PART* SPVM_TYPE_PART_new(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE_PART));
}
