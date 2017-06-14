#ifndef SPVM_CONSTANT_POOL_FIELD_H
#define SPVM_CONSTANT_POOL_FIELD_H

#include "spvm_base.h"

// Array
struct SPVM_constant_pool_field {
  int32_t abs_name_constant_pool_index;
  int32_t name_constant_pool_index;
  int32_t index;
};

#endif
