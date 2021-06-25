#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_typedecl.h"

struct spvm_use {
  SPVM_OP* op_type;
  SPVM_LIST* method_names;
  int32_t is_require;
  int32_t load_fail;
  const char* file;
};

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler);

#endif
