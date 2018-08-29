#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

enum {
  SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD,
  SPVM_SUB_C_CALL_TYPE_ID_METHOD,
};

enum {
  SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC = 1,
  SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC = 2,
  SPVM_SUB_C_FLAG_IS_ENUM = 4,
  SPVM_SUB_C_FLAG_IS_DESTRUCTOR = 8,
  SPVM_SUB_C_FLAG_IS_COMPILED = 16,
  SPVM_SUB_C_FLAG_IS_CORE = 32,
  SPVM_SUB_C_FLAG_IS_STATIC = 64, 
  SPVM_SUB_C_FLAG_IS_RETURN_OBJECT_TYPE = 128,
  SPVM_SUB_C_FLAG_IS_RETURN_VALUE_TYPE = 256,
};

// Method information
struct SPVM_sub {
  SPVM_OP* op_sub;
  SPVM_OP* op_name;
  SPVM_OP* op_block;
  SPVM_OP* op_constant;
  SPVM_LIST* object_arg_ids;
  SPVM_LIST* mys;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t call_sub_arg_stack_max;
  int32_t rel_id;
  int32_t eval_stack_max_length;
  int32_t mortal_stack_length;
  int8_t call_type_id;
  
  SPVM_LIST* info_package_var_ids;
  SPVM_LIST* info_sub_ids;
  SPVM_LIST* info_field_ids;
  SPVM_LIST* info_types;
  SPVM_LIST* info_constants;
  SPVM_LIST* info_switch_infos;
  SPVM_LIST* info_long_constants;
  SPVM_LIST* info_string_constants;
  
  int32_t id;
  void* precompile_address;
  void* native_address;
  SPVM_TYPE* return_type;
  SPVM_LIST* args;
  const char* file;
  int32_t line;
  const char* name;
  const char* abs_name;
  const char* signature;
  SPVM_PACKAGE* package;
  int32_t flag;
  int32_t args_alloc_length;
  int32_t vars_alloc_length;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);
int32_t SPVM_SUB_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub);
int32_t SPVM_SUB_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub);

#endif
