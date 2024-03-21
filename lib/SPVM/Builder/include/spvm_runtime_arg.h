// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_ARG_H
#define SPVM_RUNTIME_ARG_H

#include "spvm_typedecl.h"

struct spvm_runtime_arg {
  const char* name;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  SPVM_RUNTIME_METHOD* current_method;
  int32_t index;
  int32_t type_dimension;
  int32_t type_flag;
  int32_t stack_index;
};

#endif
