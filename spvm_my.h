#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  int32_t index;
};

SPVM_MY* SPVM_MY_new();

#endif
