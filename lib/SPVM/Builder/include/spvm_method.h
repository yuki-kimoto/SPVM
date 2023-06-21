// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_METHOD_H
#define SPVM_METHOD_H

#include "spvm_typedecl.h"

// Method information
struct spvm_method {
  const char* name;
  SPVM_OP* op_method;
  SPVM_OP* op_name;
  SPVM_OP* op_block;
  SPVM_TYPE* return_type;
  SPVM_LIST* var_decls;
  SPVM_LIST* anon_method_fields;
  const char* abs_name;
  SPVM_BASIC_TYPE* current_basic_type;
  const char* anon_method_defined_basic_type_name;
  int32_t enum_value;
  int32_t args_length;
  int32_t required_args_length;
  int32_t address_id;
  int32_t index;
  int32_t opcodes_base_id;
  int32_t opcodes_length;
  int32_t call_stack_byte_vars_length;
  int32_t call_stack_short_vars_length;
  int32_t call_stack_int_vars_length;
  int32_t call_stack_long_vars_length;
  int32_t call_stack_float_vars_length;
  int32_t call_stack_double_vars_length;
  int32_t call_stack_object_vars_length;
  int32_t call_stack_ref_vars_length;
  int32_t mortal_stack_length;
  int32_t anon_method_id;
  int32_t tmp_vars_length;
  int8_t is_static;
  int8_t is_init;
  int8_t is_destructor;
  int8_t is_enum;
  int8_t is_precompile;
  int8_t is_native;
  int8_t is_anon;
  int8_t is_required;
  int8_t access_control_type;
};

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler);

#endif
