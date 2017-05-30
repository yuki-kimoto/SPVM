#ifndef SPVM_ALLOCATOR_PARSER_H
#define SPVM_ALLOCATOR_PARSER_H
#include <stddef.h>
#include "spvm_base.h"

SPVM_ALLOCATOR_PARSER* SPVM_ALLOCATOR_PARSER_new(SPVM* spvm);

SPVM_ARRAY* SPVM_ALLOCATOR_PARSER_alloc_array(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator, int32_t capacity);
SPVM_HASH* SPVM_ALLOCATOR_PARSER_alloc_hash(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator, int32_t capacity);
char* SPVM_ALLOCATOR_PARSER_alloc_string(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator, int32_t length);
int32_t* SPVM_ALLOCATOR_PARSER_alloc_int(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator);
void* SPVM_ALLOCATOR_PARSER_alloc_memory_pool(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator, int32_t size);

SPVM_VMCODE* SPVM_ALLOCATOR_PARSER_alloc_vmcode(SPVM* spvm, SPVM_PARSER* parser);

void SPVM_ALLOCATOR_PARSER_free(SPVM* spvm, SPVM_ALLOCATOR_PARSER* allocator);

// Parser information
struct SPVM_allocator_parser {
  // Memory_pool - This is compile time memory pool. This memory pool save short string and object except array, hash
  SPVM_MEMORY_POOL* memory_pool;
  
  // Compile time arrays
  SPVM_ARRAY* arrays;
  
  // Compile time hashes
  SPVM_ARRAY* hashes;
};

#endif
