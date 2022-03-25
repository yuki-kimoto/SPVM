#ifndef SPVM_ALLOW_H
#define SPVM_ALLOW_H

#include "spvm_typedecl.h"

struct spvm_allow {
  SPVM_OP* op_allow;
  SPVM_OP* op_type;
  const char* class_name;
};

SPVM_ALLOW* SPVM_ALLOW_new(SPVM_COMPILER* compiler);

#endif
