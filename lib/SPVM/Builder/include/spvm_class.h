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
  SPVM_OP* op_class;
  SPVM_OP* op_name;
  const char* name;
  const char* module_file;
  const char* module_dir;
  const char* module_rel_file;
  SPVM_TYPE* type;
  SPVM_LIST* class_vars;
  SPVM_HASH* class_var_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* interfaces;
  SPVM_HASH* interface_symtable;
  SPVM_LIST* anon_methods;
  SPVM_LIST* allows;
  SPVM_LIST* interface_decls;
  SPVM_HASH* class_alias_symtable;
  SPVM_METHOD* method_destructor;
  int32_t id;
  int32_t method_destructor_id;
  int32_t flag;
  int32_t object_fields_length;
  int32_t object_fields_offset;
  int32_t fields_byte_size;
  int8_t has_init_block;
  int8_t is_anon;
  int8_t category;
  int8_t has_precompile_descriptor;
};

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler);
const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void);

#endif
 