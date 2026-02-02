// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_BASIC_TYPE_H
#define SPVM_API_BASIC_TYPE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_BASIC_TYPE* SPVM_API_BASIC_TYPE_new_api();

void SPVM_API_BASIC_TYPE_free_api(SPVM_API_BASIC_TYPE* api);

const char* SPVM_API_BASIC_TYPE_get_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_get_id(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_get_category(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_parent(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

const char* SPVM_API_BASIC_TYPE_get_version_string(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

const char* SPVM_API_BASIC_TYPE_get_class_dir(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

const char* SPVM_API_BASIC_TYPE_get_class_rel_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_is_pointer(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_is_anon(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_CLASS_VAR* SPVM_API_BASIC_TYPE_get_class_var_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t class_var_index);

SPVM_RUNTIME_CLASS_VAR* SPVM_API_BASIC_TYPE_get_class_var_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* class_var_name);

int32_t SPVM_API_BASIC_TYPE_get_class_vars_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_FIELD* SPVM_API_BASIC_TYPE_get_field_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t field_index);

SPVM_RUNTIME_FIELD* SPVM_API_BASIC_TYPE_get_field_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* field_name);

int32_t SPVM_API_BASIC_TYPE_get_fields_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_METHOD* SPVM_API_BASIC_TYPE_get_method_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t method_index);

SPVM_RUNTIME_METHOD* SPVM_API_BASIC_TYPE_get_method_by_name(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, const char* method_name);

int32_t SPVM_API_BASIC_TYPE_get_methods_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_anon_basic_type_by_index(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t anon_basic_type_index);

int32_t SPVM_API_BASIC_TYPE_get_anon_basic_types_length(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_has_interface(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_BASIC_TYPE* interface_basic_type);

int32_t SPVM_API_BASIC_TYPE_check_method_compatibility(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, SPVM_RUNTIME_METHOD* method, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, SPVM_RUNTIME_METHOD* dist_method);

int32_t SPVM_API_BASIC_TYPE_is_class_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_is_super_class(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, SPVM_RUNTIME_BASIC_TYPE* src_basic_type);

int32_t SPVM_API_BASIC_TYPE_can_assign_for_method_definition (
  SPVM_RUNTIME* runtime,
  SPVM_RUNTIME_BASIC_TYPE* dist_type_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag,
  SPVM_RUNTIME_BASIC_TYPE* src_type_basic_type, int32_t src_type_dimension, int32_t src_type_flag
);

const char* SPVM_API_BASIC_TYPE_get_file(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME* SPVM_API_BASIC_TYPE_get_current_runtime(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_BASIC_TYPE_get_basic_type_in_version_from(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_get_fields_size(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_BASIC_TYPE_get_monitor_var_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t* ret_basic_type_id, int32_t* ret_dimension, int32_t* ret_flag);

int32_t SPVM_API_BASIC_TYPE_has_monitor_var(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type);

#endif
