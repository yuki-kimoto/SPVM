#include "spvm_array_field_access.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ARRAY_FIELD_ACCESS* SPVM_ARRAY_FIELD_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_block_tmp(compiler->allocator, sizeof(SPVM_ARRAY_FIELD_ACCESS));
}
