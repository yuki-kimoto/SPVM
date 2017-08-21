#ifndef SPVM_CONSTANT_POOL_TYPE_H
#define SPVM_CONSTANT_POOL_TYPE_H

#include "spvm_base.h"

// SPVM_CONSTANT_POOL_TYPE
struct SPVM_constant_pool_type {
  int32_t code;
  int32_t name_id;
  int32_t element_type_code;
  int32_t package_id;
  _Bool is_array;
  _Bool is_package;
};

#endif
