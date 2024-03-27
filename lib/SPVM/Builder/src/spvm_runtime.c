// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>

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
  
  int32_t mutex_size = SPVM_MUTEX_size();
  void* mutex = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, mutex_size);
  SPVM_MUTEX_init(mutex);
  runtime->mutex = mutex;
  
  int32_t mutex_atomic_size = SPVM_MUTEX_size();
  void* mutex_atomic = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, mutex_atomic_size);
  SPVM_MUTEX_init(mutex_atomic);
  runtime->mutex_atomic = mutex_atomic;
  
  SPVM_RUNTIME_init_stdio(runtime);
  
  SPVM_ENV* env = SPVM_NATIVE_new_env();
  
  runtime->env = env;
  
  env->runtime = runtime;
  
  return runtime;
}

void SPVM_RUNTIME_init_stdio(SPVM_RUNTIME* runtime) {
  
  // stdin
  {
    int32_t stdin_fileno = fileno(stdin);
    
    assert(stdin_fileno >= 0);
    
    int32_t stdin_fileno_dup = dup(stdin_fileno);
    
    assert(stdin_fileno_dup > 2);
    
    FILE* spvm_stdin = fdopen(stdin_fileno_dup, "r");
    
    assert(spvm_stdin);
    
#if defined(_WIN32)
    
    setmode(fileno(spvm_stdin), _O_BINARY);
    
#endif
    
    runtime->spvm_stdin = spvm_stdin;
  }
  
  // stdout
  {
    int32_t stdout_fileno = fileno(stdout);
    
    assert(stdout_fileno >= 0);
    
    int32_t stdout_fileno_dup = dup(stdout_fileno);
    
    assert(stdout_fileno_dup > 2);
    
    FILE* spvm_stdout = fdopen(stdout_fileno_dup, "w");
    
    assert(spvm_stdout);
    
#if defined(_WIN32)
    
    setmode(fileno(spvm_stdout), _O_BINARY);
    
#endif
    
    runtime->spvm_stdout = spvm_stdout;
    
  }
  
  // stderr
  {
    int32_t stderr_fileno = fileno(stderr);
    
    assert(stderr_fileno >= 0);
    
    int32_t stderr_fileno_dup = dup(stderr_fileno);
    
    assert(stderr_fileno_dup > 2);
    
    FILE* spvm_stderr = fdopen(stderr_fileno_dup, "w");
    
    assert(spvm_stderr);
    
#if defined(_WIN32)
    
    setmode(fileno(spvm_stderr), _O_BINARY);
    
#endif
    
    setvbuf(spvm_stderr, NULL, _IONBF, 0);
    
    runtime->spvm_stderr = spvm_stderr;
  }
  
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  SPVM_ENV* env = runtime->env;
  
  env->free_env(env);
  
  if (runtime->basic_types) {
    SPVM_ALLOCATOR_free_memory_block_tmp(runtime->allocator, runtime->basic_types);
  }
  
  SPVM_MUTEX_destroy(runtime->mutex);
  
  SPVM_MUTEX_destroy(runtime->mutex_atomic);
  
  fclose(runtime->spvm_stdin);
  
  fclose(runtime->spvm_stdout);
  
  fclose(runtime->spvm_stderr);
  
  // Free allocator
  SPVM_ALLOCATOR_free(runtime->allocator);
  runtime->allocator = NULL;
}
