// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include "spvm_typedecl.h"

struct spvm_runtime_basic_type {
  int32_t id;
  int32_t category;
  int32_t name_id;
  int32_t class_name_id;
  int32_t class_rel_file_id;
  int32_t class_path_id;
  int32_t init_method_id;
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
  int32_t fields_size;
  int32_t parent_class_basic_type_id;
  int32_t version_string_id;
  int8_t has_init_block;
  int8_t is_anon;
  int8_t is_pointer;
  int8_t is_class;
};

#endif
