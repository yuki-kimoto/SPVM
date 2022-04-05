#ifndef SPVM_BASIC_TYPE_H
#define SPVM_BASIC_TYPE_H

#include "spvm_typedecl.h"




enum {
  SPVM_BASIC_TYPE_C_ID_UNKNOWN,
  SPVM_BASIC_TYPE_C_ID_UNDEF,
  SPVM_BASIC_TYPE_C_ID_VOID,
  SPVM_BASIC_TYPE_C_ID_BYTE,
  SPVM_BASIC_TYPE_C_ID_SHORT,
  SPVM_BASIC_TYPE_C_ID_INT,
  SPVM_BASIC_TYPE_C_ID_LONG,
  SPVM_BASIC_TYPE_C_ID_FLOAT,
  SPVM_BASIC_TYPE_C_ID_DOUBLE,
  SPVM_BASIC_TYPE_C_ID_STRING,
  SPVM_BASIC_TYPE_C_ID_ANY_OBJECT,
  SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT,
  SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_INT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_LONG_OBJECT,
  SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT,
  SPVM_BASIC_TYPE_C_ID_BOOL_OBJECT,
};

enum {
  SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT = 8,
};

enum {
  SPVM_BASIC_TYPE_C_CATEGORY_UNKNOWN,
  SPVM_BASIC_TYPE_C_CATEGORY_FAIL_LOAD,
  SPVM_BASIC_TYPE_C_CATEGORY_UNDEF,
  SPVM_BASIC_TYPE_C_CATEGORY_VOID,
  SPVM_BASIC_TYPE_C_CATEGORY_NUMERIC,
  SPVM_BASIC_TYPE_C_CATEGORY_MULNUM,
  SPVM_BASIC_TYPE_C_CATEGORY_STRING,
  SPVM_BASIC_TYPE_C_CATEGORY_CLASS,
  SPVM_BASIC_TYPE_C_CATEGORY_INTERFACE,
  SPVM_BASIC_TYPE_C_CATEGORY_CALLBACK,
  SPVM_BASIC_TYPE_C_CATEGORY_ANY_OBJECT,
};

struct spvm_basic_type {
  const char* name;
  SPVM_CLASS* class;
  int32_t id;
  int32_t category;
};

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler);
const char* const* SPVM_BASIC_TYPE_C_ID_NAMES(void);

const char* SPVM_BASIC_TYPE_get_basic_type_name(int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_fail_load_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

#endif
