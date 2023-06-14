// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CLASS_H
#define SPVM_CLASS_H

#include "spvm_typedecl.h"

enum {
  SPVM_CLASS_C_CATEGORY_CLASS,
  SPVM_CLASS_C_CATEGORY_INTERFACE,
  SPVM_CLASS_C_CATEGORY_MULNUM,
};

struct spvm_class {
  const char* parent_class_name;
  SPVM_CLASS* parent_class;
  int32_t merged_fields_original_offset;
  int32_t fields_size;
  int8_t category;
  SPVM_OP* op_class;
  SPVM_OP* op_name;
  SPVM_OP* op_extends;
  const char* name;
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
};

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler);
const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void);

#endif
