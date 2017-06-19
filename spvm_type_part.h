#ifndef SPVM_TYPE_PART_H
#define SPVM_TYPE_PART_H

#include "spvm_base.h"

extern const char* const SPVM_TYPE_PART_C_CODE_NAMES[];

struct SPVM_type_part {
  const char* value;
};

SPVM_TYPE_PART* SPVM_TYPE_PART_new(SPVM_COMPILER* compiler);

#endif
