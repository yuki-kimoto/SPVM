#ifndef SPVM_CLASS_H
#define SPVM_CLASS_H

#include "spvm_typedecl.h"

enum {
  SPVM_CLASS_C_CATEGORY_CLASS,
  SPVM_CLASS_C_CATEGORY_CALLBACK,
  SPVM_CLASS_C_CATEGORY_MULNUM,
  SPVM_CLASS_C_CATEGORY_INTERFACE,
};

enum {
  SPVM_CLASS_C_FLAG_POINTER = 1,
  SPVM_CLASS_C_FLAG_ANON_METHOD_CLASS = 2,
  SPVM_CLASS_C_FLAG_PUBLIC = 4,
};

struct spvm_class {
  int32_t id;
  int32_t method_destructor_id;
  int32_t flag;
  int32_t object_fields_length;
  int32_t object_fields_offset;
  int8_t has_init_block;
  int8_t is_anon;
  const char* name;
  const char* module_file;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* fields;
  SPVM_OP* op_class;
  SPVM_OP* op_name;
  SPVM_HASH* class_var_symtable;
  SPVM_HASH* class_alias_symtable;
  SPVM_HASH* field_symtable;
  SPVM_METHOD* method_destructor;
  const char* module_rel_file;
  SPVM_LIST* allows;
  SPVM_LIST* implements;
  SPVM_HASH* interface_class_symtable;
  SPVM_LIST* anon_methods;
  int32_t fields_byte_size;
  int8_t category;
  int8_t fail_load;
  int8_t has_precompile_descriptor;
  SPVM_LIST* class_vars;
  SPVM_TYPE* type;
};

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler);
const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void);

#endif
 