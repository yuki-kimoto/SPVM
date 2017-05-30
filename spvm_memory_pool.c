#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "spvm.h"
#include "spvm_memory_pool.h"
#include "spvm_allocator_util.h"
#include "spvm_value.h"

SPVM_MEMORY_POOL* SPVM_MEMORY_POOL_new(SPVM* spvm, int32_t page_byte_size) {
  (void)spvm;
  
  SPVM_MEMORY_POOL* memory_pool = (SPVM_MEMORY_POOL*) SPVM_ALLOCATOR_UTIL_safe_malloc_i32(1, sizeof(SPVM_MEMORY_POOL));
  
  if (page_byte_size == 0) {
    memory_pool->page_byte_size = 0xFFFF;
  }
  else {
    memory_pool->page_byte_size = page_byte_size;
  }
  
  int8_t* page = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(memory_pool->page_byte_size, sizeof(int8_t));
  memory_pool->pages_length = 1;
  memory_pool->pages = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(memory_pool->pages_length, sizeof(int8_t*));
  memory_pool->pages[0] = page;
  
  memory_pool->current_page = 0;
  memory_pool->current_offset = 0;
  
  return memory_pool;
}

void* SPVM_MEMORY_POOL_alloc(SPVM* spvm, SPVM_MEMORY_POOL* memory_pool, int32_t byte_size) {
  (void)spvm;
  
  assert(byte_size > 0);
  assert(byte_size <= memory_pool->page_byte_size);
  
  // Adjust alignment
  int32_t aligned_byte_size = (byte_size - 1) + ((int32_t)sizeof(SPVM_VALUE) - ((byte_size - 1) % (int32_t)sizeof(SPVM_VALUE)));
  
  // Move to next page
  if (memory_pool->current_offset + aligned_byte_size > memory_pool->page_byte_size) {
    // Next page is not yet allocated
    memory_pool->current_page++;
    memory_pool->current_offset = 0;
    
    if (memory_pool->current_page == memory_pool->pages_length) {
      int32_t new_memory_pool_pages_length = memory_pool->pages_length * 2;
      
      memory_pool->pages = SPVM_ALLOCATOR_UTIL_safe_realloc_i32(memory_pool->pages, new_memory_pool_pages_length, sizeof(uint8_t*));
      for (int32_t i = memory_pool->pages_length; i < new_memory_pool_pages_length; i++) {
        memory_pool->pages[i] = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(memory_pool->page_byte_size, sizeof(uint8_t));
      }
      
      memory_pool->pages_length = new_memory_pool_pages_length;
    }
  }
  
  // Allocated address
  int8_t* alloc_address = memory_pool->pages[memory_pool->current_page] + memory_pool->current_offset;
  
  memory_pool->current_offset += aligned_byte_size;
  
  return alloc_address;
}

void SPVM_MEMORY_POOL_free(SPVM* spvm, SPVM_MEMORY_POOL* memory_pool) {
  (void)spvm;
  
  for (int32_t i = 0; i < memory_pool->pages_length; i++) {
    free(memory_pool->pages[i]);
  }
  
  free(memory_pool->pages);
  
  free(memory_pool);
}
