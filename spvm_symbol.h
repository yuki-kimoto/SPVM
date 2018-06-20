#ifndef SPVM_SYMBOL_H
#define SPVM_SYMBOL_H

#include "spvm_base.h"

// Field information
struct SPVM_symbol {
  const char* name;
  int32_t index;
};

SPVM_SYMBOL* SPVM_SYMBOL_new(SPVM_COMPILER* compiler);

#endif
