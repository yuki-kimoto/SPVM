#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

// Method information
struct SPVM_sub {
  void* native_address;
  void* jit_address;
  SPVM_OP* op_name;
  SPVM_OP* op_return_type;
  SPVM_OP* op_block;
  SPVM_OP* op_package;
  SPVM_OP* op_constant;
  SPVM_LIST* op_args;
  SPVM_LIST* op_mys;
  const char* abs_name;
  const char* file_name;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t call_sub_arg_stack_max;
  int32_t id;
  int32_t eval_stack_max_length;
  int32_t object_var_index_stack_max;
  _Bool is_native;
  _Bool is_enum;
  _Bool is_destructor;
  _Bool is_jit;
  _Bool disable_jit;
  _Bool have_jit_desc;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
