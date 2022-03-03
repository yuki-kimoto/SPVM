#ifndef SPVM_METHOD_H
#define SPVM_METHOD_H

#include "spvm_typedecl.h"

enum {
  SPVM_METHOD_C_CALL_TYPE_ID_CLASS_METHOD,
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

enum {
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_VOID,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_BYTE,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_SHORT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_INT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_LONG,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_FLOAT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_DOUBLE,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_OBJECT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_BYTE,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_SHORT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_INT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_LONG,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_FLOAT,
  SPVM_METHOD_C_RETURN_TYPE_CATEGORY_ID_MULNUM_DOUBLE,
};

// Method information
struct spvm_method {
  SPVM_OP* op_method;
  SPVM_OP* op_name;
  SPVM_OP* op_block;
  SPVM_OP* op_inline;
  SPVM_OP* op_list_tmp_mys;
  SPVM_OP* op_my_condition_flag;
  SPVM_LIST* object_arg_ids;
  SPVM_LIST* mys;
  SPVM_LIST* captures;
  void* precompile_address;
  void* native_address;
  SPVM_TYPE* return_type;
  SPVM_LIST* args;
  SPVM_LIST* arg_types;
  const char* name;
  const char* abs_name;
  const char* signature;
  SPVM_CLASS* class;
  const char* accessor_original_name;
  const char* anon_method_defined_class_name;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t call_method_arg_stack_max;
  int32_t rel_id;
  int32_t eval_stack_max_length;
  int32_t mortal_stack_length;
  int32_t id;
  int32_t return_type_category_id;
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
  int32_t tmp_vars_length;
  int8_t have_vaarg;
  int8_t is_class_var_setter;
  int8_t is_class_var_getter;
  int8_t is_field_setter;
  int8_t is_field_getter;
  int8_t is_simple_constructor;
  int8_t is_constant;
  int8_t is_init;
  int8_t is_class_method;
  int8_t can_precompile;
};

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler);
int32_t SPVM_METHOD_get_var_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method);
int32_t SPVM_METHOD_get_arg_alloc_length(SPVM_COMPILER* compiler, SPVM_METHOD* method);

#endif
