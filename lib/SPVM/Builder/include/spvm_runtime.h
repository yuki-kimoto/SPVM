// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

struct spvm_runtime {
  SPVM_ALLOCATOR* allocator;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  
  SPVM_HASH* basic_type_symtable;
  
  int32_t basic_types_length;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

#endif
