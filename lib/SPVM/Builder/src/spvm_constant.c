// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>


#include "spvm_compiler.h"
#include "spvm_constant.h"
#include "spvm_allocator.h"
#include "spvm_hash.h"
#include "spvm_type.h"

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler) {
  SPVM_CONSTANT* constant = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, sizeof(SPVM_CONSTANT));
  
  return constant;
}
