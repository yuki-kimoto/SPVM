#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_CORE_LENGTH = 19
};

enum {
  SPVM_TYPE_C_ARRAY_SHIFT = 8
};

enum {
  SPVM_TYPE_C_ID_UNKNOWN,
  SPVM_TYPE_C_ID_VOID,
  SPVM_TYPE_C_ID_UNDEF,
  SPVM_TYPE_C_ID_BYTE,
  SPVM_TYPE_C_ID_SHORT,
  SPVM_TYPE_C_ID_INT,
  SPVM_TYPE_C_ID_LONG,
  SPVM_TYPE_C_ID_FLOAT,
  SPVM_TYPE_C_ID_DOUBLE,
  SPVM_TYPE_C_ID_OBJECT,
  SPVM_TYPE_C_ID_STRING,
  SPVM_TYPE_C_ID_BYTE_ARRAY,
  SPVM_TYPE_C_ID_SHORT_ARRAY,
  SPVM_TYPE_C_ID_INT_ARRAY,
  SPVM_TYPE_C_ID_LONG_ARRAY,
  SPVM_TYPE_C_ID_FLOAT_ARRAY,
  SPVM_TYPE_C_ID_DOUBLE_ARRAY,
  SPVM_TYPE_C_ID_OBJECT_ARRAY,
  SPVM_TYPE_C_ID_STRING_ARRAY,
};

extern const char* const SPVM_TYPE_C_ID_NAMES[];

struct SPVM_type {
  const char* name;
  int32_t id;
  int32_t dimension;
  const char* basic_type_name;
  SPVM_BASIC_TYPE* basic_type;
};

char* SPVM_TYPE_get_basic_type_name(SPVM_COMPILER* compiler, const char* type_name);
char* SPVM_TYPE_create_array_name(SPVM_COMPILER* compiler, const char* basic_type_name);
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
_Bool SPVM_TYPE_is_any_object(SPVM_COMPILER* compiler, SPVM_TYPE* type);
_Bool SPVM_TYPE_is_undef(SPVM_COMPILER* compiler, SPVM_TYPE* type);

SPVM_TYPE* SPVM_TYPE_get_void_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_undef_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_byte_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_byte_array_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_get_object_type(SPVM_COMPILER* compiler);

_Bool SPVM_TYPE_equal(SPVM_COMPILER* compiler, SPVM_TYPE* type1, SPVM_TYPE* type2);
SPVM_TYPE* SPVM_TYPE_search_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension);

#endif
