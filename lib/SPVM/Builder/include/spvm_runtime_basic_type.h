#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include "spvm_typedecl.h"

struct spvm_runtime_basic_type {
  const char* name;
  SPVM_RUNTIME_CLASS* class;
  int32_t id;
};

#endif
