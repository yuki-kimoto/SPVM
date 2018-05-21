#ifndef SPVM_COMPILER_ALLOCATOR_H
#define SPVM_COMPILER_ALLOCATOR_H
#include <stddef.h>
#include "spvm_base.h"

SPVM_COMPILER_ALLOCATOR* SPVM_COMPILER_ALLOCATOR_new(SPVM_COMPILER* compiler);

SPVM_LIST* SPVM_COMPILER_ALLOCATOR_alloc_list(SPVM_COMPILER* compiler, int32_t capacity);
SPVM_HASH* SPVM_COMPILER_ALLOCATOR_alloc_hash(SPVM_COMPILER* compiler, int32_t capacity);
char* SPVM_COMPILER_ALLOCATOR_alloc_string(SPVM_COMPILER* compiler, int32_t length);
void* SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(SPVM_COMPILER* compiler, int32_t size);

SPVM_VMCODE* SPVM_COMPILER_ALLOCATOR_alloc_vmcode(SPVM_COMPILER* compiler);

void SPVM_COMPILER_ALLOCATOR_free(SPVM_COMPILER* compiler);

// Parser information
struct SPVM_compiler_allocator {
  // Memory_pool - This is compile time memory pool. This memory pool save short string and object except array, hash
  SPVM_MEMORY_POOL* memory_pool;
  
  // Compile time arrays
  SPVM_LIST* arrays;
  
  // Compile time hashes
  SPVM_LIST* hashes;
};

#endif
