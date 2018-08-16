#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_runtime_basic_type {
  const char* name;
  int32_t id;
  int32_t category;
  SPVM_PACKAGE* package;
};

SPVM_RUNTIME_BASIC_TYPE* SPVM_RUNTIME_BASIC_TYPE_new(SPVM_COMPILER* compiler);

#endif
