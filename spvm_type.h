#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_CODE_NAME,
  SPVM_TYPE_C_CODE_ARRAY,
};

extern const char* const SPVM_TYPE_C_CODE_NAMES[];

struct SPVM_type {
  SPVM_RESOLVED_TYPE* resolved_type;
  const char* name;
  int32_t id;
  int32_t name_length;
  union {
    SPVM_OP* op_name;
    SPVM_OP* op_type;
  } uv;
  int32_t code;
};


SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler);
void SPVM_TYPE_build_parts(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_ARRAY* parts);
_Bool SPVM_TYPE_resolve_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, int32_t name_length);

#endif
