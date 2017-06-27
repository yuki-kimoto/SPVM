#ifndef SPVM_DATA_H
#define SPVM_DATA_H

#include "spvm_base.h"

// SPVM_DATA
struct SPVM_data {
  int8_t type;
  int32_t ref_count;
};

enum {
  SPVM_DATA_C_HEADER_BYTE_SIZE = 32
};

enum {
  SPVM_DATA_C_TYPE_OBJECT = 0,
  SPVM_DATA_C_TYPE_ARRAY = 1,
};

#endif
