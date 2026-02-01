// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_BLOCK_H
#define SPVM_BLOCK_H

#include "spvm_typedecl.h"

enum {
  SPVM_BLOCK_C_ID_NORMAL,
  SPVM_BLOCK_C_ID_IF,
  SPVM_BLOCK_C_ID_ELSE,
  SPVM_BLOCK_C_ID_SWITCH_OUTER,
  SPVM_BLOCK_C_ID_SWITCH_INNER,
  SPVM_BLOCK_C_ID_LOOP_OUTER,
  SPVM_BLOCK_C_ID_LOOP_INNER,
  SPVM_BLOCK_C_ID_METHOD,
  SPVM_BLOCK_C_ID_EVAL,
  SPVM_BLOCK_C_ID_INIT_BLOCK,
  SPVM_BLOCK_C_ID_END_BLOCK,
};

struct spvm_block {
  int32_t id;
  int32_t no_scope;
  int32_t has_object_var_decls;
  int32_t need_leave_scope;
  int32_t mortal_stack_tops_index;
  int32_t begin_opcode_index;
  int32_t condition_opcode_index;
  int32_t loop_increment_opcode_index;
  int32_t if_end_goto_opcode_index;
};

SPVM_BLOCK* SPVM_BLOCK_new(SPVM_COMPILER* compiler);

#endif
