#ifndef SPVM_RUNTIME_CLASS_H
#define SPVM_RUNTIME_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_class {
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
  SPVM_LIST* fields;
  int32_t type_id;
};

#endif
 