// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_CLASS_VAR_H
#define SPVM_RUNTIME_CLASS_VAR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

struct spvm_runtime_class_var {
  int32_t index;
  int32_t name_string_index;
  int32_t current_basic_type_id;
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  SPVM_VALUE data;
  const char* name;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
};

#endif
