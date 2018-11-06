#ifndef SPVM_RUNTIME_PACKAGE_VAR_H
#define SPVM_RUNTIME_PACKAGE_VAR_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package_var {
  int32_t id;
  int32_t name_id;
  int32_t signature_id;
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  int32_t package_id;
};

SPVM_RUNTIME_PACKAGE_VAR* SPVM_RUNTIME_PACKAGE_VAR_new();

#endif
