#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

void* SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp_no_managed(size_t byte_size) {
  
  if (byte_size < 1) {
    fprintf(stderr, "Failed to allocate memory. Size must be more than 0(%s)\n", __FILE__);
    abort();
  }
  
  if ((size_t)byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Size is too big(%s)\n", __FILE__);
    abort();
  }
  
  void* block = calloc(1, (size_t)byte_size);
  
  if (block == NULL) {
    fprintf(stderr, "Failed to allocate memory. malloc function return NULL(%s)\n", __FILE__);
    abort();
  }
  
  return block;
}

void SPVM_COMPILER_ALLOCATOR_free_tmp_no_managed(void* block) {
  free(block);
}

void* SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp(SPVM_COMPILER* compiler, int32_t byte_size) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;

  void* block = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp_no_managed(byte_size);

  assert(allocator);
  allocator->tmp_blocks_count++;

  return block;
}

void SPVM_COMPILER_ALLOCATOR_free_tmp(SPVM_COMPILER* compiler, void* block) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_COMPILER_ALLOCATOR_free_tmp_no_managed(block);
  
  allocator->tmp_blocks_count--;
}

const char* SPVM_COMPILER_ALLOCATOR_alloc_format_string(SPVM_COMPILER* compiler, const char* message_template, ...) {
  
  int32_t message_length = 0;
  
  // Message template
  int32_t message_template_length = (int32_t)strlen(message_template);
  
  va_list args;
  va_start(args, message_template);

  message_length += message_template_length;
  
  // Argument count
  char* found_ptr = (char*)message_template;
  while (1) {
    found_ptr = strchr(found_ptr, '%');
    if (found_ptr) {
      if (*(found_ptr + 1) == 's') {
        char* arg = va_arg(args, char*);
        message_length += strlen(arg);
      }
      else if (*(found_ptr + 1) == 'd') {
        (void) va_arg(args, int);
        message_length += 30;
      }
      else {
        assert(0);
      }
      found_ptr++;
    }
    else {
      break;
    }
  }
  va_end(args);
  
  char* message = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, message_length + 1);
  
  va_start(args, message_template);
  vsprintf(message, message_template, args);
  va_end(args);

  return message;
}

SPVM_COMPILER_ALLOCATOR* SPVM_COMPILER_ALLOCATOR_new() {
  
  SPVM_COMPILER_ALLOCATOR* allocator = calloc(1, sizeof(SPVM_COMPILER_ALLOCATOR));

  return allocator;
}

void SPVM_COMPILER_ALLOCATOR_init(SPVM_COMPILER* compiler) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  // Objects
  allocator->blocks = SPVM_LIST_new(compiler, 0);
  
  // Arrays
  allocator->lists = SPVM_LIST_new(compiler, 8);
  
  // Hashes
  allocator->hashes = SPVM_LIST_new(compiler, 8);
}

void* SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(SPVM_COMPILER* compiler, int32_t byte_size) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  void* block = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero_tmp_no_managed(byte_size);
  
  SPVM_LIST_push(allocator->blocks, block);
  
  return block;
}

SPVM_LIST* SPVM_COMPILER_ALLOCATOR_alloc_list(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_LIST* list = SPVM_LIST_new(compiler, capacity);
  
  SPVM_LIST_push(allocator->lists, list);
  
  return list;
}

SPVM_HASH* SPVM_COMPILER_ALLOCATOR_alloc_hash(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_HASH* hash = SPVM_HASH_new(compiler, capacity);
  
  SPVM_LIST_push(allocator->hashes, hash);
  
  return hash;
}

void SPVM_COMPILER_ALLOCATOR_free(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  // Free blocks
  int32_t i;
  for (i = 0; i < allocator->blocks->length; i++) {
    void* block = SPVM_LIST_fetch(allocator->blocks, i);
    if (block != NULL) {
      free(block);
    }
  }
  
  // Free lists
  {
    int32_t i;
    for (i = 0; i < allocator->lists->length; i++) {
      SPVM_LIST* list = SPVM_LIST_fetch(allocator->lists, i);
      if (list != NULL) {
        SPVM_LIST_free(list);
      }
    }
  }
  SPVM_LIST_free(allocator->lists);
  
  // Free hashes
  {
    int32_t i;
    for (i = 0; i < allocator->hashes->length; i++) {
      SPVM_HASH* hash = SPVM_LIST_fetch(allocator->hashes, i);
      if (hash != NULL) {
        SPVM_HASH_free(hash);
      }
    }
  }
  SPVM_LIST_free(allocator->hashes);

  free(allocator);
}
