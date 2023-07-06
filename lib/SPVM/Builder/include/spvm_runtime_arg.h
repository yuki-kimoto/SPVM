// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_ARG_H
#define SPVM_RUNTIME_ARG_H

#include "spvm_typedecl.h"

struct spvm_runtime_arg {
  int32_t index;
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
};

#endif
