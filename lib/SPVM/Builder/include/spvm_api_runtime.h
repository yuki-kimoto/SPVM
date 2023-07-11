// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_RUNTIME* SPVM_API_RUNTIME_new_api();

// Runtime
SPVM_RUNTIME* SPVM_API_RUNTIME_new_instance();
void SPVM_API_RUNTIME_free_instance(SPVM_RUNTIME* runtime);

// Basic type
int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);

int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_module_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_module_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
int32_t SPVM_API_RUNTIME_get_basic_type_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
const char* SPVM_API_RUNTIME_get_basic_type_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_anon_basic_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index);

// Type utility
int32_t SPVM_API_RUNTIME_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);
int32_t SPVM_API_RUNTIME_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_BASIC_TYPE* interface_basic_type);

int32_t SPVM_API_RUNTIME_is_super_class(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* super_basic_type, SPVM_RUNTIME_BASIC_TYPE* child_basic_type);
int32_t SPVM_API_RUNTIME_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

void SPVM_API_RUNTIME_build_precompile_module_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name);

void SPVM_API_RUNTIME_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, const char* module_name, const char* method_name);

void SPVM_API_RUNTIME_free_api(SPVM_API_RUNTIME* api);

#endif
