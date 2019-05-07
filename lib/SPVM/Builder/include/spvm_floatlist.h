#ifndef SPVM_FLOATLIST_H
#define SPVM_FLOATLIST_H

#include "spvm_base.h"

struct SPVM_floatlist {
  float* values;
  float32_t length;
  float32_t capacity;
};

#endif
