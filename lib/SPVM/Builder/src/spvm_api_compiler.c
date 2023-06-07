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
#include "spvm_class.h"
#include "spvm_string_buffer.h"
#include "spvm_allocator.h"

SPVM_ENV_COMPILER* SPVM_API_COMPILER_new_env() {
  void* env_compiler_init[]  = {
    SPVM_API_COMPILER_new_object,
    SPVM_API_COMPILER_free_object,
    SPVM_API_COMPILER_set_start_line,
    SPVM_API_COMPILER_get_start_line,
    SPVM_API_COMPILER_set_start_file,
    SPVM_API_COMPILER_get_start_file,
    SPVM_API_COMPILER_add_class_path,
    SPVM_API_COMPILER_get_class_paths_length,
    SPVM_API_COMPILER_get_class_path,
    SPVM_API_COMPILER_compile,
    SPVM_API_COMPILER_get_error_messages_length,
    SPVM_API_COMPILER_get_error_message,
    SPVM_API_COMPILER_create_runtime_codes,
    SPVM_API_COMPILER_clear_class_paths,
  };
  SPVM_ENV_COMPILER* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

SPVM_COMPILER* SPVM_API_COMPILER_new_object() {
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  return compiler;
}

void SPVM_API_COMPILER_free_object(SPVM_COMPILER* compiler) {
  
  SPVM_COMPILER_free(compiler);
}

void SPVM_API_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line) {
  SPVM_COMPILER_set_start_line(compiler, start_line);
}

int32_t SPVM_API_COMPILER_get_start_line(SPVM_COMPILER* compiler) {  
  int32_t start_line = SPVM_COMPILER_get_start_line(compiler);
  return start_line;
}

void SPVM_API_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file) {
  SPVM_COMPILER_set_start_file(compiler, start_file);
}

const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler) {
  const char* start_file = SPVM_COMPILER_get_start_file(compiler);
  return start_file;
}

void SPVM_API_COMPILER_add_class_path(SPVM_COMPILER* compiler, const char* class_path) {  
  SPVM_COMPILER_add_class_path(compiler, class_path);
}

int32_t SPVM_API_COMPILER_get_class_paths_length (SPVM_COMPILER* compiler) {
  int32_t class_paths_length = SPVM_COMPILER_get_class_paths_length(compiler);
  return class_paths_length;
}

const char* SPVM_API_COMPILER_get_class_path (SPVM_COMPILER* compiler, int32_t class_path_id) {  
  const char* class_path = SPVM_COMPILER_get_class_path(compiler, class_path_id);
  return class_path;
}

void SPVM_API_COMPILER_clear_class_paths(SPVM_COMPILER* compiler) {
  SPVM_COMPILER_clear_class_paths(compiler);
}

int32_t SPVM_API_COMPILER_compile(SPVM_COMPILER* compiler, const char* class_name) {
  
  int32_t die_error_id = SPVM_COMPILER_compile(compiler, class_name);
  return die_error_id;
}

int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler) {  
  return SPVM_COMPILER_get_error_messages_length(compiler);
}

const char* SPVM_API_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index) {  
  return SPVM_COMPILER_get_error_message(compiler, index);
}

int32_t* SPVM_API_COMPILER_create_runtime_codes(SPVM_COMPILER* compiler, SPVM_ALLOCATOR* allocator) {
  
  int32_t* runtime_codes = SPVM_COMPILER_create_runtime_codes(compiler, allocator);
  
  return runtime_codes;
}
