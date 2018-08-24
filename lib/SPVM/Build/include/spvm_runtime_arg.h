#ifndef SPVM_RUNTIME_ARG_H
#define SPVM_RUNTIME_ARG_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_arg {
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  int32_t var_id;
};

SPVM_RUNTIME_ARG* SPVM_RUNTIME_ARG_new();

#endif
