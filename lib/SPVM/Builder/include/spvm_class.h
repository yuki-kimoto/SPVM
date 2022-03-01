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
  SPVM_OP* op_type;
  const char* name;
  SPVM_LIST* class_vars;
  SPVM_HASH* class_var_symtable;
  SPVM_HASH* class_alias_symtable;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_METHOD* method_destructor;
  SPVM_LIST* info_switch_infos;
  const char* module_file;
  const char* module_rel_file;
  SPVM_LIST* op_uses;
  SPVM_LIST* op_allows;
  SPVM_LIST* op_implements;
  SPVM_HASH* interface_class_symtable;
  SPVM_LIST* anon_methods;
  int32_t id;
  int32_t fields_byte_size;
  int32_t object_fields_offset;
  int32_t object_fields_length;
  int32_t flag;
  int8_t category;
  int8_t fail_load;
  int8_t has_precompile_descriptor;
  int8_t is_anon;
  int8_t has_init_block;
};

SPVM_CLASS* SPVM_CLASS_new(SPVM_COMPILER* compiler);
const char* const* SPVM_CLASS_C_CATEGORY_NAMES(void);

#endif
 