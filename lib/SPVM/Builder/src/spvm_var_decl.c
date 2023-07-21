// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_var_decl.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_VAR_DECL* SPVM_VAR_DECL_new(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, sizeof(SPVM_VAR_DECL));

  var_decl->index = -1;
  var_decl->call_stack_index = -1;
  
  return var_decl;
}

SPVM_VAR_DECL* SPVM_VAR_DECL_new_eternal(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, sizeof(SPVM_VAR_DECL));

  var_decl->index = -1;
  var_decl->call_stack_index = -1;
  var_decl->is_permanent = 1;
  
  return var_decl;
}
