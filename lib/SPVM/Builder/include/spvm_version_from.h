// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VERSION_FROM_H
#define SPVM_VERSION_FROM_H

#include "spvm_typedecl.h"

struct spvm_version_from {
  SPVM_OP* op_version_from;
  const char* basic_type_name;
};

SPVM_VERSION_FROM* SPVM_VERSION_FROM_new(SPVM_COMPILER* compiler);

#endif
