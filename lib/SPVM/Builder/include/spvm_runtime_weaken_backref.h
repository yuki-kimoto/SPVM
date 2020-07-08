#ifndef SPVM_RUNTIME_WEAKEN_BACKREF_H
#define SPVM_RUNTIME_WEAKEN_BACKREF_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_runtime_weaken_backref {
  SPVM_OBJECT** object_address;
  SPVM_RUNTIME_WEAKEN_BACKREF* next;
};

SPVM_RUNTIME_WEAKEN_BACKREF* SPVM_RUNTIME_WEAKEN_BACKREF_new();

#endif
