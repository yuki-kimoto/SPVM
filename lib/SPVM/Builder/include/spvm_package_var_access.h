#ifndef SPVM_PACKAGE_VAR_ACCESS_H
#define SPVM_PACKAGE_VAR_ACCESS_H

#include "spvm_typedef.h"

struct SPVM_package_var_access {
  SPVM_OP* op_name;
  SPVM_PACKAGE_VAR* package_var;
  int32_t constant_pool_id;
  int32_t inline_expansion;
};

SPVM_PACKAGE_VAR_ACCESS* SPVM_PACKAGE_VAR_ACCESS_new(SPVM_COMPILER* compiler);

#endif
