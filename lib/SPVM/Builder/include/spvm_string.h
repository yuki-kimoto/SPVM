#ifndef SPVM_STRING_H
#define SPVM_STRING_H

#include "spvm_typedecl.h"

struct spvm_string {
  const char* value;
  int32_t length;
  int32_t id;
};

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler);

#endif
