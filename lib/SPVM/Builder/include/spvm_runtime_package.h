#ifndef SPVM_RUNTIME_PACKAGE_H
#define SPVM_RUNTIME_PACKAGE_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package {
  int32_t id;
  int32_t name_id;
  int32_t destructor_sub_id;
  int32_t category;
  int32_t flag;
  int32_t constant_pool_base;
  int32_t fields_base;
  int32_t subs_base;
  int32_t package_vars_base;
  uint16_t no_dup_field_access_field_ids_constant_pool_id;
  uint16_t no_dup_package_var_access_package_var_ids_constant_pool_id;
  uint16_t no_dup_call_sub_sub_ids_constant_pool_id;
  uint16_t no_dup_basic_type_ids_constant_pool_id;
  uint16_t fields_length;
  uint16_t subs_length;
  uint16_t package_vars_length;
  uint16_t fields_byte_size;
  uint16_t object_fields_byte_offset;
  uint16_t object_fields_length;
};

SPVM_RUNTIME_PACKAGE* SPVM_RUNTIME_PACKAGE_new();

#endif
