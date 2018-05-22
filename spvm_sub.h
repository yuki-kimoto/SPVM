#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

enum {
  SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD,
  SPVM_SUB_C_CALL_TYPE_ID_METHOD,
};

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
  SPVM_LIST* object_arg_ids;
  SPVM_LIST* op_mys;
  const char* abs_name;
  const char* file_name;
  const char* method_signature;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t call_sub_arg_stack_max;
  int32_t id;
  int32_t eval_stack_max_length;
  int32_t mortal_stack_max;
  int8_t call_type_id;
  _Bool is_native;
  _Bool is_enum;
  _Bool is_destructor;
  _Bool is_jit_compiled;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);

#endif
