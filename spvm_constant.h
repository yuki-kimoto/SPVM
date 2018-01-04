#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_base.h"
#include "spvm_api.h"

struct SPVM_constant {
  SPVM_TYPE* type;
  SPVM_API_VALUE value;
  int32_t id;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler);
SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler);

#endif
