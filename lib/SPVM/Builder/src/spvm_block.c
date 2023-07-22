// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_block.h"
#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_BLOCK* SPVM_BLOCK_new(SPVM_COMPILER* compiler) {
  SPVM_BLOCK* block = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_BLOCK));
  
  return block;
}
