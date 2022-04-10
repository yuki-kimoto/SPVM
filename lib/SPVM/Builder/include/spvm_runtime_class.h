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
  int32_t methods_base_id;
  int32_t methods_length;
  int32_t anon_methods_base_id;
  int32_t anon_methods_length;
  int32_t fields_base_id;
  int32_t fields_length;
  int32_t class_vars_base_id;
  int32_t class_vars_length;
  int32_t interface_classes_base_id;
  int32_t interface_classes_length;
  int8_t has_init_block;
  int8_t is_anon;
};

#endif
 