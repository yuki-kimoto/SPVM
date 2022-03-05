#ifndef SPVM_RUNTIME_TYPE_H
#define SPVM_RUNTIME_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

struct spvm_runtime_type {
  const char* name;
  SPVM_RUNTIME_BASIC_TYPE* basic_type;
  int32_t dimension;
  int32_t flag;
  int32_t category;
  int32_t width;
};

#endif
