// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>
#include <string.h>

#include "spvm_module_file.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_MODULE_FILE* SPVM_MODULE_FILE_new(SPVM_COMPILER* compiler) {
  
  return SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_MODULE_FILE));
}
