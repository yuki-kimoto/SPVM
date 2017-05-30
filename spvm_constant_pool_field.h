#ifndef SPVM_CONSTANT_POOL_FIELD_H
#define SPVM_CONSTANT_POOL_FIELD_H

#include "spvm_base.h"

// Array
struct SPVM_constant_pool_field {
  int32_t abs_name_constant_pool_address;
  int32_t package_byte_offset;
};

#endif
