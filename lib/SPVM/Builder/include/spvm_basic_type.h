// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_BASIC_TYPE_H
#define SPVM_BASIC_TYPE_H

#include "spvm_typedecl.h"

enum {
  SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT = 8,
};

struct spvm_basic_type {
  const char* name;
  int32_t id;
  int32_t category;
  SPVM_OP* op_class;
  SPVM_OP* op_name;
  SPVM_OP* op_extends;
  const char* file;
  const char* class_dir;
  const char* class_rel_file;
  const char* version_string;
  SPVM_VERSION_FROM* version_from;
  const char* basic_type_name_in_version_from;
  SPVM_LIST* constant_strings;
  SPVM_HASH* constant_string_symtable;
  SPVM_STRING_BUFFER* string_pool;
  SPVM_LIST* class_vars;
  SPVM_HASH* class_var_symtable;
  SPVM_LIST* original_fields;
  SPVM_HASH* original_field_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* virtual_methods;
  SPVM_HASH* virtual_method_symtable;
  SPVM_LIST* interface_basic_types;
  SPVM_HASH* interface_basic_symtable;
  SPVM_LIST* anon_unresolved_basic_type_names;
  SPVM_LIST* anon_basic_types;
  SPVM_LIST* allows;
  SPVM_LIST* interface_decls;
  SPVM_LIST* use_basic_type_names;
  SPVM_HASH* alias_symtable;
  SPVM_METHOD* required_method;
  SPVM_METHOD* destroy_method;
  SPVM_METHOD* init_method;
  SPVM_METHOD* end_method;
  SPVM_LIST* op_inits;
  SPVM_LIST* op_ends;
  const char* parent_name;
  SPVM_BASIC_TYPE* parent;
  SPVM_BASIC_TYPE* outmost;
  SPVM_TYPE* monitor_var_type;
  int32_t fields_size;
  int8_t is_anon;
  int8_t is_generated_by_anon_method;
  int8_t is_precompile;
  int8_t is_pointer;
  int8_t access_control_type;
};

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler);

const char* const* SPVM_BASIC_TYPE_C_ID_NAMES(void);

const char* SPVM_BASIC_TYPE_get_basic_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_mulnum_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t interface_basic_type_id, char* error_reason);

int32_t SPVM_BASIC_TYPE_has_interface_common(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t interface_basic_type_id, char* error_reason);

int32_t SPVM_BASIC_TYPE_is_super_class(SPVM_COMPILER* compiler, int32_t dist_basic_type_id, int32_t src_basic_type_id);

SPVM_STRING* SPVM_BASIC_TYPE_add_constant_string(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* value, int32_t length);

int32_t SPVM_BASIC_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

#endif
