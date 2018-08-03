#ifndef SPVM_LOOP_H
#define SPVM_LOOP_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_loop {
  SPVM_OP* op_term_init;
  SPVM_OP* op_block_statements;
  SPVM_OP* op_loop_increment;
  SPVM_OP* op_condition;
  SPVM_OP* op_var_loop;

  int32_t loop_first_goto_opcode_rel_index;
  int32_t loop_increment_start_opcode_rel_index;
  int32_t loop_condition_start_opcode_rel_index;

  int32_t sub_rel_id;
  int32_t loop_var_id;
  int32_t goto_loop_start_opcode_index;
  int32_t condition_check_start_opcode_index;
  int32_t goto_loop_top_opcode_index;
  _Bool loop_var_is_int;
  _Bool create_for_statement;
};

SPVM_LOOP* SPVM_LOOP_new(SPVM_COMPILER* compiler);

#endif
