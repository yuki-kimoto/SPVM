// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_BASIC_TYPE_H
#define SPVM_RUNTIME_BASIC_TYPE_H

#include "spvm_typedecl.h"

struct spvm_runtime_basic_type {
  const char* name;
  const char* module_dir;
  const char* module_rel_file;
  const char* version_string;
  SPVM_RUNTIME_BASIC_TYPE* parent;
  const char* string_pool;
  SPVM_RUNTIME_STRING* constant_strings;
  SPVM_RUNTIME_CLASS_VAR* class_vars;
  SPVM_RUNTIME_FIELD* fields;
  SPVM_RUNTIME_METHOD* methods;
  SPVM_RUNTIME_METHOD* init_method;
  SPVM_RUNTIME_METHOD* destructor_method;
  SPVM_RUNTIME_METHOD* required_method;
  SPVM_RUNTIME_BASIC_TYPE* anon_basic_types;
  int32_t id;
  int32_t category;
  int32_t string_pool_length;
  int32_t constant_strings_length;
  int32_t class_vars_length;
  int32_t fields_length;
  int32_t fields_size;
  int32_t methods_length;
  int32_t anon_basic_types_length;
  int8_t is_anon;
  int8_t is_pointer;
  int8_t initialized;
};

#endif
