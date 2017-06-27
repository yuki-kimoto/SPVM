#ifndef SPVM_DATA_OBJECT_H
#define SPVM_DATA_OBJECT_H

#include "spvm_base.h"

// SPVM_DATA_OBJECT
struct SPVM_data_object {
  int8_t type;
  int32_t ref_count;
  int32_t package_constant_pool_index;
  int32_t field_name_indexes_constant_pool_index;
};

#endif
