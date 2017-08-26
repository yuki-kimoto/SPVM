#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"
#include "spvm_value.h"

// SPVM_OBJECT
struct SPVM_object {
  union {
    SPVM_OBJECT* weaken_back_refs;
    SPVM_VALUE alignment;
  } uv;
  int32_t type_id;
  int32_t ref_count;
  int32_t weaken_back_refs_length;
  int32_t length;
  int32_t objects_length;
  int8_t element_byte_size;
  int8_t has_destructor;
};

#endif
