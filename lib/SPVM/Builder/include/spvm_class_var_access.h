// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CLASS_VAR_ACCESS_H
#define SPVM_CLASS_VAR_ACCESS_H

#include "spvm_typedecl.h"

struct spvm_class_var_access {
  SPVM_OP* op_name;
  SPVM_CLASS_VAR* class_var;
};

SPVM_CLASS_VAR_ACCESS* SPVM_CLASS_VAR_ACCESS_new(SPVM_COMPILER* compiler);

#endif
