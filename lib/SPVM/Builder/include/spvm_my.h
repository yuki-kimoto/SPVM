#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_OP* op_name;
  int32_t var_id;
  int32_t numeric_var_id;
  int32_t address_var_id;
};

SPVM_MY* SPVM_MY_new();

#endif
