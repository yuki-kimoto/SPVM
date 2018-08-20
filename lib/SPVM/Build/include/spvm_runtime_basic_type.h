#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_runtime_basic_type {
  const char* name;
  int32_t id;
  int32_t category;
  int32_t package_id;
};

SPVM_RUNTIME_BASIC_TYPE* SPVM_RUNTIME_BASIC_TYPE_new();

#endif
