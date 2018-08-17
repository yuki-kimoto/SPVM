#ifndef SPVM_RUNTIME_PACKAGE_VAR_H
#define SPVM_RUNTIME_PACKAGE_VAR_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package_var {
  int32_t id;
  int32_t rel_id;
  const char* name;
  const char* abs_name;
  const char* signature;
  SPVM_PACKAGE* package;
  SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type;
  int32_t type_dimension;
  int32_t type_flag;
};

SPVM_RUNTIME_PACKAGE_VAR* SPVM_RUNTIME_PACKAGE_VAR_new(SPVM_COMPILER* compiler);

#endif
