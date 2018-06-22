#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  /* Fields count limit */
  SPVM_LIMIT_C_FIELDS = INT32_MAX,

  /* Fields count our */
  SPVM_LIMIT_C_PACKAGE_VARS = INT32_MAX,
  
  /* Lexical variables count limit */
  SPVM_LIMIT_C_MY_VARS = INT32_MAX,

  /* Subroutines count limit */
  SPVM_LIMIT_C_SUBS = INT32_MAX,
  
  /* Resolved types count limit */
  SPVM_LIMIT_C_RESOLVED_TYPES = INT32_MAX, 

  /* Types count limit */
  SPVM_LIMIT_C_TYPES = INT32_MAX, 
  
  /* Case statements count limit */
  SPVM_LIMIT_C_CASES = INT32_MAX,
  
  /* Type dimension limit */
  SPVM_LIMIT_C_DIMENSION = UINT8_MAX,
  
  /* Basic type name length limit */
  SPVM_LIMIT_C_BASIC_TYPE_NAME = INT16_MAX,

  // Package items max
  // Package item is call sub, field access, package variable access, types, constants
  SPVM_LIMIT_C_PACKAGE_ITEMS_MAX = UINT16_MAX,
};

#endif
