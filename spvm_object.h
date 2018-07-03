#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"
#include "spvm_native.h"

enum {
  SPVM_OBJECT_C_CATEGORY_OBJECT,
  SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY,
  SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY,
};

// SPVM_OBJECT
struct SPVM_object {
  // This is dummy data. SPVM max data size is sizeof(SPVM_VALUE)
  // In SPVM, data is placed after SPVM_OBJECT, by this dummy, allignment is adjust
  SPVM_VALUE dummy;
  void** weaken_back_refs;
  int32_t weaken_back_refs_length;
  int32_t weaken_back_refs_capacity;
  int32_t ref_count;
  int32_t basic_type_id;
  int32_t elements_length;
  uint16_t element_byte_size;
  uint16_t dimension;
  unsigned has_destructor : 1;
  unsigned in_destroy : 1;
  unsigned category : 3;
};

#endif
