#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_FLAG_CONST = 1,
  SPVM_TYPE_C_FLAG_REF = 2,
};

struct SPVM_type {
  SPVM_OP* op_type;
  SPVM_BASIC_TYPE* basic_type;
  int32_t dimension;
  int32_t flag;
  int32_t sub_rel_id;
  int8_t is_self;
};

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler);

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


SPVM_TYPE* SPVM_TYPE_create_byte_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_short_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_int_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_long_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_float_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_double_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_any_object_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_package_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_value_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_value_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_value_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_basic_type_is_value_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension, int32_t flag);
void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_clone_type(SPVM_COMPILER* compiler, SPVM_TYPE* type);

#endif
