// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_typedecl.h"

struct spvm_type {
  SPVM_BASIC_TYPE* basic_type;
  const char* unresolved_basic_type_name;
  SPVM_TYPE* of;
  int32_t dimension;
  int32_t flag;
  int8_t resolved_in_ast;
  int8_t is_generic_type;
  int8_t is_union_type;
};

SPVM_TYPE* SPVM_TYPE_new_uninitialized(SPVM_COMPILER* compiler);

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

const char* SPVM_TYPE_new_generic_type_name(SPVM_COMPILER* compiler, SPVM_TYPE* type);

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

int32_t SPVM_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

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

int32_t SPVM_TYPE_get_type_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_field_order(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_unresolved_type(SPVM_COMPILER* compiler, const char* unresolved_basic_type_name, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_new_any_object_array_type(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_get_mulnum_field_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_basic_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_string_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_user_defined_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_satisfy_assignment_requirement(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  int32_t* need_data_conversion, int32_t allow_narrowing_conversion, int32_t interface_match,
  char* error_reason
);

int32_t SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason
);

int32_t SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion_with_interface_match(
  SPVM_COMPILER* compiler,
  int32_t dist_type_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason
);

int32_t SPVM_TYPE_satisfy_cast_requirement(
  SPVM_COMPILER* compiler,
  int32_t cast_type_basic_type_id, int32_t cast_type_dimension, int32_t cast_type_flag,
  int32_t src_type_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag,
  char* error_reason
);

int32_t SPVM_TYPE_is_super_class(SPVM_COMPILER* compiler,
  int32_t dist_basic_type_id, int32_t super_dimension, int32_t super_flag,
  int32_t src_basic_type_id, int32_t child_dimension, int32_t child_flag);

int32_t SPVM_TYPE_equals(SPVM_COMPILER* compiler, int32_t basic_type_id1, int32_t type_dimension1, int32_t type_flag1, int32_t basic_type_id2, int32_t type_dimension2, int32_t type_flag2);

int32_t SPVM_TYPE_satisfy_interface_method_requirement(SPVM_COMPILER* compiler, SPVM_METHOD* dist_method, SPVM_METHOD* src_method, char* error_reason);

int32_t SPVM_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag, int32_t interface_basic_type_id);

int32_t SPVM_TYPE_is_mutable_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

#endif
