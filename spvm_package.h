#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

struct SPVM_package {
  SPVM_OP* op_name;
  SPVM_LIST* op_subs;
  SPVM_LIST* op_fields;
  SPVM_HASH* op_field_symtable;
  SPVM_HASH* op_our_symtable;
  SPVM_HASH* method_signature_symtable;
  SPVM_HASH* has_interface_cache_symtable;
  SPVM_OP* op_sub_destructor;
  char* load_path;
  SPVM_OP* op_type;
  int32_t id;
  int32_t byte_size;
  int32_t object_field_byte_offsets_base;
  int32_t object_field_byte_offsets_length;
  _Bool is_interface;
  _Bool is_private;
  _Bool is_anon;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

int32_t SPVM_PACKAGE_get_object_fields_length(SPVM_COMPILER* compiler, SPVM_PACKAGE* package);

#endif
