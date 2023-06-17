// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_INTERFACE_H
#define SPVM_INTERFACE_H

#include "spvm_typedecl.h"

struct spvm_interface {
  SPVM_OP* op_interface;
  SPVM_OP* op_type;
};

SPVM_INTERFACE* SPVM_INTERFACE_new(SPVM_COMPILER* compiler);

#endif
