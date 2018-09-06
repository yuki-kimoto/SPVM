#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_base.h"

struct SPVM_use {
  SPVM_OP* op_type;
};

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler);

#endif
