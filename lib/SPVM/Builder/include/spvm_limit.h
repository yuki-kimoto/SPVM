#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_typedecl.h"

enum {
  // Max count of sub arguments
  SPVM_LIMIT_C_METHOD_ARGS_MAX_COUNT = 255,
  
  // Max count of mulnum fields
  SPVM_LIMIT_C_MULNUM_T_FIELDS_MAX_COUNT = 255,
  
  // mulnum fields count max
  SPVM_LIMIT_C_ARRAY_DIMENSION_MAX_COUNT = 255,
};

#endif
