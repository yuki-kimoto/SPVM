#ifndef SPVM_RUNTIME_PACKAGE_H
#define SPVM_RUNTIME_PACKAGE_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_package {
  int32_t id;
  const char* name;
  int32_t destructor_sub_id;
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* package_var_signatures;
  SPVM_HASH* package_var_signature_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* field_signatures;
  SPVM_HASH* field_signature_symtable;
  SPVM_LIST* object_field_indexes;
  SPVM_LIST* subs;
  SPVM_HASH* sub_symtable;
  SPVM_LIST* sub_signatures;
  SPVM_HASH* sub_signature_symtable;
  SPVM_HASH* has_interface_cache_symtable;
};

SPVM_RUNTIME_PACKAGE* SPVM_RUNTIME_PACKAGE_new();

#endif
