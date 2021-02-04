#ifndef SPVM_PACKAGE_VAR_H
#define SPVM_PACKAGE_VAR_H

#include "spvm_typedecl.h"

enum {
  SPVM_PACKAGE_VAR_C_FLAG_PUBLIC = 1,
};

struct spvm_package_var {
  const char* name;
  const char* signature;
  SPVM_TYPE* type;
  SPVM_PACKAGE* package;
  SPVM_OP* op_package_var;
  SPVM_OP* op_name;
  int32_t id;
  int32_t flag;
  int32_t has_setter;
  int32_t has_getter;
};

SPVM_PACKAGE_VAR* SPVM_PACKAGE_VAR_new(SPVM_COMPILER* compiler);

#endif
