#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_OP* op_name;
  uint16_t index;
  uint16_t var_id;
  uint8_t runtime_type;
  uint8_t value_field_basic_type_id;
  uint8_t type_width;
  uint8_t is_tmp;
};

SPVM_MY* SPVM_MY_new();

#endif
