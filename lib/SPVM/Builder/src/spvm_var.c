#include "spvm_var.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_VAR* SPVM_VAR_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_block_tmp(compiler->allocator, sizeof(SPVM_VAR));
}
