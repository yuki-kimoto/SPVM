#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"

// SPVM_OBJECT
struct SPVM_object {
  int8_t type;
  int32_t ref_count;
  int32_t package_constant_pool_index;
  SPVM_ARRAY* weaken_back_refs;
};

#endif
