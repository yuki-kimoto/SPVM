// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <assert.h>
#include <string.h>

#include "spvm_class_file.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_string.h"

SPVM_CLASS_FILE* SPVM_CLASS_FILE_new(SPVM_COMPILER* compiler) {
  
  return SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->class_file_allocator, sizeof(SPVM_CLASS_FILE));
}

SPVM_CLASS_FILE* SPVM_CLASS_FILE_clone(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {
  
  SPVM_CLASS_FILE* class_file_clone = SPVM_CLASS_FILE_new(compiler);
  
  class_file_clone->class_name = class_file->class_name;
  
  SPVM_CLASS_FILE_set_file(compiler, class_file_clone, class_file->file);
  
  SPVM_CLASS_FILE_set_dir(compiler, class_file_clone, class_file->dir);
  
  SPVM_CLASS_FILE_set_rel_file(compiler, class_file_clone, class_file->rel_file);
  
  SPVM_CLASS_FILE_set_content(compiler, class_file_clone, class_file->content);
  
  class_file_clone->content_length = class_file->content_length;
  
  return class_file_clone;
}

const char* SPVM_CLASS_FILE_get_class_name(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  const char* class_name = class_file->class_name;
  return class_name;
}

const char* SPVM_CLASS_FILE_get_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  const char* file = class_file->file;
  return file;
}

void SPVM_CLASS_FILE_set_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* file) {
  if (class_file->file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, (void*)class_file->file);
    class_file->file = NULL;
  }
  
  if (file) {
    int32_t file_length = strlen(file);
    class_file->file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, file_length + 1);
    memcpy((void*)class_file->file, file, file_length);
  }
}

const char* SPVM_CLASS_FILE_get_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  const char* dir = class_file->dir;
  return dir;
}

void SPVM_CLASS_FILE_set_dir(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* dir) {
  if (class_file->dir) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, (void*)class_file->dir);
    class_file->dir = NULL;
  }
  
  if (dir) {
    int32_t dir_length = strlen(dir);
    class_file->dir = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, dir_length + 1);
    memcpy((void*)class_file->dir, dir, dir_length);
  }
}

const char* SPVM_CLASS_FILE_get_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  const char* rel_file = class_file->rel_file;
  return rel_file;
}

void SPVM_CLASS_FILE_set_rel_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* rel_file) {
  if (class_file->rel_file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, (void*)class_file->rel_file);
    class_file->rel_file = NULL;
  }
  
  if (rel_file) {
    int32_t rel_file_length = strlen(rel_file);
    class_file->rel_file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, rel_file_length + 1);
    memcpy((void*)class_file->rel_file, rel_file, rel_file_length);
  }
}

const char* SPVM_CLASS_FILE_get_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  const char* content = class_file->content;
  return content;
}

void SPVM_CLASS_FILE_set_content(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, const char* content) {
  if (class_file->content) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, (void*)class_file->content);
    class_file->content = NULL;
  }
  
  if (content) {
    int32_t content_length = strlen(content);
    class_file->content = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, content_length + 1);
    memcpy((void*)class_file->content, content, content_length);
  }
}

int32_t SPVM_CLASS_FILE_get_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {  
  int32_t content_length = class_file->content_length;
  return content_length;
}

void SPVM_CLASS_FILE_set_content_length(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file, int32_t content_length) {
  class_file->content_length = content_length;
}
