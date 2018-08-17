#ifndef SPVM_RUNTIME_FIELD_H
#define SPVM_RUNTIME_FIELD_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_field {
  int32_t id;
  int32_t index;
  int32_t flag;
  const char* name;
  const char* abs_name;
  const char* signature;
  SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type;
  int32_t type_dimension;
  int32_t type_flag;
  SPVM_PACKAGE* package;
};

SPVM_RUNTIME_FIELD* SPVM_RUNTIME_FIELD_new();

#endif
