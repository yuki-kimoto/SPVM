#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"

// SPVM_OBJECT
struct SPVM_object {
  SPVM_OBJECT* weaken_back_refs;
  int32_t type_id;
  int32_t ref_count;
  int32_t weaken_back_refs_length;
  int32_t dimension;
  int32_t length;
  int32_t objects_length;
  int8_t element_byte_size;
};

#endif
