#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_memory_pool.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"

SPVM_COMPILER_ALLOCATOR* SPVM_COMPILER_ALLOCATOR_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = malloc(sizeof(SPVM_COMPILER_ALLOCATOR));
  
  // Memory pool - memory pool save short strings and object, except array and hash
  // These base_objects are created at compile time
  allocator->memory_pool = SPVM_MEMORY_POOL_new(0);
  
  // Arrays - these arrays are created at compile time
  allocator->arrays = SPVM_LIST_new(0);
  
  // Hashed - these hashes are created at compile time
  allocator->hashes = SPVM_LIST_new(0);
  
  return allocator;
}

void* SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator, int32_t size) {
  (void)compiler;
  
  void* block = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, size);
  memset(block, 0, size);
  
  return block;
}

SPVM_LIST* SPVM_COMPILER_ALLOCATOR_alloc_array(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator, int32_t capacity) {
  (void)compiler;
  
  SPVM_LIST* array = SPVM_LIST_new(capacity);
  
  SPVM_LIST_push(allocator->arrays, array);
  
  return array;
}

SPVM_HASH* SPVM_COMPILER_ALLOCATOR_alloc_hash(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator, int32_t capacity) {
  (void)compiler;
  
  SPVM_HASH* hash = SPVM_HASH_new(capacity);
  
  SPVM_LIST_push(allocator->hashes, hash);
  
  return hash;
}

int32_t* SPVM_COMPILER_ALLOCATOR_alloc_int(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator) {
  (void)compiler;
  
  int32_t* value = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, sizeof(int32_t));
  
  return value;
}

char* SPVM_COMPILER_ALLOCATOR_alloc_string(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator, int32_t length) {
  (void)compiler;
  
  assert(length >= 0);
  assert(length <= 0xFFFF);
  
  char* str = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, length + 1);
  
  return str;
}

void SPVM_COMPILER_ALLOCATOR_free(SPVM_COMPILER* compiler, SPVM_COMPILER_ALLOCATOR* allocator) {
  (void)compiler;
  
  // Free memory pool */
  SPVM_MEMORY_POOL_free(allocator->memory_pool);
  
  // Free arrays
  {
    int32_t i;
    for (i = 0; i < allocator->arrays->length; i++) {
      SPVM_LIST* array = SPVM_LIST_fetch(allocator->arrays, i);
      SPVM_LIST_free(array);
    }
  }
  SPVM_LIST_free(allocator->arrays);
  
  // Free hashes
  {
    int32_t i;
    for (i = 0; i < allocator->hashes->length; i++) {
      SPVM_HASH* hash = SPVM_LIST_fetch(allocator->hashes, i);
      SPVM_HASH_free(hash);
    }
  }
  SPVM_LIST_free(allocator->hashes);
  
  free(allocator);
}
