#ifndef SPVM_RUNTIME_INFO_CONSTANT_H
#define SPVM_RUNTIME_INFO_CONSTANT_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_info_constant {
  int32_t id;
  SPVM_VALUE value;
};

SPVM_RUNTIME_INFO_CONSTANT* SPVM_RUNTIME_INFO_CONSTANT_new();

#endif
