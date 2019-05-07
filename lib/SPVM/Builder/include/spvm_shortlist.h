#ifndef SPVM_SHORTLIST_H
#define SPVM_SHORTLIST_H

#include "spvm_base.h"

struct SPVM_shortlist {
  short16_t* values;
  short32_t length;
  short32_t capacity;
};

#endif
