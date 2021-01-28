#ifndef SPVM_WEAKEN_BACKREF_H
#define SPVM_WEAKEN_BACKREF_H

#include <stdio.h>

#include "spvm_typedef.h"

struct SPVM_weaken_backref {
  SPVM_OBJECT** object_address;
  SPVM_WEAKEN_BACKREF* next;
};

SPVM_WEAKEN_BACKREF* SPVM_WEAKEN_BACKREF_new();

#endif
