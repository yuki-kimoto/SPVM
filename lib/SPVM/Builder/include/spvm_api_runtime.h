// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_RUNTIME* SPVM_API_RUNTIME_new_api();

void SPVM_API_RUNTIME_free_api(SPVM_API_RUNTIME* api);

SPVM_RUNTIME* SPVM_API_RUNTIME_new_instance();

void SPVM_API_RUNTIME_free_instance(SPVM_RUNTIME* runtime);

// SPVM_OBJECT information
int32_t SPVM_API_RUNTIME_get_object_data_offset(SPVM_RUNTIME* runtime);

int32_t SPVM_API_RUNTIME_get_object_ref_count_offset(SPVM_RUNTIME* runtime);

int32_t SPVM_API_RUNTIME_get_object_length_offset(SPVM_RUNTIME* runtime);

// Basic type
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);

SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);

int32_t SPVM_API_RUNTIME_get_basic_types_length(SPVM_RUNTIME* runtime);

// Type utility
int32_t SPVM_API_RUNTIME_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);

int32_t SPVM_API_RUNTIME_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t dimension, int32_t flag);

int32_t SPVM_API_RUNTIME_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t flag);

// Precompile
void SPVM_API_RUNTIME_build_precompile_class_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_BASIC_TYPE* module_basic_type);

void SPVM_API_RUNTIME_build_precompile_method_source(SPVM_RUNTIME* runtime, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_METHOD* method);

SPVM_COMPILER* SPVM_API_RUNTIME_get_compiler(SPVM_RUNTIME* runtime);

void SPVM_API_RUNTIME_set_compiler(SPVM_RUNTIME* runtime, SPVM_COMPILER* compiler);

FILE* SPVM_API_RUNTIME_get_spvm_stdin(SPVM_RUNTIME* runtime);

FILE* SPVM_API_RUNTIME_get_spvm_stdout(SPVM_RUNTIME* runtime);

FILE* SPVM_API_RUNTIME_get_spvm_stderr(SPVM_RUNTIME* runtime);

#endif
