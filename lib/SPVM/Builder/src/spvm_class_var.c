// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>
#include <string.h>

#include "spvm_class_var.h"
#include "spvm_compiler.h"
#include "spvm_allocator.h"

SPVM_CLASS_VAR* SPVM_CLASS_VAR_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  return SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_CLASS_VAR));
}

