// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_STRING_H
#define SPVM_RUNTIME_STRING_H

#include "spvm_typedecl.h"

struct spvm_runtime_string {
  const char* value;
  int32_t length;
};

#endif
