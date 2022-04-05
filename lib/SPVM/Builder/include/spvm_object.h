#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

// SPVM_OBJECT
struct spvm_object {
  SPVM_WEAKEN_BACKREF* weaken_backref_head;
  int32_t ref_count;
  int32_t basic_type_id;
  uint8_t type_dimension;
  uint8_t flag;
  int32_t length;
};

enum {
  SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR = 1,
  SPVM_OBJECT_C_FLAG_IS_READ_ONLY = 2,
};

#endif
