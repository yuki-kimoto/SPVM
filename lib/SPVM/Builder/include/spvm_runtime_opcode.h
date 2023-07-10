// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_OPCODE_H
#define SPVM_RUNTIME_OPCODE_H

#include "spvm_typedecl.h"

struct spvm_opcode {
  uint16_t id;
  uint16_t operand3;
  uint32_t operand0;
  uint32_t operand1;
  uint32_t operand2;
};

#endif
