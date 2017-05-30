#ifndef SPVM_ALLOCATOR_RUNTIME_H
#define SPVM_ALLOCATOR_RUNTIME_H
#include <stddef.h>
#include "spvm_base.h"

// Parser information
struct SPVM_allocator_runtime {
  // Memory_pool
  SPVM_MEMORY_POOL* memory_pool;
  
  // Free lists
  SPVM_ARRAY** freelists;
};

SPVM_ALLOCATOR_RUNTIME* SPVM_ALLOCATOR_RUNTIME_new(SPVM* spvm);
void* SPVM_ALLOCATOR_RUNTIME_malloc(SPVM* spvm, SPVM_ALLOCATOR_RUNTIME* allocator, int64_t size);
void SPVM_ALLOCATOR_RUNTIME_free_ref(SPVM* spvm, SPVM_ALLOCATOR_RUNTIME* allocator, SPVM_REF* ref);
int32_t SPVM_ALLOCATOR_RUNTIME_get_freelist_index(SPVM* spvm, SPVM_ALLOCATOR_RUNTIME* allocator, int64_t size);
void SPVM_ALLOCATOR_RUNTIME_free(SPVM* spvm, SPVM_ALLOCATOR_RUNTIME* allocator);

#endif
