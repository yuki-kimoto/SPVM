#ifndef SPVM_TYPE_H
#define SPVM_TYPE_H

#include <stdio.h>

#include "spvm_base.h"

enum {
  SPVM_TYPE_C_FLAG_CONST = 1,
  SPVM_TYPE_C_FLAG_REF = 2,
};

enum {
  SPVM_TYPE_C_RUNTIME_TYPE_UNKNOWN,
  SPVM_TYPE_C_RUNTIME_TYPE_BYTE,
  SPVM_TYPE_C_RUNTIME_TYPE_SHORT,
  SPVM_TYPE_C_RUNTIME_TYPE_INT,
  SPVM_TYPE_C_RUNTIME_TYPE_LONG,
  SPVM_TYPE_C_RUNTIME_TYPE_FLOAT,
  SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE,
  SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT,
  SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE,
  SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY,
  SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY,
  SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_INT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT,
  SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE,
  SPVM_TYPE_C_RUNTIME_TYPE_VOID,
};


struct SPVM_type {
  SPVM_OP* op_type;
  SPVM_BASIC_TYPE* basic_type;
  int32_t dimension;
  int32_t flag;
  int32_t info_constant_id;
  int32_t constant_pool_id;
  int8_t is_self;
};

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler);

int32_t SPVM_TYPE_has_interface(
  SPVM_COMPILER* compiler,
  int32_t package_basic_type_id, int32_t package_type_dimension, int32_t package_type_flag,
  int32_t interface_basic_type_id, int32_t interface_type_dimension, int32_t interface_type_flag
);

int32_t SPVM_TYPE_get_runtime_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

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

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_numeric_object(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
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

int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);
void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension, int32_t flag);
void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag);

SPVM_TYPE* SPVM_TYPE_clone_type(SPVM_COMPILER* compiler, SPVM_TYPE* type);

#endif
