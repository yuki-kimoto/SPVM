// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_COMPILER_H
#define SPVM_API_COMPILER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_COMPILER* SPVM_API_COMPILER_new_env();
SPVM_COMPILER* SPVM_API_COMPILER_new_object();
void SPVM_API_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line);
int32_t SPVM_API_COMPILER_get_start_line(SPVM_COMPILER* compiler);
void SPVM_API_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file);
const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler);
void SPVM_API_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir);
int32_t SPVM_API_COMPILER_get_include_dirs_length (SPVM_COMPILER* compiler);
const char* SPVM_API_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t index);
void SPVM_API_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler);
int32_t SPVM_API_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name);
void SPVM_API_COMPILER_free_object(SPVM_COMPILER* compiler);
int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler);
const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index);
int32_t* SPVM_API_COMPILER_create_runtime_codes(SPVM_COMPILER* compiler, SPVM_ALLOCATOR* allocator);

#endif
