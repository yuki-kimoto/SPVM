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
#include "spvm_module_file.h"

SPVM_API_COMPILER* SPVM_API_COMPILER_new_api() {
  void* env_compiler_init[]  = {
    SPVM_API_COMPILER_new_instance,
    SPVM_API_COMPILER_free_instance,
    SPVM_API_COMPILER_set_start_line,
    SPVM_API_COMPILER_get_start_line,
    SPVM_API_COMPILER_set_start_file,
    SPVM_API_COMPILER_get_start_file,
    SPVM_API_COMPILER_add_include_dir,
    SPVM_API_COMPILER_get_include_dirs_length,
    SPVM_API_COMPILER_get_include_dir,
    SPVM_API_COMPILER_compile,
    SPVM_API_COMPILER_get_error_messages_length,
    SPVM_API_COMPILER_get_error_message,
    NULL, // reserved12
    SPVM_API_COMPILER_clear_include_dirs,
    SPVM_API_COMPILER_get_module_file,
    SPVM_API_COMPILER_set_module_file,
    SPVM_API_COMPILER_get_runtime,
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
  assert(include_dir);
  
  if (include_dir) {
    SPVM_STRING* include_dir_string = SPVM_STRING_new(compiler, include_dir, strlen(include_dir));
    SPVM_COMPILER_add_include_dir(compiler, include_dir_string->value);
  }
}

int32_t SPVM_API_COMPILER_get_include_dirs_length (SPVM_COMPILER* compiler) {
  return SPVM_COMPILER_get_include_dirs_length(compiler);
}

const char* SPVM_API_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t include_dir_id) {  
  return SPVM_COMPILER_get_include_dir(compiler, include_dir_id);
}

void SPVM_API_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler) {
  SPVM_COMPILER_clear_include_dirs(compiler);
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

SPVM_MODULE_FILE* SPVM_API_COMPILER_get_module_file(SPVM_COMPILER* compiler, const char* module_name) {
  return SPVM_COMPILER_get_module_file(compiler, module_name);
}

void SPVM_API_COMPILER_set_module_file(SPVM_COMPILER* compiler, const char* module_name, SPVM_MODULE_FILE* module_file) {
  if (module_name) {
    SPVM_STRING* module_name_string = SPVM_STRING_new(compiler, module_name, strlen(module_name));
    module_name = module_name_string->value;
  }
  
  SPVM_COMPILER_set_module_file(compiler, module_name, module_file);
  
  return;
}

void  SPVM_API_COMPILER_free_api(SPVM_API_COMPILER* api) {
  free(api);
}
