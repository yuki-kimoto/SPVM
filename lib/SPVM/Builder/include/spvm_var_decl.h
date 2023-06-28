// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VAR_DECL_H
#define SPVM_VAR_DECL_H

#include "spvm_typedecl.h"

struct spvm_var_decl {
  SPVM_OP* op_var_decl;
  SPVM_TYPE* type;
  SPVM_VAR* var;
  SPVM_OP* op_optional_arg_default;
  int32_t index;
  int32_t call_stack_id;
  int8_t is_arg;
  int8_t is_permanent;
};

SPVM_VAR_DECL* SPVM_VAR_DECL_new();

SPVM_VAR_DECL* SPVM_VAR_DECL_new_eternal(SPVM_COMPILER* compiler);

#endif
