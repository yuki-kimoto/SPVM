#ifndef SPVM_REF_OBJECT_H
#define SPVM_REF_OBJECT_H

#include "spvm_value.h"
#include "spvm_base.h"

struct SPVM_ref_object {
  int32_t ref_count;
  int8_t type;
  int32_t package_constant_pool_address;
};

#endif
