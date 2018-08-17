#ifndef SPVM_SUB_H
#define SPVM_SUB_H

#include "spvm_base.h"

enum {
  SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD,
  SPVM_SUB_C_CALL_TYPE_ID_METHOD,
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
  SPVM_LIST* info_package_var_accesses;
  SPVM_LIST* info_field_accesses;
  SPVM_LIST* info_types;
  SPVM_LIST* info_call_subs;
  SPVM_LIST* info_constants;
  SPVM_LIST* info_switch_infos;
  
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
  _Bool have_native_desc;
  _Bool have_precompile_desc;
  _Bool is_enum;
  _Bool is_destructor;
  _Bool is_compiled;
  _Bool is_core;
  _Bool is_static;
  _Bool is_return_type_object;
};

SPVM_SUB* SPVM_SUB_new(SPVM_COMPILER* compiler);
int32_t SPVM_SUB_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub);
int32_t SPVM_SUB_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_SUB* sub);

#endif
