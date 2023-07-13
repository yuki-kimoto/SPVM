// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_allocator.h"
#include "spvm_runtime.h"
#include "spvm_hash.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_arg.h"
#include "spvm_opcode.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  SPVM_RUNTIME* runtime = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_RUNTIME));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  runtime->allocator = allocator;
  
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(runtime->allocator, 0);
  
  return runtime;
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // SPVM_ALLOCATOR_free_memory_block_tmp(runtime->allocator, runtime->basic_types);
    
  // Free allocator
  // SPVM_ALLOCATOR_free(runtime->allocator);
  // runtime->allocator = NULL;
}
