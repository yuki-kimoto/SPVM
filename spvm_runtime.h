#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_nai.h"

struct SPVM_runtime {
  
  // Runtime memory allocator
  SPVM_RUNTIME_ALLOCATOR* allocator;

  // Call stack
  SPVM_VALUE* call_stack;

  // Env
  SPVM_NAI* nai;
  
  // Exception
  SPVM_OBJECT* exception;
  
  // Bytecodes
  uint8_t* bytecodes;
  
  // Constant pool
  int32_t* constant_pool;
  
  // Call stack capacity
  int32_t call_stack_capacity;
  
  // Operand stack base
  int32_t call_stack_base;
  
  // Operand stack top
  int32_t operand_stack_top;
  
  // Packages length
  int32_t packages_length;

  // Indexes of package
  int32_t package_indexes_constant_pool_index;

  // Subroutines length
  int32_t subs_length;

  // Indexes of package
  int32_t sub_indexes_constant_pool_index;

  int32_t object_count;
  
  int32_t debug;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();
void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);
SPVM_NAI* SPVM_RUNTIME_new_nai(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_call_sub(SPVM_NAI* nai, int32_t sub_constant_pool_index);

#endif
