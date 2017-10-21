#ifndef SPVM_PACKAGE_VAR_H
#define SPVM_PACKAGE_VAR_H

#include "spvm_base.h"

struct SPVM_package_var {
  SPVM_OP* op_name;
  SPVM_OP* op_our;
};

SPVM_PACKAGE_VAR* SPVM_PACKAGE_VAR_new(SPVM_COMPILER* compiler);

#endif
