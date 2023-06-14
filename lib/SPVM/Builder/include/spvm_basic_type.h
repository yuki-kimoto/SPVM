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
  SPVM_CLASS* class;
  int32_t id;
  int32_t category;
  SPVM_OP* op_class;
  SPVM_OP* op_name;
  SPVM_OP* op_extends;
  const char* class_file;
  const char* class_path;
  const char* class_rel_file;
  const char* version_string;
  SPVM_TYPE* type;
  SPVM_LIST* class_vars;
  SPVM_HASH* class_var_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* merged_fields;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* interfaces;
  SPVM_HASH* interface_symtable;
  SPVM_LIST* anon_methods;
  SPVM_LIST* allows;
  SPVM_LIST* interface_decls;
  SPVM_LIST* use_class_names;
  SPVM_HASH* class_alias_symtable;
  SPVM_METHOD* required_method;
  SPVM_METHOD* destructor_method;
  SPVM_METHOD* init_method;
  const char* parent_class_name;
  SPVM_CLASS* parent_class;
  SPVM_BASIC_TYPE* parent_class_basic_type;
  int32_t class_id;
  int32_t merged_fields_original_offset;
  int32_t fields_size;
  int8_t has_init_block;
  int8_t is_anon;
  int8_t is_precompile;
  int8_t is_pointer;
  int8_t access_control_type;
  int8_t is_class;
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

int32_t SPVM_BASIC_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_unknown_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_not_found_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_integer_type(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_is_integer_type_within_int(SPVM_COMPILER* compiler, int32_t basic_type_id);

int32_t SPVM_BASIC_TYPE_has_interface(SPVM_COMPILER* compiler, int32_t class_basic_type_id, int32_t interface_basic_type_id);

int32_t SPVM_BASIC_TYPE_is_super_class(SPVM_COMPILER* compiler, int32_t super_basic_type_id, int32_t child_basic_type_id);

#endif
