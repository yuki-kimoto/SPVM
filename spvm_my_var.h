#ifndef SPVM_MY_VAR_H
#define SPVM_MY_VAR_H

#include "spvm_base.h"

struct SPVM_my_var {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  SPVM_OP* op_term_assumption;
  int32_t address;
};

SPVM_MY_VAR* SPVM_MY_VAR_new();

#endif
