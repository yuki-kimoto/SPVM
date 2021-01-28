#ifndef SPVM_ALLOW_H
#define SPVM_ALLOW_H

#include "spvm_typedef.h"

struct SPVM_allow {
  SPVM_OP* op_type;
};

SPVM_ALLOW* SPVM_ALLOW_new(SPVM_COMPILER* compiler);

#endif
