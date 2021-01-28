#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_typedef.h"
#include "spvm_native.h"

struct SPVM_constant {
  SPVM_OP* op_constant;
  SPVM_TYPE* type;
  SPVM_VALUE value;
  int32_t string_length;
  int32_t constant_pool_id;
  int32_t constant_id;
  const char* num_str;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler);
SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler);

#endif
