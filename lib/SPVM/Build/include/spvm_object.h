#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"
#include "spvm_native.h"

enum {
  SPVM_OBJECT_C_CATEGORY_OBJECT,
  SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY,
  SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY,
  SPVM_OBJECT_C_CATEGORY_VALUE_T_ARRAY,
};

// SPVM_OBJECT
struct SPVM_object {
  void* body;
  void** weaken_back_refs;
  int32_t weaken_back_refs_length;
  int32_t weaken_back_refs_capacity;
  int32_t ref_count;
  int32_t basic_type_id;
  int32_t elements_length;
  uint8_t type_dimension;
  uint8_t type_flag;
  uint8_t has_destructor;
  uint8_t in_destroy;
  uint8_t category;
};

#endif
