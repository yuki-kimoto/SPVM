#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_typedef.h"

struct SPVM_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_OP* op_name;
  int32_t id;
  int32_t mem_id;
  int32_t type_category;
  int32_t type_width;
  int8_t is_tmp;
};

SPVM_MY* SPVM_MY_new();

#endif
