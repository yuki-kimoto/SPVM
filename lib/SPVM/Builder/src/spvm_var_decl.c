// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_var_decl.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_VAR_DECL* SPVM_VAR_DECL_new(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_VAR_DECL));
  
  var_decl->index = -1;
  var_decl->runtime_var_index = -1;
  
  return var_decl;
}

SPVM_VAR_DECL* SPVM_VAR_DECL_new_arg(SPVM_COMPILER* compiler) {
  SPVM_VAR_DECL* var_decl = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_VAR_DECL));
  
  var_decl->index = -1;
  var_decl->runtime_var_index = -1;
  var_decl->is_arg = 1;
  
  return var_decl;
}
