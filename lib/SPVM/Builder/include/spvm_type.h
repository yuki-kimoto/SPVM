#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

enum {
  SPVM_TYPE_C_FLAG_REF = 1,
  SPVM_TYPE_C_FLAG_MUTABLE = 2,
};

struct spvm_type {
  const char* name;
  int32_t dimension;
  int32_t flag;
  int32_t width;
  int32_t id;
  SPVM_BASIC_TYPE* basic_type;
};

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
int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
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
int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_or_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_any_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_basic_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_get_mulnum_field_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_basic_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_not_found_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_check_assignability(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  SPVM_CONSTANT* src_constant, int32_t* need_implicite_conversion, int32_t* narrowing_conversion_error, int32_t* mutable_invalid
);

int32_t SPVM_TYPE_check_castability(
  SPVM_COMPILER* compiler,
  int32_t cast_type_basic_type_id, int32_t cast_type_dimension, int32_t cast_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag
);

#endif
