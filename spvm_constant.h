#ifndef SPVM_CONSTANT_H
#define SPVM_CONSTANT_H

#include "spvm_base.h"

enum {
  SPVM_CONSTANT_C_CODE_BYTE,
  SPVM_CONSTANT_C_CODE_SHORT,
  SPVM_CONSTANT_C_CODE_INT,
  SPVM_CONSTANT_C_CODE_LONG,
  SPVM_CONSTANT_C_CODE_FLOAT,
  SPVM_CONSTANT_C_CODE_DOUBLE,
  SPVM_CONSTANT_C_CODE_STRING,
};

extern const char* const SPVM_CONSTANT_C_CODE_NAMES[];

struct SPVM_constant {
  SPVM_RESOLVED_TYPE* resolved_type;
  union {
    // byte, short, int value is saved to long_value
    int64_t long_value;
    float float_value;
    double double_value;
    const char* string_value;
  } uv;
  int32_t code;
  int32_t constant_pool_address;
  _Bool is_undef;
};

SPVM_CONSTANT* SPVM_CONSTANT_new(SPVM_* spvm);
SPVM_CONSTANT* SPVM_CONSTANT_create_int_1(SPVM_* spvm);

#endif
