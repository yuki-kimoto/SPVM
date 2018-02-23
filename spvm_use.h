#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_base.h"

struct SPVM_use {
  const char* package_name;
  const char* package_name_with_template_args;
  SPVM_LIST* template_args;
};

SPVM_USE* SPVM_USE_new(SPVM_COMPILER* compiler);

#endif
