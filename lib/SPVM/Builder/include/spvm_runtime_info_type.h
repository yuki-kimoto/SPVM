#ifndef SPVM_RUNTIME_INFO_TYPE_H
#define SPVM_RUNTIME_INFO_TYPE_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_info_type {
  int32_t basic_type_id;
  uint16_t dimension;
  uint16_t flag;
};

SPVM_RUNTIME_INFO_TYPE* SPVM_RUNTIME_INFO_TYPE_new();

#endif
