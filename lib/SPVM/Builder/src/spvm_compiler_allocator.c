#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_compiler.h"
#include "spvm_constant_pool.h"

SPVM_COMPILER_ALLOCATOR* SPVM_COMPILER_ALLOCATOR_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = malloc(sizeof(SPVM_COMPILER_ALLOCATOR));
  
  // Objects
  allocator->blocks = SPVM_LIST_new(0);
  
  // Arrays
  allocator->lists = SPVM_LIST_new(8);
  
  // Hashes
  allocator->hashes = SPVM_LIST_new(8);

  // Constant pools
  allocator->constant_pools = SPVM_LIST_new(8);
  
  return allocator;
}

void* SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(SPVM_COMPILER* compiler, int32_t byte_size) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  void* block = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(byte_size);
  
  SPVM_LIST_push(allocator->blocks, block);
  
  return block;
}

SPVM_LIST* SPVM_COMPILER_ALLOCATOR_alloc_list(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_LIST* list = SPVM_LIST_new(capacity);
  
  SPVM_LIST_push(allocator->lists, list);
  
  return list;
}

SPVM_HASH* SPVM_COMPILER_ALLOCATOR_alloc_hash(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;

  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_HASH* hash = SPVM_HASH_new(capacity);
  
  SPVM_LIST_push(allocator->hashes, hash);
  
  return hash;
}

SPVM_CONSTANT_POOL* SPVM_COMPILER_ALLOCATOR_alloc_constant_pool(SPVM_COMPILER* compiler, int32_t capacity) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  SPVM_CONSTANT_POOL* constant_pool = SPVM_CONSTANT_POOL_new(capacity);
  
  SPVM_LIST_push(allocator->constant_pools, constant_pool);
  
  return constant_pool;
}

void SPVM_COMPILER_ALLOCATOR_free(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_COMPILER_ALLOCATOR* allocator = compiler->allocator;
  
  // Free blocks
  int32_t i;
  for (i = 0; i < allocator->blocks->length; i++) {
    void* block = SPVM_LIST_fetch(allocator->blocks, i);
    if (block != NULL) {
      free(block);
    }
  }
  
  // Free lists
  {
    int32_t i;
    for (i = 0; i < allocator->lists->length; i++) {
      SPVM_LIST* list = SPVM_LIST_fetch(allocator->lists, i);
      if (list != NULL) {
        SPVM_LIST_free(list);
      }
    }
  }
  SPVM_LIST_free(allocator->lists);
  
  // Free hashes
  {
    int32_t i;
    for (i = 0; i < allocator->hashes->length; i++) {
      SPVM_HASH* hash = SPVM_LIST_fetch(allocator->hashes, i);
      if (hash != NULL) {
        SPVM_HASH_free(hash);
      }
    }
  }
  SPVM_LIST_free(allocator->hashes);

  // Free constant pool
  {
    int32_t i;
    for (i = 0; i < allocator->constant_pools->length; i++) {
      SPVM_CONSTANT_POOL* constant_pool = SPVM_LIST_fetch(allocator->constant_pools, i);
      if (constant_pool != NULL) {
        SPVM_CONSTANT_POOL_free(constant_pool);
      }
    }
  }
  SPVM_LIST_free(allocator->constant_pools);
  
  free(allocator);
}
