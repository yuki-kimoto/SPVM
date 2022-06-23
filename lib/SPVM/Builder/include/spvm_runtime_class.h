#ifndef SPVM_RUNTIME_CLASS_H
#define SPVM_RUNTIME_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_class {
  int32_t name_id;
  int32_t module_rel_file_id;
  int32_t module_dir_id;
  int32_t id;
  int32_t destructor_method_id;
  int32_t required_method_id;
  int32_t type_id;
  int32_t methods_base_id;
  int32_t methods_length;
  int32_t anon_methods_base_id;
  int32_t anon_methods_length;
  int32_t fields_base_id;
  int32_t fields_length;
  int32_t class_vars_base_id;
  int32_t class_vars_length;
  int32_t interfaces_base_id;
  int32_t interfaces_length;
  int32_t fields_byte_size;
  int32_t parent_class_id;
  int8_t has_init_block;
  int8_t is_anon;
  int8_t is_pointer;
};

#endif
