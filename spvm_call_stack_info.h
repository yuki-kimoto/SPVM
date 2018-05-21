#ifndef SPVM_CALL_STACK_INFO_H
#define SPVM_CALL_STACK_INFO_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_call_stack_info {
  int32_t mortal_stack_base;
  int32_t* mortal_stack;
};

void SPVM_CALL_STACK_init_call_stack_info(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id);
void SPVM_CALL_STACK_foo(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id);

#endif
