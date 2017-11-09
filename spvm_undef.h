#ifndef SPVM_UNDEF_H
#define SPVM_UNDEF_H

#include "spvm_base.h"

// Field information
struct SPVM_undef {
  SPVM_TYPE* type;
};

SPVM_UNDEF* SPVM_UNDEF_new(SPVM_COMPILER* compiler);

#endif
