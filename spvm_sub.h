#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

// Method information
struct SPVM_sub {
  SPVM_OP* op_name;
  SPVM_OP* op_return_type;
  SPVM_OP* op_block;
  SPVM_ARRAY* op_args;
  SPVM_ARRAY* op_my_vars;
  void* native_address;
  const char* abs_name;
  const char* file_name;
  int32_t bytecode_base;
  int32_t bytecode_length;
  int32_t operand_stack_max;
  int32_t constant_pool_index;
  int32_t abs_name_constant_pool_index;
  int32_t file_name_constant_pool_index;
  _Bool is_native;
  _Bool is_constant;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
