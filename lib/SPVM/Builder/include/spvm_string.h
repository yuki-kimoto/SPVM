// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_STRING_H
#define SPVM_STRING_H

#include "spvm_typedecl.h"

struct spvm_string {
  const char* value;
  int32_t length;
  int32_t index;
  int32_t string_pool_index;
};

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length);

#endif
