#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

enum {
  SPVM_TYPE_C_FLAG_REF = 1,
  SPVM_TYPE_C_FLAG_MUTABLE = 2,
};







enum {
  SPVM_TYPE_C_CATEGORY_UNKNOWN,
  SPVM_TYPE_C_CATEGORY_FAIL_LOAD,
  SPVM_TYPE_C_CATEGORY_UNDEF,
  SPVM_TYPE_C_CATEGORY_VOID,
  SPVM_TYPE_C_CATEGORY_NUMERIC,
  SPVM_TYPE_C_CATEGORY_MULNUM,
  SPVM_TYPE_C_CATEGORY_STRING,
  SPVM_TYPE_C_CATEGORY_CLASS,
  SPVM_TYPE_C_CATEGORY_INTERFACE,
  SPVM_TYPE_C_CATEGORY_CALLBACK,
  SPVM_TYPE_C_CATEGORY_ANY_OBJECT,
  SPVM_TYPE_C_CATEGORY_NUMERIC_ARRAY,
  SPVM_TYPE_C_CATEGORY_MULNUM_ARRAY,
  SPVM_TYPE_C_CATEGORY_STRING_ARRAY,
  SPVM_TYPE_C_CATEGORY_CLASS_ARRAY,
  SPVM_TYPE_C_CATEGORY_INTERFACE_ARRAY,
  SPVM_TYPE_C_CATEGORY_CALLBACK_ARRAY,
  SPVM_TYPE_C_CATEGORY_ANY_OBJECT_ARRAY,
  SPVM_TYPE_C_CATEGORY_MULDIM_ARRAY,
  SPVM_TYPE_C_CATEGORY_NUMERIC_REF,
  SPVM_TYPE_C_CATEGORY_MULNUM_REF,
};

struct spvm_type {
  const char* name;
  int32_t dimension;
  int32_t flag;
  int32_t width;
  int32_t id;
  SPVM_BASIC_TYPE* basic_type;
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

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_void_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_undef_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_byte_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_short_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_int_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_long_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_float_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_double_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_string_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_object_type(SPVM_COMPILER* compiler);


SPVM_TYPE* SPVM_TYPE_new_byte_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_short_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_int_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_long_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_float_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_double_ref_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_any_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_element_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_byte_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_short_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_int_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_long_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_float_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_double_object_type(SPVM_COMPILER* compiler);
SPVM_TYPE* SPVM_TYPE_new_bool_object_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_bool_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_mulnum_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_object(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_interface_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_callback_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_class_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_muldim_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_mulnum_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_basic_type_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_or_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_any_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_embedded_class_name(SPVM_COMPILER* compiler, const char* type_name);

int32_t SPVM_TYPE_get_elem_byte_size(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_get_mulnum_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_basic_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_fail_load_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_can_assign(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  SPVM_CONSTANT* src_constant, int32_t* need_implicite_conversion, int32_t* narrowing_conversion_error, int32_t* mutable_invalid
);

#endif
