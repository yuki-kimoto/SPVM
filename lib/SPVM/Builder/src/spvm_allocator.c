#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_allocator.h"

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new() {
  
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_ALLOCATOR));

  assert(allocator->memory_blocks_count_tmp == 0);
  assert(allocator->memory_blocks_count_permanent == 0);

  allocator->permanent_memory_blocks_capacity = 1024;
  allocator->permanent_memory_blocks = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(void*) * allocator->permanent_memory_blocks_capacity);

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
  
  void* parmanent_block = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(byte_size);
  allocator->memory_blocks_count_permanent++;
  
  int32_t length = allocator->permanent_memory_blocks_length;
  int32_t capacity = allocator->permanent_memory_blocks_capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    void** new_permanent_memory_blocks;
    new_permanent_memory_blocks = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(void*) * new_capacity);
    memcpy(new_permanent_memory_blocks, allocator->permanent_memory_blocks, sizeof(void*) * capacity);
    SPVM_ALLOCATOR_free_memory_block_unmanaged(allocator->permanent_memory_blocks);

    allocator->permanent_memory_blocks = new_permanent_memory_blocks;
    allocator->permanent_memory_blocks_capacity = new_capacity;
  }
  
  int32_t permanent_memory_blocks_index = allocator->permanent_memory_blocks_length;
  allocator->permanent_memory_blocks[permanent_memory_blocks_index] = parmanent_block;
  allocator->permanent_memory_blocks_length++;
  
  return parmanent_block;
}

void SPVM_ALLOCATOR_free_memory_block_permanent(SPVM_ALLOCATOR* allocator, void* block) {
  (void)allocator;

  SPVM_ALLOCATOR_free_memory_block_unmanaged(block);
  
  allocator->memory_blocks_count_permanent--;

}

void SPVM_ALLOCATOR_free(SPVM_ALLOCATOR* allocator) {
  (void)allocator;
  
  // Free permanent memory blocks
  int32_t i;
  for (i = 0; i < allocator->permanent_memory_blocks_length; i++) {
    void* permanent_memory_block = allocator->permanent_memory_blocks[i];
    assert(permanent_memory_block);
    if (permanent_memory_block) {
      SPVM_ALLOCATOR_free_memory_block_permanent(allocator, permanent_memory_block);
    }
  }
  SPVM_ALLOCATOR_free_memory_block_unmanaged(allocator->permanent_memory_blocks);
  
  assert(allocator->memory_blocks_count_tmp == 0);
  
  assert(allocator->memory_blocks_count_permanent == 0);

  SPVM_ALLOCATOR_free_memory_block_unmanaged(allocator);
}
