// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_allow.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ALLOW* SPVM_ALLOW_new(SPVM_COMPILER* compiler) {
  SPVM_ALLOW* allow = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, sizeof(SPVM_ALLOW));
  
  return allow;
}
