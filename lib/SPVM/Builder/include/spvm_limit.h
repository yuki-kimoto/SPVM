#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  // OP code operand max value(65535)
  SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX = UINT16_MAX,
  
  // Sub max count in a package
  SPVM_LIMIT_C_SUBS_MAX_COUNT = UINT16_MAX,

  // Fields max count in a package
  SPVM_LIMIT_C_FIELDS_MAX_COUNT = UINT16_MAX,

  // Package variables max count in a package
  SPVM_LIMIT_C_PACKAGE_VARS_MAX_COUNT = UINT16_MAX,

  // Line max count in a sub
  SPVM_LIMIT_C_LINES_MAX_COUNT = UINT16_MAX,
  
  // Sub arguments max count
  SPVM_LIMIT_C_SUB_ARGS_MAX = UINT8_MAX,

  // valut_t field count max
  SPVM_LIMIT_C_VALUE_T_FIELDS_LENGTH_MAX = 16,

  // valut_t field count max
  SPVM_LIMIT_C_STACK_MAX = UINT8_MAX,
};

#endif
