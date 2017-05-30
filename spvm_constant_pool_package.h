#ifndef SPVM_CONSTANT_POOL_PACKAGE_H
#define SPVM_CONSTANT_POOL_PACKAGE_H

#include "spvm_base.h"

// Array
struct SPVM_constant_pool_package {
  SPVM_VALUE* free_need_field_offsets_pool_address;
  int32_t name_constant_pool_address;
  int32_t byte_size;
  int32_t free_need_field_offsets_length;
  int32_t ref_fields_count;
};

#endif
