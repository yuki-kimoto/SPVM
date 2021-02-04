#ifndef SPVM_ENUMERATION_VALUE_H
#define SPVM_ENUMERATION_VALUE_H

#include "spvm_typedecl.h"

// Field information
struct spvm_enumeration_value {
  SPVM_OP* op_name;
  SPVM_OP* op_constant;
};

SPVM_ENUMERATION_VALUE* SPVM_ENUMERATION_VALUE_new(SPVM_COMPILER* compiler);

#endif
