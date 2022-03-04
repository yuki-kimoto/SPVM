#ifndef SPVM_MY_H
#define SPVM_MY_H

#include "spvm_typedecl.h"

struct spvm_my {
  SPVM_OP* op_my;
  SPVM_TYPE* type;
  SPVM_VAR* var;
  int32_t id;
  int32_t mem_id;
  int8_t is_tmp;
  int8_t is_arg;
  int8_t is_eternal;
};

SPVM_MY* SPVM_MY_new();

SPVM_MY* SPVM_MY_new_eternal(SPVM_COMPILER* compiler);

#endif
