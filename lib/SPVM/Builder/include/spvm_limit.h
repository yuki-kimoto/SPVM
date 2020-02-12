#ifndef SPVM_LIMIT_H
#define SPVM_LIMIT_H

#include "spvm_base.h"

enum {
  // Sub arguments max count
  SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT = 256,

  // mulnum fields count max
  SPVM_LIMIT_C_VALUE_FIELDS_MAX_COUNT = 256,

  // mulnum fields count min
  SPVM_LIMIT_C_VALUE_FIELDS_MIN_COUNT = 1,
};

#endif
