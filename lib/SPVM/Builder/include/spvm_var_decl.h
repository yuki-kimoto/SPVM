// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VAR_DECL_H
#define SPVM_VAR_DECL_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

struct spvm_var_decl {
  SPVM_OP* op_var_decl;
  SPVM_TYPE* type;
  SPVM_VAR* var;
  const char* name;
  SPVM_OP* op_arg_default;
  SPVM_VALUE arg_default_value;
  int32_t index;
  int32_t typed_var_index;
  int32_t stack_index;
  int8_t is_arg;
  int8_t is_optional_arg;
};

SPVM_VAR_DECL* SPVM_VAR_DECL_new(SPVM_COMPILER* compiler);

SPVM_VAR_DECL* SPVM_VAR_DECL_new_arg(SPVM_COMPILER* compiler);

#endif
