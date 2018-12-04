#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_native.h"

struct SPVM_runtime {
  SPVM_PORTABLE* portable;
  
  int32_t* constant_pool;
  int32_t constant_pool_length;
  
  SPVM_OPCODE* opcodes;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_types;
  SPVM_RUNTIME_BASIC_TYPE* sorted_basic_types;
  int32_t basic_types_length;

  SPVM_RUNTIME_FIELD* fields;
  int32_t fields_length;

  SPVM_RUNTIME_PACKAGE_VAR* package_vars;
  int32_t package_vars_length;

  SPVM_RUNTIME_ARG* args;
  
  SPVM_RUNTIME_SUB* subs;
  int32_t subs_length;

  SPVM_RUNTIME_PACKAGE* packages;
  int32_t packages_length;

  char* string_pool;
  int32_t string_pool_length;

  // Package variables
  SPVM_VALUE* package_vars_heap;
  
  // C function addresses(native or precompile)
  void** sub_cfunc_addresses;
  
  // Memory blocks count
  int32_t memory_blocks_count;
};

#endif
