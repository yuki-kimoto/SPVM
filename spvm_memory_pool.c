#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "spvm_memory_pool.h"
#include "spvm_util_allocator.h"
#include "spvm_api.h"

SPVM_MEMORY_POOL* SPVM_MEMORY_POOL_new(int32_t page_byte_size) {
  
  SPVM_MEMORY_POOL* memory_pool = (SPVM_MEMORY_POOL*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_MEMORY_POOL));
  
  if (page_byte_size == 0) {
    memory_pool->page_byte_size = 0xFFFF;
  }
  else {
    memory_pool->page_byte_size = page_byte_size;
  }
  
  char* page = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(memory_pool->page_byte_size);
  memory_pool->pages_length = 1;
  int64_t memory_pool_pages_byte_size = (int64_t)memory_pool->pages_length * (int64_t)sizeof(char*);
  memory_pool->pages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(memory_pool_pages_byte_size);
  memory_pool->pages[0] = page;
  
  memory_pool->current_page = 0;
  memory_pool->current_offset = 0;
  
  return memory_pool;
}

void* SPVM_MEMORY_POOL_alloc(SPVM_MEMORY_POOL* memory_pool, int32_t byte_size) {
  
  assert(byte_size > 0);
  
  if (byte_size > memory_pool->page_byte_size) {
    fprintf(stderr, "Very lerge memory byte size is specified(SPVM_MEMORY_POOL_alloc())\n");
    abort();
  }
  
  // Adjust alignment
  int32_t aligned_byte_size = (byte_size - 1) + ((int32_t)sizeof(SPVM_API_VALUE) - ((byte_size - 1) % (int32_t)sizeof(SPVM_API_VALUE)));
  
  // Move to next page
  if (memory_pool->current_offset + aligned_byte_size > memory_pool->page_byte_size) {
    // Next page is not yet allocated
    memory_pool->current_page++;
    memory_pool->current_offset = 0;
    
    if (memory_pool->current_page == memory_pool->pages_length) {
      int32_t new_memory_pool_pages_length = memory_pool->pages_length * 2;
      
      int64_t new_pages_byte_size = (int64_t)new_memory_pool_pages_length * (int64_t)sizeof(char*);
      char** new_pages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_pages_byte_size);
      memcpy(new_pages, memory_pool->pages, memory_pool->pages_length * sizeof(char*));
      free(memory_pool->pages);
      memory_pool->pages = new_pages;
      
      {
        int32_t i;
        for (i = memory_pool->pages_length; i < new_memory_pool_pages_length; i++) {
          memory_pool->pages[i] = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(memory_pool->page_byte_size);
        }
      }
      
      memory_pool->pages_length = new_memory_pool_pages_length;
    }
  }
  
  // Allocated address
  char* alloc_address = memory_pool->pages[memory_pool->current_page] + memory_pool->current_offset;
  
  memory_pool->current_offset += aligned_byte_size;
  
  return alloc_address;
}

void SPVM_MEMORY_POOL_free(SPVM_MEMORY_POOL* memory_pool) {
  
  {
    int32_t i;
    for (i = 0; i < memory_pool->pages_length; i++) {
      free(memory_pool->pages[i]);
    }
  }
  
  free(memory_pool->pages);
  
  free(memory_pool);
}
