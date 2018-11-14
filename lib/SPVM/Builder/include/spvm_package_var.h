#ifndef SPVM_PACKAGE_VAR_H
#define SPVM_PACKAGE_VAR_H

#include "spvm_base.h"

enum {
  SPVM_PACKAGE_VAR_C_FLAG_PRIVATE = 1,
};

struct SPVM_package_var {
  SPVM_OP* op_package_var;
  SPVM_PACKAGE* package;
  SPVM_OP* op_var;
  SPVM_TYPE* type;
  const char* abs_name;
  const char* signature;
  const char* name;
  int32_t id;
  int32_t rel_id;
  int32_t flag;
};

SPVM_PACKAGE_VAR* SPVM_PACKAGE_VAR_new(SPVM_COMPILER* compiler);

#endif
