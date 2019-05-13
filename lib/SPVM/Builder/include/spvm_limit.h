#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  // Sub max count in a package
  SPVM_LIMIT_C_SUBS_MAX_COUNT = UINT16_MAX,

  // Fields max count in a package
  SPVM_LIMIT_C_FIELDS_MAX_COUNT = UINT16_MAX,

  // Package variables max count in a package
  SPVM_LIMIT_C_PACKAGE_VARS_MAX_COUNT = UINT16_MAX,

  // Switch statements max count in a package
  SPVM_LIMIT_C_SWITCHES_MAX_COUNT = UINT16_MAX,

  // Line max count in a sub
  SPVM_LIMIT_C_LINES_MAX_COUNT = UINT16_MAX,

  // Opcodes max count in a subroutine
  SPVM_LIMIT_C_OPCODES_MAX_COUNT = UINT16_MAX,
  
  // Sub arguments max count
  SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT = UINT8_MAX,

  // valut_t field count max
  SPVM_LIMIT_C_VALUE_T_FIELDS_MAX_COUNT = 16,
};

#endif
