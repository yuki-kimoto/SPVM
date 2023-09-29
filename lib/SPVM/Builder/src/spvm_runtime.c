// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <unistd.h>

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
#include "spvm_mutex.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  SPVM_RUNTIME* runtime = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_RUNTIME));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  runtime->allocator = allocator;
  
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(runtime->allocator, 0);
  
  runtime->assignability_symtable = SPVM_HASH_new_hash_permanent(runtime->allocator, 0);
  
  int32_t mutex_assignability_symtable_size = SPVM_MUTEX_size();
  void* mutex_assignability_symtable = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, mutex_assignability_symtable_size);
  SPVM_MUTEX_init(mutex_assignability_symtable);
  runtime->mutex_assignability_symtable = mutex_assignability_symtable;
  
  int32_t mutex_update_object_size = SPVM_MUTEX_size();
  void* mutex_update_object = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, mutex_update_object_size);
  SPVM_MUTEX_init(mutex_update_object);
  runtime->mutex_update_object = mutex_update_object;
  
  spvm_warn("LINE %d", __LINE__);
  
  runtime->spvm_stdin = fdopen(dup(fileno(stdin)), "rb");
  
  spvm_warn("LINE %d", __LINE__);
  
  setvbuf(runtime->spvm_stdin, NULL, _IOLBF, 0);
  
  spvm_warn("LINE %d", __LINE__);
  
  runtime->spvm_stdout = fdopen(dup(fileno(stdout)), "wb");
  
  spvm_warn("LINE %d", __LINE__);
  
  setvbuf(runtime->spvm_stdout, NULL, _IOLBF, 0);
  
  spvm_warn("LINE %d", __LINE__);
  
  runtime->spvm_stderr = fdopen(dup(fileno(stderr)), "wb");
  
  spvm_warn("LINE %d", __LINE__);
  
  setvbuf(runtime->spvm_stderr, NULL, _IONBF, 0);
  
  spvm_warn("LINE %d", __LINE__);
  
  return runtime;
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  if (runtime->basic_types) {
    SPVM_ALLOCATOR_free_memory_block_tmp(runtime->allocator, runtime->basic_types);
  }
  
  SPVM_MUTEX_destroy(runtime->mutex_assignability_symtable);
  
  spvm_warn("LINE %d", __LINE__);
  
  fclose(runtime->spvm_stdin);
  
  spvm_warn("LINE %d", __LINE__);
  
  fclose(runtime->spvm_stdout);
  
  spvm_warn("LINE %d", __LINE__);
  
  fclose(runtime->spvm_stderr);
  
  spvm_warn("LINE %d", __LINE__);
  
  // Free allocator
  SPVM_ALLOCATOR_free(runtime->allocator);
  runtime->allocator = NULL;
}
