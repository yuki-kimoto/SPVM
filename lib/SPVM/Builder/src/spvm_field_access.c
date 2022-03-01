#include "spvm_field_access.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_FIELD_ACCESS* SPVM_FIELD_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_new_block_compile_tmp(compiler, sizeof(SPVM_FIELD_ACCESS));
}
