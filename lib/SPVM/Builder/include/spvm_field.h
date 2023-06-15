// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_FIELD_H
#define SPVM_FIELD_H

#include "spvm_typedecl.h"

struct spvm_field {
  SPVM_OP* op_field;
  SPVM_OP* op_name;
  SPVM_OP* op_anon_method_field_default;
  const char* name;
  SPVM_TYPE* type;
  SPVM_BASIC_TYPE* class_basic_type;
  int32_t id;
  int32_t index;
  int32_t offset;
  int8_t is_anon_method_field;
  int8_t has_setter;
  int8_t has_getter;
  int8_t access_control_type;
};

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler);

#endif
