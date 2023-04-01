// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_FIELD_H
#define SPVM_FIELD_H

#include "spvm_typedecl.h"

struct spvm_field {
  SPVM_OP* op_field;
  SPVM_OP* op_name;
  const char* name;
  SPVM_TYPE* type;
  SPVM_CLASS* class;
  int32_t id;
  int32_t index;
  int32_t offset;
  int8_t is_captured;
  int8_t has_setter;
  int8_t has_getter;
  int8_t access_control_type;
};

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler);

#endif
