// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include "spvm_typedecl.h"

struct spvm_runtime_basic_type {
  int32_t id;
  int32_t category;
  int32_t name_string_address_id;
  int32_t name_string_index;
  int32_t module_dir_string_address_id;
  int32_t module_dir_string_index;
  int32_t module_rel_file_string_address_id;
  int32_t module_rel_file_string_index;
  int32_t version_string_string_address_id;
  int32_t version_string_string_index;
  int32_t parent_id;
  int32_t string_pool_base;
  int32_t string_pool_length;
  int32_t constant_strings_base;
  int32_t constant_strings_length;
  int32_t class_vars_base;
  int32_t class_vars_length;
  int32_t fields_base;
  int32_t fields_length;
  int32_t fields_size;
  int32_t methods_base;
  int32_t methods_length;
  int32_t init_method_index;
  int32_t destructor_method_index;
  int32_t required_method_index;
  int32_t anon_basic_types_base;
  int32_t anon_basic_types_length;
  int8_t is_anon;
  int8_t is_pointer;
  int8_t initialized;
};

#endif
