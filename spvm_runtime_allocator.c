#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include "spvm_runtime_allocator.h"
#include "spvm_runtime_api.h"
#include "spvm_util_allocator.h"
#include "spvm_memory_pool.h"
#include "spvm_dynamic_array.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool.h"
#include "spvm_api.h"

SPVM_RUNTIME_ALLOCATOR* SPVM_RUNTIME_ALLOCATOR_new(SPVM_RUNTIME* runtime) {
  (void)runtime;
  
  SPVM_RUNTIME_ALLOCATOR* allocator = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME_ALLOCATOR));

  // use memory pool max reference byte size
  allocator->object_max_byte_size_use_memory_pool = 0xFFFF;
  
  // Memory pool
  allocator->memory_pool = SPVM_MEMORY_POOL_new(allocator->object_max_byte_size_use_memory_pool);
  
  // Free lists
  int64_t allocator_freelists_byte_size = (int64_t)16 * (int64_t)sizeof(SPVM_DYNAMIC_ARRAY);
  allocator->freelists = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(allocator_freelists_byte_size);
  
  // Initialize free list
  {
    int32_t i;
    for (i = 0; i < 16; i++) {
      allocator->freelists[i] = SPVM_DYNAMIC_ARRAY_new(0);
    }
  }
  
  return allocator;
}

int32_t SPVM_RUNTIME_ALLOCATOR_get_freelist_index(SPVM_API* api, SPVM_RUNTIME_ALLOCATOR* allocator, int64_t byte_size) {
  (void)api;
  (void)allocator;
  
  assert(byte_size > 1);
  
  // byte_size = 128;
  
  // To 2 ^ n
  // This algorizm is from http://ideone.com/EStSRd
  int64_t N = byte_size;
  int64_t _N1 = N-1;
  int64_t _N2 = _N1 | (_N1 >>  1);
  int64_t _N3 = _N2 | (_N2 >>  2);
  int64_t _N4 = _N3 | (_N3 >>  4);
  int64_t _N5 = _N4 | (_N4 >>  8);
  int64_t _N6 = _N5 | (_N5 >> 16);
  int64_t _N7 = _N6 | (_N6 >> 32);
  int64_t Value = _N7 + 1;
  
  // Category
  int64_t div_byte_size = Value;
  int32_t index = -1;
  while (1) {
    div_byte_size = div_byte_size / 2;
    if (div_byte_size == 0) {
      break;
    }
    else {
      index++;
    }
  }
  assert(index >= 0);
  
  return index;
}

void* SPVM_RUNTIME_ALLOCATOR_malloc(SPVM_API* api, SPVM_RUNTIME_ALLOCATOR* allocator, int32_t byte_size) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  assert(byte_size > 0);
  int32_t index = SPVM_RUNTIME_ALLOCATOR_get_freelist_index(api, allocator, byte_size);
  int32_t alloc_byte_size = pow(2, index + 1);
  
  void* block;
  if (alloc_byte_size > allocator->object_max_byte_size_use_memory_pool) {
    block = SPVM_UTIL_ALLOCATOR_safe_malloc(alloc_byte_size);
  }
  else {
    void* free_address = SPVM_DYNAMIC_ARRAY_pop(allocator->freelists[index]);
    if (free_address) {
      block = free_address;
    }
    else {
      block = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, alloc_byte_size);
    }
  }
  
  if (block != NULL) {
    runtime->object_count++;
  }

#ifdef DEBUG
  fprintf(stderr, "MALLOC OBJECT COUNT %d\n", runtime->object_count);
#endif
  
  // Address first bit must be 0 for weaken reference
  assert(((intptr_t)block & 1) == 0);
  
  return block;
}

void SPVM_RUNTIME_ALLOCATOR_free_object(SPVM_API* api, SPVM_RUNTIME_ALLOCATOR* allocator, SPVM_OBJECT* object) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->runtime;
  
  if (object == NULL) {
    return;
  }
  else {
    // Byte size
    int32_t byte_size = SPVM_RUNTIME_API_calcurate_object_byte_size(api, object);
    
    assert(byte_size > 0);
    
    runtime->object_count--;
    assert(runtime->object_count >= 0);

#ifdef DEBUG
    fprintf(stderr, "FREE OBJECT COUNT %d\n", runtime->object_count);
#endif
    
    if (byte_size > allocator->object_max_byte_size_use_memory_pool) {
      free(object);
    }
    else {
      // Freelist index
      int32_t freelist_index = SPVM_RUNTIME_ALLOCATOR_get_freelist_index(api, allocator, byte_size);
      
      // Push free address
      SPVM_DYNAMIC_ARRAY_push(allocator->freelists[freelist_index], object);
    }
  }
}

void SPVM_RUNTIME_ALLOCATOR_free(SPVM_RUNTIME* runtime, SPVM_RUNTIME_ALLOCATOR* allocator) {
  (void)runtime;
  
  // Free memory pool */
  SPVM_MEMORY_POOL_free(allocator->memory_pool);
  
  free(allocator->freelists);
  
  free(allocator);
}
