#ifndef SPVM_BASIC_TYPE_H
#define SPVM_BASIC_TYPE_H

#include "spvm_typedecl.h"

enum {
  SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT = 8,
};

struct spvm_basic_type {
  const char* name;
  SPVM_CLASS* class;
  int32_t id;
  int32_t category;
};

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler);
const char* const* SPVM_NATIVE_C_BASIC_TYPE_ID_NAMES(void);

const char* SPVM_BASIC_TYPE_get_basic_type_name(int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_not_found_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_get_category(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);
int32_t SPVM_BASIC_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t class_basic_type_id, int32_t interface_basic_type_id);

#endif
