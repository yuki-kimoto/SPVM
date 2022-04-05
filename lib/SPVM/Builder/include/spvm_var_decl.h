#ifndef SPVM_VAR_DECL_H
#define SPVM_VAR_DECL_H

#include "spvm_typedecl.h"

struct spvm_var_decl {
  SPVM_OP* op_var_decl;
  SPVM_TYPE* type;
  SPVM_VAR* var;
  int32_t id;
  int32_t mem_id;
  int32_t arg_id;
  int8_t is_tmp;
  int8_t is_arg;
  int8_t is_eternal;
};

SPVM_VAR_DECL* SPVM_VAR_DECL_new();

SPVM_VAR_DECL* SPVM_VAR_DECL_new_eternal(SPVM_COMPILER* compiler);

#endif
