#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

struct spvm_constant {
  SPVM_OP* op_constant;
  SPVM_TYPE* type;
  SPVM_VALUE value;
  int32_t string_length;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler);

#endif
