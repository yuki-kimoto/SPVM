// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_METHOD_H
#define SPVM_RUNTIME_METHOD_H

#include "spvm_typedecl.h"

// Runtime method information
struct spvm_runtime_method {
  int32_t index;
  int32_t name_string_index;
  int32_t args_base;
  int32_t args_length;
  int32_t required_args_length;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t current_basic_type_id;
  int32_t call_stack_byte_vars_length;
  int32_t call_stack_short_vars_length;
  int32_t call_stack_int_vars_length;
  int32_t call_stack_long_vars_length;
  int32_t call_stack_float_vars_length;
  int32_t call_stack_double_vars_length;
  int32_t call_stack_object_vars_length;
  int32_t call_stack_ref_vars_length;
  int32_t mortal_stack_length;
  int32_t return_basic_type_id;
  int32_t return_type_dimension;
  int32_t return_type_flag;
  int8_t is_class_method;
  int8_t is_init;
  int8_t is_anon;
  int8_t is_precompile;
  int8_t is_native;
  int8_t is_destructor;
  int8_t is_required;
  int8_t is_enum;
  void* native_address;
  void* precompile_address;
  const char* name;
  SPVM_OPCODE* opcodes;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type;
  SPVM_RUNTIME_BASIC_TYPE* return_basic_type;
};

#endif
