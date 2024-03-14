// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VAR_DECL_H
#define SPVM_VAR_DECL_H

#include "spvm_typedecl.h"

struct spvm_var_decl {
  SPVM_OP* op_var_decl;
  SPVM_TYPE* type;
  SPVM_VAR* var;
  SPVM_OP* op_arg_default;
  const char* name;
  int32_t index;
  int32_t runtime_var_index;
  int32_t arg_stack_index;
  int8_t is_arg;
};

SPVM_VAR_DECL* SPVM_VAR_DECL_new();

SPVM_VAR_DECL* SPVM_VAR_DECL_new_arg(SPVM_COMPILER* compiler);

#endif
