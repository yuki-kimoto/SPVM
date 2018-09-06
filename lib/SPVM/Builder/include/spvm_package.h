#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

enum {
  SPVM_PACKAGE_C_CATEGORY_CLASS,
  SPVM_PACKAGE_C_CATEGORY_INTERFACE,
  SPVM_PACKAGE_C_CATEGORY_POINTER,
  SPVM_PACKAGE_C_CATEGORY_VALUE_T,
};

extern const char* const SPVM_PACKAGE_C_CATEGORY_NAMES[];

struct SPVM_package {
  SPVM_OP* op_package;
  SPVM_OP* op_name;
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* subs;
  SPVM_HASH* sub_symtable;
  SPVM_LIST* sub_signatures;
  SPVM_HASH* sub_signature_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* field_signatures;
  SPVM_HASH* field_signature_symtable;
  SPVM_LIST* object_field_indexes;
  SPVM_LIST* package_var_signatures;
  SPVM_HASH* package_var_signature_symtable;
  SPVM_HASH* has_interface_cache_symtable;
  SPVM_SUB* sub_destructor;
  const char* load_path;
  SPVM_OP* op_type;
  int32_t id;
  _Bool is_private;
  _Bool is_anon;
  int32_t category;
  const char* name;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

#endif
