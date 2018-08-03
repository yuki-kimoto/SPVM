#ifndef SPVM_LOOP_EXPANSION_H
#define SPVM_LOOP_EXPANSION_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_loop_expansion {
  int32_t loop_var_id;
  int32_t loop_var_init_start_opcode_index;
  int32_t goto_loop_start_opcode_index;
  int32_t loop_var_inc_start_opcode_index;
  int32_t condition_check_start_opcode_index;
  int32_t goto_loop_top_opcode_index;
  _Bool loop_var_is_int;
  _Bool can_expansion;
};

#endif
