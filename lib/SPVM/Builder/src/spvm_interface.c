// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_interface.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_INTERFACE* SPVM_INTERFACE_new(SPVM_COMPILER* compiler) {
  SPVM_INTERFACE* interface = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_INTERFACE));
  
  return interface;
}
