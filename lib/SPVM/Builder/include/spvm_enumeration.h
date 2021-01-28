#ifndef SPVM_ENUMERATION_H
#define SPVM_ENUMERATION_H

#include "spvm_typedef.h"

struct SPVM_enumeration {
  SPVM_LIST* enumeration_values;
};

SPVM_ENUMERATION* SPVM_ENUMERATION_new(SPVM_COMPILER* compiler);

#endif
