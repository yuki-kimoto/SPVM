#ifndef SPVM_LOOP_INFO_H
#define SPVM_LOOP_INFO_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_loop_info {
  int32_t sub_rel_id;
  int32_t loop_var_id;
  int32_t loop_var_init_start_opcode_index;
  int32_t goto_loop_start_opcode_index;
  int32_t loop_var_inc_start_opcode_index;
  int32_t condition_check_start_opcode_index;
  int32_t goto_loop_top_opcode_index;
  _Bool loop_var_is_int;
  _Bool can_info;
};

SPVM_LOOP_INFO* SPVM_LOOP_INFO_new(SPVM_COMPILER* compiler);

#endif
