#ifndef SPVM_PACKAGE_VAR_ACCESS_H
#define SPVM_PACKAGE_VAR_ACCESS_H

#include "spvm_base.h"

struct SPVM_package_var_access {
  SPVM_OP* op_name;
  SPVM_OP* op_package_var;
  int32_t sub_rel_id;
};

SPVM_PACKAGE_VAR_ACCESS* SPVM_PACKAGE_VAR_ACCESS_new(SPVM_COMPILER* compiler);

#endif
