#ifndef SPVM_INTLIST_H
#define SPVM_INTLIST_H

#include "spvm_base.h"

struct SPVM_intlist {
  int32_t* values;
  int32_t length;
  int32_t capacity;
};

#endif
