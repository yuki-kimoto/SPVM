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

#endif
