// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_typedecl.h"

struct spvm_runtime {
  int32_t* runtime_codes;
  
  int32_t runtime_codes_length;
  
  SPVM_ALLOCATOR* allocator;
  
  const char* string_pool;
  
  SPVM_RUNTIME_STRING* constant_strings;
  
  int32_t constant_strings_length;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  
  int32_t basic_types_length;
  
  SPVM_RUNTIME_METHOD* methods;
  
  SPVM_RUNTIME_ARG* args;
  
  SPVM_OPCODE* opcodes;
  
  SPVM_HASH* basic_type_symtable;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

#endif
