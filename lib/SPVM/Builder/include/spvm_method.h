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
  const char* outmost_basic_type_name;
  const char* args_signature;
  int32_t enum_value;
  int32_t args_length;
  int32_t required_args_length;
  int32_t index;
  SPVM_OPCODE_LIST* opcode_list;
  int32_t byte_vars_width;
  int32_t short_vars_width;
  int32_t int_vars_width;
  int32_t long_vars_width;
  int32_t float_vars_width;
  int32_t double_vars_width;
  int32_t object_vars_width;
  int32_t ref_vars_width;
  int32_t mortal_stack_length;
  int32_t mortal_stack_tops_length;
  int32_t tmp_vars_length;
  int8_t is_class_method;
  int8_t is_init_method;
  int8_t is_end_method;
  int8_t is_destroy_method;
  int8_t is_enum;
  int8_t is_precompile;
  int8_t is_native;
  int8_t is_required;
  int8_t access_control_type;
  SPVM_OP* op_anon_method_field_var_decl_start;
};

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler);

#endif
