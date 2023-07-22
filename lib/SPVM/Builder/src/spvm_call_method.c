// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_call_method.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_CALL_METHOD* SPVM_CALL_METHOD_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_CALL_METHOD));
}
