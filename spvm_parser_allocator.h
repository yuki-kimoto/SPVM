#ifndef SPVM_PARSER_ALLOCATOR_H
#define SPVM_PARSER_ALLOCATOR_H
#include <stddef.h>
#include "spvm_base.h"

SPVM_PARSER_ALLOCATOR* SPVM_PARSER_ALLOCATOR_new(SPVM_* spvm);

SPVM_ARRAY* SPVM_PARSER_ALLOCATOR_alloc_array(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator, int32_t capacity);
SPVM_HASH* SPVM_PARSER_ALLOCATOR_alloc_hash(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator, int32_t capacity);
char* SPVM_PARSER_ALLOCATOR_alloc_string(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator, int32_t length);
int32_t* SPVM_PARSER_ALLOCATOR_alloc_int(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator);
void* SPVM_PARSER_ALLOCATOR_alloc_memory_pool(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator, int32_t size);

SPVM_VMCODE* SPVM_PARSER_ALLOCATOR_alloc_vmcode(SPVM_* spvm, SPVM_PARSER* parser);

void SPVM_PARSER_ALLOCATOR_free(SPVM_* spvm, SPVM_PARSER_ALLOCATOR* allocator);

// Parser information
struct SPVM_parser_allocator {
  // Memory_pool - This is compile time memory pool. This memory pool save short string and object except array, hash
  SPVM_MEMORY_POOL* memory_pool;
  
  // Compile time arrays
  SPVM_ARRAY* arrays;
  
  // Compile time hashes
  SPVM_ARRAY* hashes;
};

#endif
