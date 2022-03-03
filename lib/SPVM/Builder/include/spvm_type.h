#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

enum {
  SPVM_TYPE_C_FLAG_REF = 1,
  SPVM_TYPE_C_FLAG_MUTABLE = 2,
};

enum {
  SPVM_TYPE_C_TYPE_CATEGORY_UNKNOWN,
  SPVM_TYPE_C_TYPE_CATEGORY_BYTE,
  SPVM_TYPE_C_TYPE_CATEGORY_SHORT,
  SPVM_TYPE_C_TYPE_CATEGORY_INT,
  SPVM_TYPE_C_TYPE_CATEGORY_LONG,
  SPVM_TYPE_C_TYPE_CATEGORY_FLOAT,
  SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE,
  SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT,
  SPVM_TYPE_C_TYPE_CATEGORY_CLASS,
  SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY,
  SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY,
  SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_INT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT,
  SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE,
  SPVM_TYPE_C_TYPE_CATEGORY_VOID,
  SPVM_TYPE_C_TYPE_CATEGORY_STRING,
};

struct spvm_type {
  const char* type_name;
  SPVM_BASIC_TYPE* basic_type;
  int32_t dimension;
  int32_t flag;
  int32_t category;
  int32_t width;
};

int32_t SPVM_TYPE_has_callback(
  SPVM_COMPILER* compiler,
  int32_t class_basic_type_id, int32_t class_type_dimension, int32_t class_type_flag,
  int32_t callback_basic_type_id, int32_t callback_type_dimension, int32_t callback_type_flag
);

int32_t SPVM_TYPE_has_interface(
  SPVM_COMPILER* compiler,
  int32_t class_basic_type_id, int32_t class_type_dimension, int32_t class_type_flag,
  int32_t interface_basic_type_id, int32_t interface_type_dimension, int32_t interface_type_flag
);

int32_t SPVM_TYPE_get_type_category(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

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

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_create_byte_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_short_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_int_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_long_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_float_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_double_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_create_bool_object_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_bool_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_object(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_multi_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_multi_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_mulnum_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_basic_type_is_multi_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_or_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_oarray_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_embedded_class_name(SPVM_COMPILER* compiler, const char* type_name);

int32_t SPVM_TYPE_get_elem_byte_size(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

#endif
