#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

struct SPVM_type {
  int32_t dimension;
  SPVM_BASIC_TYPE* basic_type;
  _Bool is_const;
  int32_t sub_rel_id;
};

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

SPVM_TYPE* SPVM_TYPE_create_void_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_undef_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_byte_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_short_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_int_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_long_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_float_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_double_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_string_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_object_type(SPVM_COMPILER* compiler);

_Bool SPVM_TYPE_equal(SPVM_COMPILER* compiler, SPVM_TYPE* type1, SPVM_TYPE* type2);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension);
void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension);
void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, SPVM_TYPE* type);

#endif
