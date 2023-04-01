// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VAR_H
#define SPVM_VAR_H

#include "spvm_typedecl.h"

struct spvm_var {
  const char* name;
  SPVM_OP* op_name;
  SPVM_VAR_DECL* var_decl;
  int8_t is_declaration;
  int8_t is_initialized;
  SPVM_CALL_METHOD* call_method;
};

SPVM_VAR* SPVM_VAR_new(SPVM_COMPILER* compiler);

#endif
