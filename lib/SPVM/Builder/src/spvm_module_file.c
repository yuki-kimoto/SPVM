// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>
#include <string.h>

#include "spvm_module_file.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_string.h"

SPVM_MODULE_FILE* SPVM_MODULE_FILE_new(SPVM_COMPILER* compiler) {
  
  return SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, sizeof(SPVM_MODULE_FILE));
}

const char* SPVM_MODULE_FILE_get_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* module_name = module_file->module_name;
  return module_name;
}

void SPVM_MODULE_FILE_set_module_name(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* module_name) {
  if (module_file->module_name) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, (void*)module_file->module_name);
    module_file->module_name = NULL;
  }
  
  if (module_name) {
    int32_t module_name_length = strlen(module_name);
    module_file->module_name = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, module_name_length + 1);
    memcpy((void*)module_file->module_name, module_name, module_name_length);
  }
}

const char* SPVM_MODULE_FILE_get_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* file = module_file->file;
  return file;
}

void SPVM_MODULE_FILE_set_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* file) {
  if (module_file->file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, (void*)module_file->file);
    module_file->file = NULL;
  }
  
  if (file) {
    int32_t file_length = strlen(file);
    module_file->file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, file_length + 1);
    memcpy((void*)module_file->file, file, file_length);
  }
}

const char* SPVM_MODULE_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* dir = module_file->dir;
  return dir;
}

void SPVM_MODULE_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* dir) {
  if (module_file->dir) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, (void*)module_file->dir);
    module_file->dir = NULL;
  }
  
  if (dir) {
    int32_t dir_length = strlen(dir);
    module_file->dir = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, dir_length + 1);
    memcpy((void*)module_file->dir, dir, dir_length);
  }
}

const char* SPVM_MODULE_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* rel_file = module_file->rel_file;
  return rel_file;
}

void SPVM_MODULE_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* rel_file) {
  if (rel_file) {
    SPVM_STRING* rel_file_string = SPVM_STRING_new(compiler, rel_file, strlen(rel_file));
    module_file->rel_file = rel_file_string->value;
  }
  else {
    module_file->rel_file = NULL;
  }
}

const char* SPVM_MODULE_FILE_get_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  const char* content = module_file->content;
  return content;
}

void SPVM_MODULE_FILE_set_content(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, const char* content) {
  if (content) {
    SPVM_STRING* content_string = SPVM_STRING_new(compiler, content, strlen(content));
    module_file->content = content_string->value;
  }
  else {
    module_file->content = NULL;
  }
}

int32_t SPVM_MODULE_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file) {  
  int32_t content_length = module_file->content_length;
  return content_length;
}

void SPVM_MODULE_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_MODULE_FILE* module_file, int32_t content_length) {
  module_file->content_length = content_length;
}
