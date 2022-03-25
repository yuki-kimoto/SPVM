#ifndef SPVM_IMPLEMENT_H
#define SPVM_IMPLEMENT_H

#include "spvm_typedecl.h"

struct spvm_implement {
  SPVM_OP* op_implement;
  const char* class_name;
};

SPVM_IMPLEMENT* SPVM_IMPLEMENT_new(SPVM_COMPILER* compiler);

#endif
