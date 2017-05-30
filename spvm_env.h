#ifndef SPVM_ENV_H
#define SPVM_ENV_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_env {
  // Call stack
  SPVM_VALUE* call_stack;
  
  // Call stack capacity
  int32_t call_stack_capacity;
  
  // Operand stack base
  int32_t call_stack_base;
  
  // Operand stack top
  int32_t operand_stack_top;
  
  // Exception
  _Bool abort;
};

SPVM_ENV* SPVM_ENV_new(SPVM* spvm);
void SPVM_ENV_free(SPVM* spvm, SPVM_ENV* env);

#endif
