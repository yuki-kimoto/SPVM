#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_base.h"

struct SPVM_my {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  int32_t index;
  int32_t width;
  SPVM_OP* op_term_type_inference;
  _Bool try_type_inference;
  _Bool is_arg;
};

SPVM_MY* SPVM_MY_new();

#endif
