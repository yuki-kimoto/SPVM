#ifndef SPVM_BASE_OBJECT_H
#define SPVM_BASE_OBJECT_H

#include "spvm_base.h"

// SPVM_BASE_OBJECT
struct SPVM_base_object {
  int8_t type;
  int32_t ref_count;
  SPVM_ARRAY* weaken_back_refs;
  int32_t weaken_back_refs_count;
};

enum {
  SPVM_BASE_OBJECT_C_TYPE_OBJECT = 0,
  SPVM_BASE_OBJECT_C_TYPE_ARRAY = 1,
};

#endif
