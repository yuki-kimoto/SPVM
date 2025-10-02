// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_COMPILER_H
#define SPVM_API_COMPILER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_COMPILER* SPVM_API_COMPILER_new_api();

SPVM_COMPILER* SPVM_API_COMPILER_new_instance();

void SPVM_API_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line);

int32_t SPVM_API_COMPILER_get_start_line(SPVM_COMPILER* compiler);

void SPVM_API_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file);

const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler);

void SPVM_API_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir);

void SPVM_API_COMPILER_prepend_include_dir(SPVM_COMPILER* compiler, const char* include_dir);

int32_t SPVM_API_COMPILER_get_include_dirs_length (SPVM_COMPILER* compiler);

const char* SPVM_API_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t index);

void SPVM_API_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler);

void SPVM_API_COMPILER_add_class_file(SPVM_COMPILER* compiler, const char* class_name);

SPVM_CLASS_FILE* SPVM_API_COMPILER_get_class_file(SPVM_COMPILER* compiler, const char* class_name);

void SPVM_API_COMPILER_set_class_file(SPVM_COMPILER* compiler, const char* class_name, SPVM_CLASS_FILE* class_file);

void SPVM_API_COMPILER_delete_class_file(SPVM_COMPILER* compiler, const char* class_name);

int32_t SPVM_API_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name);

void SPVM_API_COMPILER_free_instance(SPVM_COMPILER* compiler);

int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler);

const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index);

SPVM_RUNTIME* SPVM_API_COMPILER_get_runtime(SPVM_COMPILER* compiler);

void  SPVM_API_COMPILER_free_api(SPVM_API_COMPILER* api);

int32_t SPVM_API_COMPILER_compile_anon_class(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr);

int32_t SPVM_API_COMPILER_compile_script(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr);

#endif
