#ifndef SPVM_ALLOCATOR_H
#define SPVM_ALLOCATOR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

enum {
  SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP = 0,
  SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT = 1,
};

// Parser information
struct spvm_allocator {
  // Blocks
  SPVM_LIST* blocks;

  // This is temporary memory blocks count allocated by the SPVM compiler.
  int32_t memory_blocks_count_tmp;

  // This is eternal memory blocks count allocated by the SPVM compiler.
  int32_t memory_blocks_count_permanent;
};

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new();

int32_t SPVM_ALLOCATOR_get_memory_blocks_count(SPVM_ALLOCATOR* allocator);

void* SPVM_ALLOCATOR_alloc_memory_block_unmanaged(size_t byte_size);
void SPVM_ALLOCATOR_free_memory_block_unmanaged(void* block);

void* SPVM_ALLOCATOR_alloc_memory_block_tmp(SPVM_ALLOCATOR* allocator, size_t byte_size);
void SPVM_ALLOCATOR_free_memory_block_tmp(SPVM_ALLOCATOR* allocator, void* block);

void* SPVM_ALLOCATOR_alloc_memory_block_permanent(SPVM_ALLOCATOR* allocator, size_t byte_size);
SPVM_LIST* SPVM_ALLOCATOR_alloc_list_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity);
SPVM_HASH* SPVM_ALLOCATOR_alloc_hash_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity);

void SPVM_ALLOCATOR_free(SPVM_ALLOCATOR* allocator);

#endif
