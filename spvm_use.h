#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_base.h"

struct SPVM_use {
  const char* package_name;
  SPVM_DYNAMIC_ARRAY* template_args;
};

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler);

#endif
