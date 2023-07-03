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
  
  SPVM_RUNTIME_CLASS_VAR* class_vars;
  
  int32_t class_vars_length;
  
  SPVM_RUNTIME_FIELD* fields;
  
  int32_t fields_length;
  
  SPVM_RUNTIME_METHOD* methods;
  
  int32_t methods_length;
  
  SPVM_RUNTIME_ARG* args;
  
  int32_t args_length;
  
  int32_t* anon_basic_type_ids;
  
  int32_t anon_basic_type_ids_length;
  
  SPVM_OPCODE* opcodes;
  
  int32_t* opcodes_length;
  
  SPVM_HASH* basic_type_symtable;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);

SPVM_ALLOCATOR* SPVM_RUNTIME_get_allocator(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_build(SPVM_RUNTIME* runtime, int32_t* runtime_codes);

#endif
