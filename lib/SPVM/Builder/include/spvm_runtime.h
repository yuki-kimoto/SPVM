// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

#include <stdlib.h>
#include <stdio.h>

struct spvm_runtime {
  SPVM_COMPILER* compiler;
  
  SPVM_ENV* env;
  
  SPVM_ALLOCATOR* allocator;
  
  SPVM_RUNTIME_BASIC_TYPE** basic_types;
  
  SPVM_HASH* basic_type_symtable;
  
  int32_t basic_types_length;
  
  SPVM_HASH* assignability_symtable; 
  
  SPVM_MUTEX* mutex;
  
  SPVM_MUTEX* mutex_atomic;
  
  int32_t memory_blocks_count;
  
  FILE* spvm_stdin;
  
  FILE* spvm_stdout;
  
  FILE* spvm_stderr;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();

SPVM_COMPILER* SPVM_COMPILER_new_with_runtime(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_init_stdio(SPVM_RUNTIME* runtime);

#endif
