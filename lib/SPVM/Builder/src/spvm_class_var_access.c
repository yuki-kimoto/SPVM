#include "spvm_class_var_access.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_CLASS_VAR_ACCESS* SPVM_CLASS_VAR_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_new_block_tmp(compiler->allocator, sizeof(SPVM_CLASS_VAR_ACCESS));
}
