#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

// Method information
struct SPVM_sub {
  SPVM_OP* op_name;
  SPVM_OP* op_return_type;
  SPVM_OP* op_block;
  SPVM_OP* op_package;
  SPVM_OP* op_constant;
  SPVM_LIST* op_args;
  SPVM_LIST* op_mys;
  SPVM_LIST* on_stack_replacement_jump_opcode_indexes;
  void* native_address;
  const char* abs_name;
  const char* file_name;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t call_sub_arg_stack_max;
  int32_t id;
  int32_t eval_stack_max_length;
  int32_t loop_structure_count;
  _Bool is_native;
  _Bool is_enum;
  _Bool is_destructor;
  _Bool is_jit;
  _Bool disable_jit;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
