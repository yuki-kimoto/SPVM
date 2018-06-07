#ifndef SPVM_COMPILER_ALLOCATOR_H
#define SPVM_COMPILER_ALLOCATOR_H
#include <stddef.h>
#include "spvm_base.h"

SPVM_COMPILER_ALLOCATOR* SPVM_COMPILER_ALLOCATOR_new(SPVM_COMPILER* compiler);

SPVM_LIST* SPVM_COMPILER_ALLOCATOR_alloc_list(SPVM_COMPILER* compiler, int32_t capacity);
SPVM_HASH* SPVM_COMPILER_ALLOCATOR_alloc_hash(SPVM_COMPILER* compiler, int32_t capacity);
void* SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(SPVM_COMPILER* compiler, int32_t size);

SPVM_VMCODE* SPVM_COMPILER_ALLOCATOR_alloc_vmcode(SPVM_COMPILER* compiler);

void SPVM_COMPILER_ALLOCATOR_free(SPVM_COMPILER* compiler);

// Parser information
struct SPVM_compiler_allocator {
  // Compile time lists
  SPVM_LIST* blocks;

  // Compile time lists
  SPVM_LIST* lists;
  
  // Compile time hashes
  SPVM_LIST* hashes;
  
  void** memory_blocks;
};

#endif
