#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_allocator.h"
#include "spvm_native.h"

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new() {
  
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_ALLOCATOR));

  assert(allocator->memory_blocks_count_tmp == 0);
  assert(allocator->memory_blocks_count_permanent == 0);

  allocator->permanent_memory_blocks = SPVM_LIST_new(allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

  return allocator;
}

int32_t SPVM_ALLOCATOR_get_memory_blocks_count(SPVM_ALLOCATOR* allocator) {
  int32_t memory_blocks_count = allocator->memory_blocks_count_tmp + allocator->memory_blocks_count_permanent;
  
  return memory_blocks_count;
}

void* SPVM_ALLOCATOR_alloc_memory_block_unmanaged(size_t byte_size) {
  
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

void SPVM_ALLOCATOR_free_memory_block_unmanaged(void* block) {
  free(block);
}

void* SPVM_ALLOCATOR_alloc_memory_block_tmp(SPVM_ALLOCATOR* allocator, size_t byte_size) {
  (void)allocator;
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(byte_size);

  assert(allocator);
  allocator->memory_blocks_count_tmp++;

  return block;
}

void SPVM_ALLOCATOR_free_memory_block_tmp(SPVM_ALLOCATOR* allocator, void* block) {
  (void)allocator;

  SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
  
  allocator->memory_blocks_count_tmp--;
}

void* SPVM_ALLOCATOR_alloc_memory_block_permanent(SPVM_ALLOCATOR* allocator, size_t byte_size) {
  (void)allocator;
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(byte_size);
  allocator->memory_blocks_count_permanent++;
  
  SPVM_LIST_push(allocator->permanent_memory_blocks, block);
  
  return block;
}

void SPVM_ALLOCATOR_free_memory_block_permanent(SPVM_ALLOCATOR* allocator, void* block) {
  (void)allocator;

  SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
  
  allocator->memory_blocks_count_permanent--;
}

SPVM_LIST* SPVM_ALLOCATOR_alloc_list_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  (void)allocator;

  int32_t memory_block_type = SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT;
  SPVM_LIST* list = SPVM_LIST_new(allocator, capacity, memory_block_type);
  
  return list;
}

SPVM_HASH* SPVM_ALLOCATOR_alloc_hash_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  (void)allocator;

  int32_t memory_block_type = SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT;
  SPVM_HASH* hash = SPVM_HASH_new(allocator, capacity, memory_block_type);
  
  return hash;
}

void SPVM_ALLOCATOR_free(SPVM_ALLOCATOR* allocator) {
  (void)allocator;
  
  // Free permanent blocks
  int32_t i;
  for (i = 0; i < allocator->permanent_memory_blocks->length; i++) {
    void* permanent_block = SPVM_LIST_fetch(allocator->permanent_memory_blocks, i);
    if (permanent_block != NULL) {
      SPVM_ALLOCATOR_free_memory_block_permanent(allocator, permanent_block);
    }
  }
  SPVM_LIST_free(allocator->permanent_memory_blocks);
  
  assert(allocator->memory_blocks_count_tmp == 0);
  assert(allocator->memory_blocks_count_permanent == 0);

  SPVM_ALLOCATOR_free_memory_block_unmanaged(allocator);
}
