#ifndef SPVM_ARRAY_H
#define SPVM_ARRAY_H

#include "spvm_base.h"

// SPVM_ARRAY
struct SPVM_array {
  int8_t type;
  int8_t value_type;
  int32_t ref_count;
  SPVM_ARRAY* weaken_back_refs;
  int32_t weaken_back_refs_count;
  int32_t length;
};

enum {
  SPVM_ARRAY_C_VALUE_TYPE_BYTE,
  SPVM_ARRAY_C_VALUE_TYPE_SHORT,
  SPVM_ARRAY_C_VALUE_TYPE_INT,
  SPVM_ARRAY_C_VALUE_TYPE_LONG,
  SPVM_ARRAY_C_VALUE_TYPE_FLOAT,
  SPVM_ARRAY_C_VALUE_TYPE_DOUBLE,
  SPVM_ARRAY_C_VALUE_TYPE_OBJECT,
};

#endif
