#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_CORE_LENGTH = 14
};

enum {
  SPVM_TYPE_C_ARRAY_SHIFT = 6
};

enum {
  SPVM_TYPE_C_CODE_UNKNOWN = -1
};

enum {
  SPVM_TYPE_C_CODE_VOID,
  SPVM_TYPE_C_CODE_BYTE,
  SPVM_TYPE_C_CODE_SHORT,
  SPVM_TYPE_C_CODE_INT,
  SPVM_TYPE_C_CODE_LONG,
  SPVM_TYPE_C_CODE_FLOAT,
  SPVM_TYPE_C_CODE_DOUBLE,
  SPVM_TYPE_C_CODE_BYTE_ARRAY,
  SPVM_TYPE_C_CODE_SHORT_ARRAY,
  SPVM_TYPE_C_CODE_INT_ARRAY,
  SPVM_TYPE_C_CODE_LONG_ARRAY,
  SPVM_TYPE_C_CODE_FLOAT_ARRAY,
  SPVM_TYPE_C_CODE_DOUBLE_ARRAY,
  SPVM_TYPE_C_CODE_STRING,
};

extern const char* const SPVM_TYPE_C_CODE_NAMES[];

struct SPVM_type {
  const char* name;
  SPVM_OP* op_package;
  int32_t code;
  int32_t id;
  int32_t dimension;
  SPVM_TYPE* base_type;
  int32_t element_type_id;
  int32_t parent_type_id;
};

char* SPVM_TYPE_get_base_name(SPVM_COMPILER* compiler, const char* type_name);
char* SPVM_TYPE_create_array_name(SPVM_COMPILER* compiler, const char* base_name);
char* SPVM_TYPE_get_element_name(SPVM_COMPILER* compiler, const char* type_name);
char* SPVM_TYPE_get_parent_name(SPVM_COMPILER* compiler, const char* type_name);


SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler);

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_string(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_package(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_object(SPVM_COMPILER* compiler, SPVM_TYPE* type);

SPVM_TYPE* SPVM_TYPE_get_void_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_byte_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_byte_array_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler);

#endif
