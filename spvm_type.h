#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_CODE_NAME,
  SPVM_TYPE_C_CODE_ARRAY,
  SPVM_TYPE_C_CODE_TEMPLATE,
};

enum {
  SPVM_TYPE_C_CORE_LENGTH = 13
};

enum {
  SPVM_TYPE_C_ID_VOID = -1
};

enum {
  SPVM_TYPE_C_ID_BYTE,
  SPVM_TYPE_C_ID_SHORT,
  SPVM_TYPE_C_ID_INT,
  SPVM_TYPE_C_ID_LONG,
  SPVM_TYPE_C_ID_FLOAT,
  SPVM_TYPE_C_ID_DOUBLE,
  SPVM_TYPE_C_ID_STRING,
  SPVM_TYPE_C_ID_ARRAY_BYTE,
  SPVM_TYPE_C_ID_ARRAY_SHORT,
  SPVM_TYPE_C_ID_ARRAY_INT,
  SPVM_TYPE_C_ID_ARRAY_LONG,
  SPVM_TYPE_C_ID_ARRAY_FLOAT,
  SPVM_TYPE_C_ID_ARRAY_DOUBLE,
};

extern const char* const SPVM_TYPE_C_CODE_NAMES[];
extern const char* const SPVM_TYPE_C_CORE_NAMES[];

struct SPVM_type {
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
void SPVM_TYPE_build_parts(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_DYNAMIC_ARRAY* parts);
_Bool SPVM_TYPE_resolve_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, int32_t name_length);

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_string(SPVM_COMPILER* compiler, SPVM_TYPE* type);

#endif
