#ifndef SPVM_DOUBLELIST_H
#define SPVM_DOUBLELIST_H

#include "spvm_base.h"

struct SPVM_doublelist {
  double* values;
  double32_t length;
  double32_t capacity;
};

#endif
