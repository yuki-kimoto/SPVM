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
#include "spvm_module_file.h"

SPVM_API_MODULE_FILE* SPVM_API_MODULE_FILE_new_api(void) {
  void* env_compiler_init[]  = {
    SPVM_API_MODULE_FILE_new_instance,
    SPVM_API_MODULE_FILE_get_module_name,
    SPVM_API_MODULE_FILE_set_module_name,
    SPVM_API_MODULE_FILE_get_file,
    SPVM_API_MODULE_FILE_set_file,
    SPVM_API_MODULE_FILE_get_dir,
    SPVM_API_MODULE_FILE_set_dir,
    SPVM_API_MODULE_FILE_get_rel_file,
    SPVM_API_MODULE_FILE_set_rel_file,
    SPVM_API_MODULE_FILE_get_content,
    SPVM_API_MODULE_FILE_set_content,
    SPVM_API_MODULE_FILE_get_content_length,
    SPVM_API_MODULE_FILE_set_content_length,
    SPVM_API_MODULE_FILE_free_instance_v2,
    SPVM_API_MODULE_FILE_new_instance_v2,
  };
  SPVM_API_MODULE_FILE* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

void SPVM_API_MODULE_FILE_free_api(SPVM_API_MODULE_FILE* api) {
  free(api);
}

SPVM_MODULE_FILE* SPVM_API_MODULE_FILE_new_instance(SPVM_COMPILER* compiler) {
  
  return SPVM_MODULE_FILE_new(compiler);
}

SPVM_MODULE_FILE* SPVM_API_MODULE_FILE_new_instance_v2(SPVM_COMPILER* compiler, const char* module_name) {
  
  SPVM_COMPILER_new_module_file(compiler, module_name);
  
  SPVM_MODULE_FILE* module_file = SPVM_COMPILER_get_module_file(compiler, module_name);
  
  return module_file;
}

void SPVM_API_MODULE_FILE_free_instance_v2(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {
  
  SPVM_MODULE_FILE_free_v2(compiler, module_file);
}

const char* SPVM_API_MODULE_FILE_get_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_module_name(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* module_name) {
  SPVM_MODULE_FILE_set_module_name(compiler, module_file, module_name);
}

const char* SPVM_API_MODULE_FILE_get_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_file(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* file) {
  SPVM_MODULE_FILE_set_file(compiler, module_file, file);
}

const char* SPVM_API_MODULE_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_dir(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* dir) {
  SPVM_MODULE_FILE_set_dir(compiler, module_file, dir);
}

const char* SPVM_API_MODULE_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_rel_file(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* rel_file) {
  SPVM_MODULE_FILE_set_rel_file(compiler, module_file, rel_file);
}

const char* SPVM_API_MODULE_FILE_get_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_content(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* content) {
  SPVM_MODULE_FILE_set_content(compiler, module_file, content);
}

int32_t SPVM_API_MODULE_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  return SPVM_MODULE_FILE_get_content_length(compiler, module_file);
}

void SPVM_API_MODULE_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, int32_t content_length) {
  SPVM_MODULE_FILE_set_content_length(compiler, module_file, content_length);
}

