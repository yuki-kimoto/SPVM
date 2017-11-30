#ifndef SPVM_OPCODE_H
#define SPVM_OPCODE_H

#include "spvm_base.h"

struct SPVM_opcode {
  int32_t code;
  int32_t operand0;
  int32_t operand1;
  int32_t operand2;
  int32_t jit_operand0;
  int32_t jit_operand1;
  int32_t jit_operand2;
  int32_t dummy;
};

SPVM_OPCODE* SPVM_OPCODE_new();

#endif
