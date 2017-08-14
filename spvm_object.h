#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"

// SPVM_OBJECT
struct SPVM_object {
  SPVM_OBJECT* weaken_back_refs;
  int32_t ref_count;
  int32_t weaken_back_refs_length;
  int32_t package_constant_pool_index;
  int32_t length;
  int32_t object_length;
  int8_t type;
  int8_t value_type;
};

enum {
  SPVM_OBJECT_C_TYPE_OBJECT = 0,
  SPVM_OBJECT_C_TYPE_ARRAY = 1,
};

enum {
  SPVM_OBJECT_C_VALUE_TYPE_BYTE,
  SPVM_OBJECT_C_VALUE_TYPE_SHORT,
  SPVM_OBJECT_C_VALUE_TYPE_INT,
  SPVM_OBJECT_C_VALUE_TYPE_LONG,
  SPVM_OBJECT_C_VALUE_TYPE_FLOAT,
  SPVM_OBJECT_C_VALUE_TYPE_DOUBLE,
  SPVM_OBJECT_C_VALUE_TYPE_OBJECT,
};

#endif
