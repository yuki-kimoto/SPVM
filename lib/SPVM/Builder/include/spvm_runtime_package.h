#ifndef SPVM_RUNTIME_PACKAGE_H
#define SPVM_RUNTIME_PACKAGE_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package {
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* object_field_indexes;
  SPVM_HASH* sub_symtable;
  int32_t id;
  int32_t name_id;
  int32_t destructor_sub_id;
  int32_t category;
  int32_t flag;
  int32_t info_switch_infos_base;
  int32_t constant_pool_base;
  int32_t subs_base;
  uint16_t info_switch_infos_length;
  uint16_t no_dup_field_access_field_ids_constant_pool_id;
  uint16_t no_dup_package_var_access_package_var_ids_constant_pool_id;
  uint16_t no_dup_call_sub_sub_ids_constant_pool_id;
  uint16_t no_dup_basic_type_ids_constant_pool_id;
  uint16_t subs_length;
};

SPVM_RUNTIME_PACKAGE* SPVM_RUNTIME_PACKAGE_new();

#endif
