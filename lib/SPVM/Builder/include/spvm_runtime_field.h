// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_FIELD_H
#define SPVM_RUNTIME_FIELD_H

#include "spvm_typedecl.h"

struct spvm_runtime_field {
  int32_t index;
  int32_t offset;
  int32_t name_string_index;
  const char* name;
  int32_t current_basic_type_id;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type;
  int32_t basic_type_id;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  int32_t type_dimension;
  int32_t type_flag;
};

#endif
