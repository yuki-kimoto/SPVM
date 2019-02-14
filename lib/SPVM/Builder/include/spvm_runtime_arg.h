#ifndef SPVM_RUNTIME_ARG_H
#define SPVM_RUNTIME_ARG_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_arg {
  int32_t basic_type_id;
  uint16_t mem_id;
  uint16_t type_flag;
  uint8_t type_dimension;
  uint8_t runtime_type;
  uint8_t type_width;
};

SPVM_RUNTIME_ARG* SPVM_RUNTIME_ARG_new();

#endif
