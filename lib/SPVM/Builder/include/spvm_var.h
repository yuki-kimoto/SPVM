#ifndef SPVM_VAR_H
#define SPVM_VAR_H

#include "spvm_typedecl.h"

struct spvm_var {
  SPVM_OP* op_name;
  SPVM_MY* my;
  int8_t is_declaration;
  int8_t is_outer;
  int8_t is_arg;
  int8_t is_initialized;
  SPVM_CALL_SUB* call_sub;
};

SPVM_VAR* SPVM_VAR_new(SPVM_COMPILER* compiler);

#endif
