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
  SPVM_DYNAMIC_ARRAY* op_args;
  SPVM_DYNAMIC_ARRAY* op_mys;
  void* native_address;
  const char* abs_name;
  const char* file_name;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t call_sub_arg_stack_max;
  int32_t id;
  int32_t eval_stack_max_length;
  _Bool is_native;
  _Bool is_constant;
  _Bool is_destructor;
  _Bool is_jit;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
