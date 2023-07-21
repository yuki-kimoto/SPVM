// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_field_access.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_FIELD_ACCESS* SPVM_FIELD_ACCESS_new(SPVM_COMPILER* compiler) {
  return SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, sizeof(SPVM_FIELD_ACCESS));
}
