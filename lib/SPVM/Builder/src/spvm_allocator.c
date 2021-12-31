#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new() {
  
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new_block_unmanaged(sizeof(SPVM_ALLOCATOR));

  assert(allocator->memory_blocks_count == 0);

  return allocator;
}

void SPVM_ALLOCATOR_init(SPVM_COMPILER* compiler) {
  (void)compiler;

  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  // Arrays
  allocator->lists = SPVM_LIST_new(compiler, 8, 0);

  // Objects
  allocator->blocks = SPVM_LIST_new(compiler, 0, 0);
  
  // Hashes
  allocator->hashes = SPVM_ALLOCATOR_new_list_compile_eternal(compiler, 8);
}

void* SPVM_ALLOCATOR_new_block_unmanaged(size_t byte_size) {
  
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

void SPVM_ALLOCATOR_free_block_unmanaged(void* block) {
  free(block);
}

void* SPVM_ALLOCATOR_new_block_compile_tmp(SPVM_COMPILER* compiler, int32_t byte_size) {
  (void)compiler;
  
  SPVM_ALLOCATOR* allocator = compiler->allocator;

  void* block = SPVM_ALLOCATOR_new_block_unmanaged(byte_size);

  assert(allocator);
  allocator->memory_blocks_count++;
  allocator->tmp_memory_blocks_count++;

  return block;
}

void SPVM_ALLOCATOR_free_block_compile_tmp(SPVM_COMPILER* compiler, void* block) {
  (void)compiler;

  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_ALLOCATOR_free_block_unmanaged(block);
  
  allocator->memory_blocks_count--;
  allocator->tmp_memory_blocks_count--;
}

void SPVM_ALLOCATOR_free_block_compile_eternal(SPVM_COMPILER* compiler, void* block) {
  (void)compiler;

  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_ALLOCATOR_free_block_unmanaged(block);
  
  allocator->memory_blocks_count--;
}

void* SPVM_ALLOCATOR_new_block_compile_eternal(SPVM_COMPILER* compiler, int32_t byte_size) {
  (void)compiler;
  
  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  void* block = SPVM_ALLOCATOR_new_block_unmanaged(byte_size);
  allocator->memory_blocks_count++;
  
  SPVM_LIST_push(allocator->blocks, block);
  
  return block;
}

SPVM_LIST* SPVM_ALLOCATOR_new_list_compile_eternal(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  int32_t memory_block_type = SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL;
  SPVM_LIST* list = SPVM_LIST_new(compiler, capacity, memory_block_type);
  
  SPVM_LIST_push(allocator->lists, list);
  
  return list;
}

SPVM_HASH* SPVM_ALLOCATOR_new_hash_compile_eternal(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  int32_t memory_block_type = SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL;
  SPVM_HASH* hash = SPVM_HASH_new(compiler, capacity, memory_block_type);
  
  SPVM_LIST_push(allocator->hashes, hash);
  
  return hash;
}

void SPVM_ALLOCATOR_free(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_ALLOCATOR* allocator = compiler->allocator;
  
  // Free blocks
  int32_t i;
  for (i = 0; i < allocator->blocks->length; i++) {
    void* block = SPVM_LIST_fetch(allocator->blocks, i);
    if (block != NULL) {
      SPVM_ALLOCATOR_free_block_compile_eternal(compiler, block);
    }
  }
  SPVM_LIST_free(allocator->blocks);
  
  // Free lists
  SPVM_LIST_free(allocator->lists);
  
  assert(allocator->memory_blocks_count == 0);
  assert(allocator->tmp_memory_blocks_count == 0);

  SPVM_ALLOCATOR_free_block_unmanaged(allocator);
}
