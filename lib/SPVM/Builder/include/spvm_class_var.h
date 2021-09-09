#ifndef SPVM_CLASS_VAR_H
#define SPVM_CLASS_VAR_H

#include "spvm_typedecl.h"

enum {
  SPVM_CLASS_VAR_C_FLAG_PUBLIC = 1,
};

struct spvm_class_var {
  const char* name;
  const char* signature;
  SPVM_TYPE* type;
  SPVM_CLASS* class;
  SPVM_OP* op_class_var;
  SPVM_OP* op_name;
  int32_t id;
  int32_t flag;
  int32_t has_setter;
  int32_t has_getter;
};

SPVM_CLASS_VAR* SPVM_CLASS_VAR_new(SPVM_COMPILER* compiler);

#endif
