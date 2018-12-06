#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

enum {
  SPVM_PACKAGE_C_CATEGORY_CLASS,
  SPVM_PACKAGE_C_CATEGORY_INTERFACE,
  SPVM_PACKAGE_C_CATEGORY_VALUE,
};

enum {
  SPVM_PACKAGE_C_FLAG_POINTER = 1,
  SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE = 2,
  SPVM_PACKAGE_C_FLAG_PRIVATE = 4,
  SPVM_PACKAGE_C_FLAG_PUBLIC = 8,
};

extern const char* const SPVM_PACKAGE_C_CATEGORY_NAMES[];

struct SPVM_package {
  SPVM_OP* op_package;
  SPVM_OP* op_name;
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* subs;
  SPVM_HASH* sub_symtable;
  SPVM_HASH* sub_name_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_SUB* sub_destructor;
  SPVM_LIST* info_package_var_ids;
  SPVM_HASH* info_package_var_id_symtable;
  SPVM_LIST* info_sub_ids;
  SPVM_HASH* info_sub_id_symtable;
  SPVM_LIST* info_field_ids;
  SPVM_HASH* info_field_id_symtable;
  SPVM_LIST* info_basic_type_ids;
  SPVM_HASH* info_basic_type_id_symtable;
  SPVM_LIST* info_switch_infos;
  SPVM_HASH* string_symtable;
  SPVM_CONSTANT_POOL* constant_pool;
  SPVM_HASH* constant_pool_32bit_value_symtable;
  SPVM_HASH* constant_pool_32bit2_value_symtable;
  SPVM_HASH* constant_pool_64bit_value_symtable;
  int32_t constant_pool_base;
  int32_t no_dup_field_access_field_ids_constant_pool_id;
  int32_t no_dup_package_var_access_package_var_ids_constant_pool_id;
  int32_t no_dup_call_sub_sub_ids_constant_pool_id;
  int32_t no_dup_basic_type_ids_constant_pool_id;
  int32_t object_field_indexes_constant_pool_id;
  const char* load_path;
  SPVM_OP* op_type;
  SPVM_LIST* op_uses;
  int32_t id;
  int32_t fields_byte_size;
  int32_t object_fields_offset;
  int32_t object_fields_length;
  int32_t flag;
  int32_t category;
  const char* name;
  SPVM_OP* op_begin_sub;
  int32_t fail_load;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

#endif
