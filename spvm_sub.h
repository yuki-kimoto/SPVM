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
  SPVM_DYNAMIC_ARRAY* op_my_vars;
  void* native_address;
  const char* abs_name;
  const char* file_name;
  int32_t bytecode_base;
  int32_t bytecode_length;
  int32_t operand_stack_max;
  int32_t id;
  _Bool is_native;
  _Bool is_constant;
  _Bool is_destructor;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
