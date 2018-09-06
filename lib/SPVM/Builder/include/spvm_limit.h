#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  // OP code operand max value
  SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX = UINT16_MAX,

  // valut_t field count max
  SPVM_LIMIT_C_VALUE_T_FIELDS_LENGTH_MAX = 16,

  // valut_t field count max
  SPVM_LIMIT_C_STACK_MAX = UINT8_MAX,
};

#endif
