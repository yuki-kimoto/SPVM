#ifndef SPVM_MEMORY_POOL_H
#define SPVM_MEMORY_POOL_H

#include "spvm_base.h"

struct SPVM_memory_pool {
  int32_t page_byte_size;
  int32_t pages_length;
  int32_t current_offset;
  int8_t** pages;
  int32_t current_page;
};

SPVM_MEMORY_POOL* SPVM_MEMORY_POOL_new(SPVM_* spvm, int32_t page_byte_size);
void* SPVM_MEMORY_POOL_alloc(SPVM_* spvm, SPVM_MEMORY_POOL* memory_pool, int32_t block_size);
void SPVM_MEMORY_POOL_free(SPVM_* spvm, SPVM_MEMORY_POOL* memory_pool);

#endif
