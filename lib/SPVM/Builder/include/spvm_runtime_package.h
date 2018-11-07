#ifndef SPVM_RUNTIME_PACKAGE_H
#define SPVM_RUNTIME_PACKAGE_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package {
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* object_field_indexes;
  SPVM_LIST* subs;
  SPVM_HASH* sub_symtable;
  int32_t id;
  int32_t name_id;
  int32_t destructor_sub_id;
  int32_t category;
  int32_t flag;
  int32_t info_package_var_ids_base;
  int32_t info_field_ids_base;
  int32_t info_sub_ids_base;
  int32_t info_types_base;
  int32_t info_switch_infos_base;
  int32_t info_string_values_base;
  int32_t constant_pool_base;
  uint16_t info_package_var_ids_length;
  uint16_t info_field_ids_length;
  uint16_t info_sub_ids_length;
  uint16_t info_types_length;
  uint16_t info_switch_infos_length;
  uint16_t info_string_values_length;
  uint16_t no_dup_field_access_field_ids_constant_pool_id;
};

SPVM_RUNTIME_PACKAGE* SPVM_RUNTIME_PACKAGE_new();

#endif
