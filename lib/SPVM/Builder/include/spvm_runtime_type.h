#ifndef SPVM_RUNTIME_TYPE_H
#define SPVM_RUNTIME_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

struct spvm_runtime_type {
  int32_t id;
  int32_t basic_type_id;
  int32_t dimension;
  int32_t flag;
  int32_t width;
  int32_t mulnum_field_basic_type_id;
};

#endif
