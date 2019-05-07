#ifndef SPVM_LONGLIST_H
#define SPVM_LONGLIST_H

#include "spvm_base.h"

struct SPVM_longlist {
  long64_t* values;
  long32_t length;
  long32_t capacity;
};

#endif
