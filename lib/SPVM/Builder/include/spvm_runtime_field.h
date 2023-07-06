// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_FIELD_H
#define SPVM_RUNTIME_FIELD_H

#include "spvm_typedecl.h"

struct spvm_runtime_field {
  const char* name;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  int32_t index;
  int32_t offset;
  int32_t type_dimension;
  int32_t type_flag;
};

#endif
