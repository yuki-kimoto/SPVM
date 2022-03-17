#ifndef SPVM_ARG_H
#define SPVM_ARG_H

#include "spvm_typedecl.h"

struct spvm_arg {
  SPVM_OP* op_arg;
  SPVM_VAR* var;
  SPVM_TYPE* type;
  int32_t type_id;
};

SPVM_ARG* SPVM_ARG_new();

#endif
