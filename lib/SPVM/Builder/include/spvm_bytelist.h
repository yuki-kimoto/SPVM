#ifndef SPVM_BYTELIST_H
#define SPVM_BYTELIST_H

#include "spvm_base.h"

struct SPVM_bytelist {
  byte8_t* values;
  byte32_t length;
  byte32_t capacity;
};

#endif
