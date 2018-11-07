#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

enum {
  SPVM_PACKAGE_C_CATEGORY_CLASS,
  SPVM_PACKAGE_C_CATEGORY_INTERFACE,
  SPVM_PACKAGE_C_CATEGORY_VALUE_T,
};

enum {
  SPVM_PACKAGE_C_FLAG_IS_PRIVATE = 1,
  SPVM_PACKAGE_C_FLAG_IS_ANON = 2,
  SPVM_PACKAGE_C_FLAG_IS_POINTER = 4,
  SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB = 8,
};

extern const char* const SPVM_PACKAGE_C_CATEGORY_NAMES[];

struct SPVM_package {
  SPVM_OP* op_package;
  SPVM_OP* op_name;
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* subs;
  SPVM_HASH* sub_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* object_field_indexes;
  SPVM_SUB* sub_destructor;
  SPVM_LIST* info_package_var_ids;
  SPVM_HASH* info_package_var_id_symtable;
  SPVM_LIST* info_sub_ids;
  SPVM_HASH* info_sub_id_symtable;
  SPVM_LIST* info_field_ids;
  SPVM_HASH* info_field_id_symtable;
  SPVM_LIST* info_types;
  SPVM_HASH* info_type_symtable;
  SPVM_LIST* info_switch_infos;
  SPVM_LIST* info_long_constants;
  SPVM_HASH* info_long_constant_symtable;
  SPVM_LIST* info_double_constants;
  SPVM_HASH* info_double_constant_symtable;
  SPVM_LIST* info_string_constants;
  SPVM_HASH* info_string_constant_symtable;
  SPVM_CONSTANT_POOL* constant_pool;
  SPVM_HASH* constant_pool_32bit_value_symtable;
  SPVM_HASH* constant_pool_64bit_value_symtable;
  int32_t constant_pool_base;
  const char* load_path;
  SPVM_OP* op_type;
  int32_t id;
  int32_t flag;
  int32_t category;
  const char* name;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

#endif
