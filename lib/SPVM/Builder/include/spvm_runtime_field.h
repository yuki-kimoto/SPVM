#ifndef SPVM_RUNTIME_FIELD_H
#define SPVM_RUNTIME_FIELD_H

#include "spvm_typedecl.h"

struct spvm_runtime_field {
  const char* name;
  const char* signature;
  int32_t id;
  int32_t index;
  int32_t offset;
  int32_t type_id;
};

#endif
