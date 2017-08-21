#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"

// SPVM_OBJECT
struct SPVM_object {
  SPVM_OBJECT* weaken_back_refs;
  int32_t ref_count;
  int32_t weaken_back_refs_length;
  int32_t package_id;
  int32_t length;
  int8_t value_type;
  int8_t is_array;
  int32_t type_code;
  int32_t type_id;
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
