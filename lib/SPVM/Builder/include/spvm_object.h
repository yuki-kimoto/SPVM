#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"
#include "spvm_native.h"

// SPVM_OBJECT
struct SPVM_object {
  SPVM_WEAKEN_BACKREF* weaken_backref_head;
  int32_t ref_count;
  int32_t basic_type_id;
  uint8_t type_dimension;
  uint8_t type_category;
  uint8_t flag;
  int32_t length;
};

enum {
  SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR = 1,
  SPVM_OBJECT_C_FLAG_STRING_IS_CONSTANT = 2,
  SPVM_OBJECT_C_FLAG_STRING_IS_SHORT = 4,
  SPVM_OBJECT_C_FLAG_STRING_IS_UTF8 = 8,
};

#endif
