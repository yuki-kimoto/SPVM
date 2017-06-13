#ifndef SPVM_TYPE_PART_H
#define SPVM_TYPE_PART_H

#include "spvm_base.h"

enum {
  SPVM_TYPE_PART_C_CODE_SUB,
  SPVM_TYPE_PART_C_CODE_NAME,
  SPVM_TYPE_PART_C_CODE_BYTE
};

extern const char* const SPVM_TYPE_PART_C_CODE_NAMES[];

struct SPVM_type_part {
  union {
    SPVM_OP* op_name;
    const char* char_name;
  } uv;
  int32_t code;
};

SPVM_TYPE_PART* SPVM_TYPE_PART_new(SPVM_COMPILER* compiler);

#endif
