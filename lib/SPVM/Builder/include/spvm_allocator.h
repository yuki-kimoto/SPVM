// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_ALLOCATOR_H
#define SPVM_ALLOCATOR_H

#include "spvm_typedecl.h"

enum {
  SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP = 0,
  SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT = 1,
};

struct spvm_allocator {
  void** permanent_memory_blocks;
  
  int32_t permanent_memory_blocks_length;
  
  int32_t permanent_memory_blocks_capacity;
  
  int32_t memory_blocks_count_tmp;
  
  int32_t memory_blocks_count_permanent;
};

SPVM_ALLOCATOR* SPVM_ALLOCATOR_new();

int32_t SPVM_ALLOCATOR_get_memory_blocks_count(SPVM_ALLOCATOR* allocator);

void* SPVM_ALLOCATOR_alloc_memory_block_unmanaged(size_t size);

void SPVM_ALLOCATOR_free_memory_block_unmanaged(void* block);

void* SPVM_ALLOCATOR_alloc_memory_block_tmp(SPVM_ALLOCATOR* allocator, size_t size);

void SPVM_ALLOCATOR_free_memory_block_tmp(SPVM_ALLOCATOR* allocator, void* block);

void* SPVM_ALLOCATOR_alloc_memory_block_permanent(SPVM_ALLOCATOR* allocator, size_t size);

void SPVM_ALLOCATOR_free(SPVM_ALLOCATOR* allocator);

#endif
