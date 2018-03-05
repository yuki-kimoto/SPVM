#ifndef SPVM_CALL_STACK_INFO_H
#define SPVM_CALL_STACK_INFO_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_call_stack_info {
  int32_t length;
  int32_t auto_dec_ref_count_stack_top_base;
  int32_t auto_dec_ref_count_stack_base;
  int32_t loop_stack_base;
};

void SPVM_CALL_STACK_init_call_stack_info(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id);
void SPVM_CALL_STACK_foo(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id);

#endif
