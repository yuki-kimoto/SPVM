#ifndef SPVM_METHOD_H
#define SPVM_METHOD_H

#include "spvm_typedecl.h"

enum {
  SPVM_METHOD_C_CALL_TYPE_ID_STATIC_METHOD,
  SPVM_METHOD_C_CALL_TYPE_ID_INSTANCE_METHOD,
};

enum {
  SPVM_METHOD_C_FLAG_NATIVE = 1,
  SPVM_METHOD_C_FLAG_PRECOMPILE = 2,
  SPVM_METHOD_C_FLAG_ENUM = 4,
  SPVM_METHOD_C_FLAG_DESTRUCTOR = 8,
  SPVM_METHOD_C_FLAG_OBJECT_TYPE_RETURN = 16,
  SPVM_METHOD_C_FLAG_MULTI_NUMERIC_TYPE_RETURN = 32,
  SPVM_METHOD_C_FLAG_ANON = 64,
  SPVM_METHOD_C_FLAG_PRIVATE = 128,
};

// Method information
struct spvm_method {
  SPVM_OP* op_method;
  SPVM_OP* op_name;
  SPVM_OP* op_block;
  SPVM_OP* op_inline;
  SPVM_LIST* object_arg_ids;
  SPVM_LIST* mys;
  SPVM_LIST* captures;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t call_spvm_method_arg_stack_max;
  int32_t rel_id;
  int32_t eval_stack_max_length;
  int32_t mortal_stack_length;
  int32_t call_type_id;
  int32_t id;
  void* precompile_address;
  void* native_address;
  SPVM_TYPE* return_type;
  SPVM_LIST* args;
  const char* name;
  const char* signature;
  SPVM_CLASS* class;
  int32_t flag;
  int32_t args_alloc_length;
  int32_t vars_alloc_length;
  int32_t byte_vars_alloc_length;
  int32_t short_vars_alloc_length;
  int32_t int_vars_alloc_length;
  int32_t long_vars_alloc_length;
  int32_t float_vars_alloc_length;
  int32_t double_vars_alloc_length;
  int32_t object_vars_alloc_length;
  int32_t ref_vars_alloc_length;
  int32_t return_type_category;
  int8_t have_vaarg;
  int8_t is_class_var_setter;
  int8_t is_class_var_getter;
  int8_t is_field_setter;
  int8_t is_field_getter;
  int8_t is_simple_constructor;
  int8_t is_constant;
  int8_t is_begin;
  int8_t is_class_method;
  const char* accessor_original_name;
  SPVM_OP* op_list_tmp_mys;
  int32_t tmp_vars_length;
  SPVM_OP* op_my_condition_flag;
  int32_t can_precompile;
  const char* anon_method_defined_class_name;
};

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler);
int32_t SPVM_METHOD_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method);
int32_t SPVM_METHOD_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method);

#endif
