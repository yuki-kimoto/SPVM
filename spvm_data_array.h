#ifndef SPVM_DATA_ARRAY_H
#define SPVM_DATA_ARRAY_H

#include "spvm_base.h"

// SPVM_DATA_ARRAY
struct SPVM_data_array {
  int8_t type;
  int8_t value_type;
  int32_t ref_count;
  int32_t length;
};

enum {
  SPVM_DATA_ARRAY_C_VALUE_TYPE_BYTE = 0,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_SHORT = 1,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_INT = 2,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_LONG = 3,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_FLOAT = 4,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_DOUBLE = 5,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_REF = 6,
};

#endif
