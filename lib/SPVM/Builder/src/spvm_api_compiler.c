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

SPVM_ENV_COMPILER* SPVM_API_COMPILER_new_env() {
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
    SPVM_API_COMPILER_create_runtime_codes,
    SPVM_API_COMPILER_clear_include_dirs,
  };
  SPVM_ENV_COMPILER* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

SPVM_COMPILER* SPVM_API_COMPILER_new_instance() {
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  return compiler;
}

void SPVM_API_COMPILER_free_instance(SPVM_COMPILER* compiler) {
  
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
  if (start_file) {
    SPVM_STRING* start_file_string = SPVM_STRING_new(compiler, start_file, strlen(start_file));
    SPVM_COMPILER_set_start_file(compiler, start_file_string->value);
  }
  else {
    SPVM_COMPILER_set_start_file(compiler, NULL);
  }
}

const char* SPVM_API_COMPILER_get_start_file(SPVM_COMPILER* compiler) {
  const char* start_file = SPVM_COMPILER_get_start_file(compiler);
  return start_file;
}

void SPVM_API_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir) {
  assert(include_dir);
  
  if (include_dir) {
    SPVM_STRING* include_dir_string = SPVM_STRING_new(compiler, include_dir, strlen(include_dir));
    SPVM_COMPILER_add_include_dir(compiler, include_dir_string->value);
  }
}

int32_t SPVM_API_COMPILER_get_include_dirs_length (SPVM_COMPILER* compiler) {
  int32_t include_dirs_length = SPVM_COMPILER_get_include_dirs_length(compiler);
  return include_dirs_length;
}

const char* SPVM_API_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t include_dir_id) {  
  const char* include_dir = SPVM_COMPILER_get_include_dir(compiler, include_dir_id);
  return include_dir;
}

void SPVM_API_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler) {
  SPVM_COMPILER_clear_include_dirs(compiler);
}

int32_t SPVM_API_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name) {
  
  int32_t die_error_id = SPVM_COMPILER_compile(compiler, basic_type_name);
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

void SPVM_API_COMPILER_add_module_file(
  SPVM_COMPILER* compiler,
  const char* module_name,
  const char* file,
  const char* dir,
  const char* rel_file,
  const char* content,
  int32_t content_length
) {
  
  SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
  
  if (module_name) {
    SPVM_STRING* module_name_string = SPVM_STRING_new(compiler, module_name, strlen(module_name));
    module_file->module_name = module_name_string->value;
  }
  
  if (file) {
    SPVM_STRING* file_string = SPVM_STRING_new(compiler, file, strlen(file));
    module_file->file = file_string->value;
  }
  
  if (dir) {
    SPVM_STRING* dir_string = SPVM_STRING_new(compiler, dir, strlen(dir));
    module_file->dir = dir_string->value;
  }
  
  if (rel_file) {
    SPVM_STRING* rel_file_string = SPVM_STRING_new(compiler, rel_file, strlen(rel_file));
    module_file->rel_file = rel_file_string->value;
  }
  
  if (content) {
    SPVM_STRING* content_string = SPVM_STRING_new(compiler, content, content_length);
    module_file->content = content_string->value;
  }
  
  module_file->content_length = content_length;
  
  SPVM_COMPILER_add_module_file(compiler, module_name, module_file);
  
  return;
}
