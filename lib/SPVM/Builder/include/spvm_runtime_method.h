// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_METHOD_H
#define SPVM_RUNTIME_METHOD_H

#include "spvm_typedecl.h"

// Runtime method information
struct spvm_runtime_method {
  void* native_address;
  void* precompile_address;
  const char* name;
  SPVM_OPCODE* opcodes;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type;
  SPVM_RUNTIME_BASIC_TYPE* return_basic_type;
  SPVM_RUNTIME_ARG* args;
  int32_t index;
  int32_t args_length;
  int32_t required_args_length;
  int32_t opcodes_length;
  int32_t byte_vars_width;
  int32_t short_vars_width;
  int32_t int_vars_width;
  int32_t long_vars_width;
  int32_t float_vars_width;
  int32_t double_vars_width;
  int32_t object_vars_width;
  int32_t ref_vars_width;
  int32_t mortal_stack_length;
  int32_t return_type_dimension;
  int32_t return_type_flag;
  int8_t is_class_method;
  int8_t is_enum;
  int8_t is_precompile;
  int8_t is_native;
  int8_t is_init;
  int8_t is_destructor;
  int8_t is_required;
  int8_t is_precompile_fallback;
};

#endif
