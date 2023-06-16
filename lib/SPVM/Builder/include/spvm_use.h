// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_typedecl.h"

struct spvm_use {
  SPVM_OP* op_use;
  const char* basic_type_name;
  const char* alias_name;
  const char* file;
  int8_t is_require;
};

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler);

#endif
