#include "spvm_var_decl.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_VAR_DECL* SPVM_VAR_DECL_new(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, sizeof(SPVM_VAR_DECL));

  var_decl->id = -1;
  var_decl->mem_id = -1;
  
  return var_decl;
}

SPVM_VAR_DECL* SPVM_VAR_DECL_new_eternal(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_VAR_DECL));

  var_decl->id = -1;
  var_decl->mem_id = -1;
  var_decl->is_eternal = 1;
  
  return var_decl;
}
