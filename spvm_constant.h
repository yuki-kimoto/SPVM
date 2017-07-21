#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_base.h"

struct SPVM_constant {
  SPVM_TYPE* type;
  union {
    // byte, short, int value is saved to long_value
    int64_t long_value;
    float float_value;
    double double_value;
    const char* string_value;
  } uv;
  uint64_t tmp_ulong_value;
  int32_t constant_pool_index;
  _Bool sign;
  _Bool resolved;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_COMPILER* compiler);
SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_COMPILER* compiler);

#endif
