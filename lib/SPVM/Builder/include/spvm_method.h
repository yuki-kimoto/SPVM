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

// Method information
struct spvm_method {
  const char* name;
  const char* signature;
  SPVM_OP* op_method;
  SPVM_OP* op_name;
  SPVM_OP* op_block;
  SPVM_TYPE* return_type;
  SPVM_LIST* mys;
  SPVM_LIST* captures;
  const char* abs_name;
  SPVM_CLASS* class;
  const char* accessor_original_name;
  const char* anon_method_defined_class_name;
  void* precompile_address;
  void* native_address;
  int32_t args_length;
  int32_t id;
  int32_t rel_id;
  int32_t tmp_vars_length;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t flag;
  int32_t call_stack_byte_vars_length;
  int32_t call_stack_short_vars_length;
  int32_t call_stack_int_vars_length;
  int32_t call_stack_long_vars_length;
  int32_t call_stack_float_vars_length;
  int32_t call_stack_double_vars_length;
  int32_t call_stack_object_vars_length;
  int32_t call_stack_ref_vars_length;
  int32_t anon_method_id;
  int8_t have_vaarg;
  int8_t is_class_var_setter;
  int8_t is_class_var_getter;
  int8_t is_field_setter;
  int8_t is_field_getter;
  int8_t is_simple_constructor;
  int8_t is_constant;
  int8_t can_precompile;
  int8_t is_class_method;
  int8_t is_init;
  int32_t mortal_stack_length;
  SPVM_OP* op_inline;
};

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler);

#endif
