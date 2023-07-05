// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api_module_file.h"
#include "spvm_compiler.h"
#include "spvm_string.h"
#include "spvm_module_file.h"

SPVM_ENV_MODULE_FILE* SPVM_API_MODULE_FILE_new_env(void) {
  void* env_compiler_init[]  = {
    SPVM_API_MODULE_FILE_new_env,
    SPVM_API_MODULE_FILE_new_instance,
    SPVM_API_MODULE_FILE_get_module_name,
    SPVM_API_MODULE_FILE_set_module_name,
    SPVM_API_MODULE_FILE_get_module_name,
    SPVM_API_MODULE_FILE_set_file,
    SPVM_API_MODULE_FILE_get_dir,
    SPVM_API_MODULE_FILE_set_dir,
    SPVM_API_MODULE_FILE_get_rel_file,
    SPVM_API_MODULE_FILE_set_rel_file,
    SPVM_API_MODULE_FILE_get_content,
    SPVM_API_MODULE_FILE_set_content,
    SPVM_API_MODULE_FILE_get_content_length,
    SPVM_API_MODULE_FILE_set_content_length,
  };
  SPVM_ENV_MODULE_FILE* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

SPVM_MODULE_FILE* SPVM_API_MODULE_FILE_new_instance(SPVM_COMPILER* compiler) {
  
  SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
  
  return module_file;
}

const char* SPVM_API_MODULE_FILE_get_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* module_name = module_file->module_name;
  return module_name;
}

void SPVM_API_MODULE_FILE_set_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* module_name) {
  if (module_name) {
    SPVM_STRING* module_name_string = SPVM_STRING_new(compiler, module_name, strlen(module_name));
    module_file->module_name = module_name_string->value;
  }
  else {
    module_file->module_name = NULL;
  }
}

void SPVM_API_MODULE_FILE_set_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* file) {
  if (file) {
    SPVM_STRING* file_string = SPVM_STRING_new(compiler, file, strlen(file));
    module_file->file = file_string->value;
  }
  else {
    module_file->file = NULL;
  }
}

const char* SPVM_API_MODULE_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* dir = module_file->dir;
  return dir;
}

void SPVM_API_MODULE_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* dir) {
  if (dir) {
    SPVM_STRING* dir_string = SPVM_STRING_new(compiler, dir, strlen(dir));
    module_file->dir = dir_string->value;
  }
  else {
    module_file->dir = NULL;
  }
}

const char* SPVM_API_MODULE_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* rel_file = module_file->rel_file;
  return rel_file;
}

void SPVM_API_MODULE_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* rel_file) {
  if (rel_file) {
    SPVM_STRING* rel_file_string = SPVM_STRING_new(compiler, rel_file, strlen(rel_file));
    module_file->rel_file = rel_file_string->value;
  }
  else {
    module_file->rel_file = NULL;
  }
}

const char* SPVM_API_MODULE_FILE_get_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* content = module_file->content;
  return content;
}

void SPVM_API_MODULE_FILE_set_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* content) {
  if (content) {
    SPVM_STRING* content_string = SPVM_STRING_new(compiler, content, strlen(content));
    module_file->content = content_string->value;
  }
  else {
    module_file->content = NULL;
  }
}

int32_t SPVM_API_MODULE_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  int32_t content_length = module_file->content_length;
  return content_length;
}

void SPVM_API_MODULE_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, int32_t content_length) {
  module_file->content_length = content_length;
}

