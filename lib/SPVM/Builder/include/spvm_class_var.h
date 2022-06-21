#ifndef SPVM_CLASS_VAR_H
#define SPVM_CLASS_VAR_H

#include "spvm_typedecl.h"

struct spvm_class_var {
  const char* name;
  const char* signature;
  SPVM_TYPE* type;
  SPVM_CLASS* class;
  SPVM_OP* op_class_var;
  SPVM_OP* op_name;
  int32_t id;
  int8_t has_setter;
  int8_t has_getter;
  int8_t access_control_type;
};

SPVM_CLASS_VAR* SPVM_CLASS_VAR_new(SPVM_COMPILER* compiler);

#endif
