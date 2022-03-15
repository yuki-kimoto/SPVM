#ifndef SPVM_RUNTIME_TYPE_H
#define SPVM_RUNTIME_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

struct spvm_runtime_type {
  const char* name;
  int32_t id;
  int32_t name_id;
  int32_t basic_type_id;
  int32_t dimension;
  int32_t flag;
  int32_t category;
  int32_t width;
};

#endif
