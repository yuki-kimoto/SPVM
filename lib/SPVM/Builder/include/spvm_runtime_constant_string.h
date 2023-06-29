// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_CONSTANT_STRING_H
#define SPVM_RUNTIME_CONSTANT_STRING_H

#include "spvm_typedecl.h"

struct spvm_runtime_constant_string {
  const char* value;
  int32_t length;
  int32_t global_address_id;
  int32_t address_id;
  int32_t index;
  int32_t string_pool_address_id;
  int32_t string_pool_index;
};

#endif
