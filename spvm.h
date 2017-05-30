#ifndef SPVM_H
#define SPVM_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct spvm_ {
  
  // Parser
  SPVM_PARSER* parser;
  
  // Entry point subroutine name
  const char* entry_point_sub_name;
  
  // Constant pool
  SPVM_CONSTANT_POOL* constant_pool;
  
  // Constant pool package symbol table
  SPVM_HASH* constant_pool_package_symtable;

  // Constant pool field symbol table
  SPVM_HASH* constant_pool_field_symtable;

  // Constant pool subroutine symbol table
  SPVM_HASH* constant_pool_sub_symtable;
  
  // Bytecodes
  SPVM_BYTECODE_ARRAY* bytecode_array;
  
  // Runtime memory allocator
  SPVM_ALLOCATOR_RUNTIME* allocator_runtime;
  
  // use memory pool max reference byte size
  int64_t ref_max_byte_size_use_memory_pool;
};

SPVM* SPVM_new();
void SPVM_run(SPVM* spvm, const char* package_name);
void SPVM_free(SPVM* spvm);

#endif
