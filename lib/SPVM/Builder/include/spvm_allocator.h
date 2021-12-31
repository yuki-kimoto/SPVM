#ifndef SPVM_ALLOCATOR_H
#define SPVM_ALLOCATOR_H

#include "spvm_typedecl.h"

enum {
  SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY = 0,
  SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL = 1,
  SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME = 2,
};

// Parser information
struct spvm_allocator {
  // Blocks
  SPVM_LIST* blocks;

  // Lists
  SPVM_LIST* lists;
  
  // Hashes
  SPVM_LIST* hashes;
  
  // This is all memory blocks allocated by the SPVM compiler and runtime.
  int32_t memory_blocks_count;

  // This is temporary memory blocks allocated by the SPVM compiler and runtime.
  int32_t tmp_memory_blocks_count;
};

void* SPVM_ALLOCATOR_new_block_unmanaged(size_t byte_size);
void SPVM_ALLOCATOR_free_block_unmanaged(void* block);

void* SPVM_ALLOCATOR_new_block_compile_tmp(SPVM_COMPILER* compiler, int32_t byte_size);
void SPVM_ALLOCATOR_free_block_compile_tmp(SPVM_COMPILER* compiler, void* block);

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new();
void SPVM_ALLOCATOR_init(SPVM_COMPILER* compiler);

SPVM_LIST* SPVM_ALLOCATOR_new_list_compile_eternal(SPVM_COMPILER* compiler, int32_t capacity);
SPVM_HASH* SPVM_ALLOCATOR_new_hash_compile_eternal(SPVM_COMPILER* compiler, int32_t capacity);
void* SPVM_ALLOCATOR_new_block_compile_eternal(SPVM_COMPILER* compiler, int32_t size);

SPVM_VMCODE* SPVM_ALLOCATOR_alloc_vmcode(SPVM_COMPILER* compiler);

void SPVM_ALLOCATOR_free(SPVM_COMPILER* compiler);

#endif
