#ifndef SPVM_VAR_H
#define SPVM_VAR_H

#include "spvm_base.h"

struct SPVM_var {
  SPVM_OP* op_name;
  SPVM_OP* op_my_var;
};

SPVM_VAR* SPVM_VAR_new(SPVM_* spvm);

#endif
