#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_OP* op_name;
  int32_t index;
  int32_t is_tmp;
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

SPVM_MY* SPVM_MY_new();

#endif
