#ifndef SPVM_RUNTIME_MY_H
#define SPVM_RUNTIME_MY_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_my {
  int32_t basic_type_id;
  uint16_t var_id;
  uint16_t type_flag;
  uint8_t type_dimension;
  uint8_t value_field_basic_type_id;
};

SPVM_RUNTIME_MY* SPVM_RUNTIME_MY_new();

#endif
