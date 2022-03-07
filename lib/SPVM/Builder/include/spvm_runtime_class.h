#ifndef SPVM_RUNTIME_CLASS_H
#define SPVM_RUNTIME_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_class {
  const char* name;
  SPVM_TYPE* type;
  SPVM_LIST* class_vars;
  SPVM_HASH* class_var_symtable;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  int32_t id;
  const char* module_file;
  int32_t method_destructor_id;
  int32_t flag;
  int32_t object_fields_length;
  int32_t object_fields_offset;
  int8_t has_init_block;
  int8_t is_anon;
};

#endif
 