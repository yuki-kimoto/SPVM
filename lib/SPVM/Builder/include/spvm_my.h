#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_OP* op_name;
  int32_t index;
  int32_t var_id;
  int32_t runtime_type;
  int32_t type_width;
  int8_t is_tmp;
  int8_t is_used;
};

SPVM_MY* SPVM_MY_new();

#endif
