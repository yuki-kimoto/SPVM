#ifndef SPVM_COMPATIBLE_H
#define SPVM_COMPATIBLE_H

#include "spvm_typedecl.h"

struct spvm_compatible {
  SPVM_OP* op_type;
};

SPVM_COMPATIBLE* SPVM_COMPATIBLE_new(SPVM_COMPILER* compiler);

#endif
