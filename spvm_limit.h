#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  /* Type dimension limit */
  SPVM_LIMIT_C_DIMENSION = UINT8_MAX,
  
  /* Basic type name length limit */
  SPVM_LIMIT_C_BASIC_TYPE_NAME = INT16_MAX,

  // Package items max
  // Package item is call sub, field access, package variable access, types, constants
  SPVM_LIMIT_C_PACKAGE_ITEMS_MAX = UINT16_MAX,
};

#endif
