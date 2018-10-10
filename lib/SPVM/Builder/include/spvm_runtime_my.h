#ifndef SPVM_RUNTIME_MY_H
#define SPVM_RUNTIME_MY_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_my {
  int32_t basic_type_id;
  int32_t type_dimension;
  int32_t type_flag;
  int32_t byte_var_id;
  int32_t short_var_id;
  int32_t int_var_id;
  int32_t long_var_id;
  int32_t float_var_id;
  int32_t double_var_id;
  int32_t object_var_id;
  int32_t ref_var_id;
  int32_t value_field_basic_type_id;
};

SPVM_RUNTIME_MY* SPVM_RUNTIME_MY_new();

#endif
