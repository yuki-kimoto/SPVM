// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_compiler.h"
#include "spvm_api_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_method.h"
#include "spvm_string_buffer.h"
#include "spvm_allocator.h"
#include "spvm_string.h"
#include "spvm_class_file.h"

SPVM_API_COMPILER* SPVM_API_COMPILER_new_api() {
  void* env_compiler_init[]  = {
    SPVM_API_COMPILER_new_instance,
    SPVM_API_COMPILER_free_instance,
    SPVM_API_COMPILER_get_start_line,
    SPVM_API_COMPILER_set_start_line,
    SPVM_API_COMPILER_get_start_file,
    SPVM_API_COMPILER_set_start_file,
    SPVM_API_COMPILER_get_include_dirs_length,
    SPVM_API_COMPILER_get_include_dir,
    SPVM_API_COMPILER_add_include_dir,
    SPVM_API_COMPILER_clear_include_dirs,
    SPVM_API_COMPILER_add_class_file,
    SPVM_API_COMPILER_delete_class_file,
    SPVM_API_COMPILER_get_class_file,
    SPVM_API_COMPILER_compile,
    SPVM_API_COMPILER_get_error_message,
    SPVM_API_COMPILER_get_error_messages_length,
    SPVM_API_COMPILER_get_runtime,
    SPVM_API_COMPILER_prepend_include_dir,
    SPVM_API_COMPILER_compile_anon_class,
    SPVM_API_COMPILER_compile_script,
  };
  SPVM_API_COMPILER* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

SPVM_COMPILER* SPVM_API_COMPILER_new_instance() {
  return SPVM_COMPILER_new();
}

void SPVM_API_COMPILER_free_instance(SPVM_COMPILER* compiler) {
  SPVM_COMPILER_free(compiler);
}

int32_t SPVM_API_COMPILER_get_start_line(SPVM_COMPILER* compiler) {  
  return SPVM_COMPILER_get_start_line(compiler);
}

void SPVM_API_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line) {
  SPVM_COMPILER_set_start_line(compiler, start_line);
}

const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_get_start_file(compiler);
}

void SPVM_API_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file) {
  SPVM_COMPILER_set_start_file(compiler, start_file);
}

void SPVM_API_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir) {
  SPVM_COMPILER_add_include_dir(compiler, include_dir);
}

int32_t SPVM_API_COMPILER_get_include_dirs_length (SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_get_include_dirs_length(compiler);
}

const char* SPVM_API_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t index) {  
  return SPVM_COMPILER_get_include_dir(compiler, index);
}

void SPVM_API_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler) {
  SPVM_COMPILER_clear_include_dirs(compiler);
}

void SPVM_API_COMPILER_add_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  SPVM_COMPILER_add_class_file(compiler, class_name);
}

SPVM_CLASS_FILE* SPVM_API_COMPILER_get_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  return SPVM_COMPILER_get_class_file(compiler, class_name);
}

void SPVM_API_COMPILER_delete_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  SPVM_COMPILER_delete_class_file(compiler, class_name);
}

int32_t SPVM_API_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name) {
  return SPVM_COMPILER_compile(compiler, basic_type_name);
}

int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler) {  
  return SPVM_COMPILER_get_error_messages_length(compiler);
}

const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index) {  
  return SPVM_COMPILER_get_error_message(compiler, index);
}

SPVM_RUNTIME* SPVM_API_COMPILER_get_runtime(SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_get_runtime(compiler);
}

void SPVM_API_COMPILER_prepend_include_dir(SPVM_COMPILER* compiler, const char* include_dir) {
  SPVM_COMPILER_prepend_include_dir(compiler, include_dir);
}

void  SPVM_API_COMPILER_free_api(SPVM_API_COMPILER* api) {
  free(api);
}

int32_t SPVM_API_COMPILER_compile_anon_class(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr) {
  return SPVM_COMPILER_compile_anon_class(compiler, source, anon_basic_type_name_ptr);
}

int32_t SPVM_API_COMPILER_compile_script(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr) {
  return SPVM_COMPILER_compile_script(compiler, source, anon_basic_type_name_ptr);
}
