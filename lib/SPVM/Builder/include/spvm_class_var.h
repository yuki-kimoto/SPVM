// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CLASS_VAR_H
#define SPVM_CLASS_VAR_H

#include "spvm_typedecl.h"

struct spvm_class_var {
  const char* name;
  SPVM_TYPE* type;
  SPVM_BASIC_TYPE* current_basic_type;
  SPVM_OP* op_class_var;
  SPVM_OP* op_name;
  int32_t address_id;
  int32_t index;
  int8_t has_setter;
  int8_t has_getter;
  int8_t access_control_type;
};

SPVM_CLASS_VAR* SPVM_CLASS_VAR_new(SPVM_COMPILER* compiler);

#endif
