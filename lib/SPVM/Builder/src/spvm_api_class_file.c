// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api_class_file.h"
#include "spvm_compiler.h"
#include "spvm_string.h"
#include "spvm_class_file.h"
#include "spvm_class_file.h"

SPVM_API_CLASS_FILE* SPVM_API_CLASS_FILE_new_api(void) {
  void* env_compiler_init[]  = {
    SPVM_API_CLASS_FILE_get_class_name,
    SPVM_API_CLASS_FILE_get_file,
    SPVM_API_CLASS_FILE_set_file,
    SPVM_API_CLASS_FILE_get_dir,
    SPVM_API_CLASS_FILE_set_dir,
    SPVM_API_CLASS_FILE_get_rel_file,
    SPVM_API_CLASS_FILE_set_rel_file,
    SPVM_API_CLASS_FILE_get_content,
    SPVM_API_CLASS_FILE_set_content,
    SPVM_API_CLASS_FILE_get_content_length,
    SPVM_API_CLASS_FILE_set_content_length,
  };
  SPVM_API_CLASS_FILE* env_compiler = calloc(1, sizeof(env_compiler_init));
  memcpy(env_compiler, env_compiler_init, sizeof(env_compiler_init));
  
  return env_compiler;
}

void SPVM_API_CLASS_FILE_free_api(SPVM_API_CLASS_FILE* api) {
  free(api);
}

const char* SPVM_API_CLASS_FILE_get_class_name(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_class_name(compiler, class_file);
}

const char* SPVM_API_CLASS_FILE_get_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_file(compiler, class_file);
}

void SPVM_API_CLASS_FILE_set_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* file) {
  SPVM_CLASS_FILE_set_file(compiler, class_file, file);
}

const char* SPVM_API_CLASS_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_dir(compiler, class_file);
}

void SPVM_API_CLASS_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* dir) {
  SPVM_CLASS_FILE_set_dir(compiler, class_file, dir);
}

const char* SPVM_API_CLASS_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_rel_file(compiler, class_file);
}

void SPVM_API_CLASS_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* rel_file) {
  SPVM_CLASS_FILE_set_rel_file(compiler, class_file, rel_file);
}

const char* SPVM_API_CLASS_FILE_get_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_content(compiler, class_file);
}

void SPVM_API_CLASS_FILE_set_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* content) {
  SPVM_CLASS_FILE_set_content(compiler, class_file, content);
}

int32_t SPVM_API_CLASS_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  return SPVM_CLASS_FILE_get_content_length(compiler, class_file);
}

void SPVM_API_CLASS_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, int32_t content_length) {
  SPVM_CLASS_FILE_set_content_length(compiler, class_file, content_length);
}

