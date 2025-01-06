// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_version_from.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_VERSION_FROM* SPVM_VERSION_FROM_new(SPVM_COMPILER* compiler) {
  SPVM_VERSION_FROM* version_from = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->current_each_compile_allocator, sizeof(SPVM_VERSION_FROM));
  
  return version_from;
}
