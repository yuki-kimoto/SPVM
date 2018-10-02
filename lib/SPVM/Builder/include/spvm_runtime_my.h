#ifndef SPVM_RUNTIME_MY_H
#define SPVM_RUNTIME_MY_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_my {
  int32_t var_id;
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  int32_t numeric_var_id;
  int32_t address_var_id;
};

SPVM_RUNTIME_MY* SPVM_RUNTIME_MY_new();

#endif
