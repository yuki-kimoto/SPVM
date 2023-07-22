// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_use.h"
#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler) {
  SPVM_USE* use = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_USE));
  
  return use;
}
