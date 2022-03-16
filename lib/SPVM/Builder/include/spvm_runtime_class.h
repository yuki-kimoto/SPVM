#ifndef SPVM_RUNTIME_CLASS_H
#define SPVM_RUNTIME_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_class {
  int32_t name_id;
  int32_t module_file_id;
  int32_t id;
  int32_t method_destructor_id;
  int32_t flag;
  int32_t object_fields_length;
  int32_t object_fields_offset;
  int32_t type_id;
  int32_t method_ids_base;
  int32_t method_ids_length;
  int32_t field_ids_base;
  int32_t field_ids_length;
  int32_t class_var_ids_base;
  int32_t class_var_ids_length;
  int32_t interface_class_ids_base;
  int32_t interface_class_ids_length;
  int8_t has_init_block;
  int8_t is_anon;
};

#endif
 