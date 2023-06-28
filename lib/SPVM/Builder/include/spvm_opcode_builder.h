// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_BYTECODE_BUILDER_H
#define SPVM_BYTECODE_BUILDER_H

#include "spvm_typedecl.h"

void SPVM_OPCODE_BUILDER_build_opcode_array(SPVM_COMPILER* compiler);

void SPVM_OPCODE_BUILDER_set_opcode_id(SPVM_COMPILER* compiler, SPVM_OPCODE* opcode, int32_t opcode_id);

void SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(
  SPVM_COMPILER* compiler,
  SPVM_OPCODE_ARRAY* opcode_array,
  int32_t in_eval_block,
  SPVM_LIST* unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack,
  SPVM_LIST* unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack,
  SPVM_OP* op_method,
  int32_t line
);

int32_t SPVM_OPCODE_BUILDER_get_call_stack_index(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_OPCODE_BUILDER_get_returned_op_var(SPVM_COMPILER* compiler, SPVM_OP* op);

#endif
