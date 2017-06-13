#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "spvm_array.h"
#include "spvm_hash.h"
#include "spvm_memory_pool.h"
#include "spvm_util_allocator.h"
#include "spvm_parser_allocator.h"
#include "spvm_parser.h"

SPVM_PARSER_ALLOCATOR* SPVM_PARSER_ALLOCATOR_new(SPVM_PARSER* parser) {
  (void)parser;
  
  SPVM_PARSER_ALLOCATOR* allocator = malloc(sizeof(SPVM_PARSER_ALLOCATOR));
  
  // Memory pool - memory pool save short strings and object, except array and hash
  // These datas are created at compile time
  allocator->memory_pool = SPVM_MEMORY_POOL_new(0);
  
  // Arrays - these arrays are created at compile time
  allocator->arrays = SPVM_ARRAY_new(0);
  
  // Hashed - these hashes are created at compile time
  allocator->hashes = SPVM_ARRAY_new(0);
  
  return allocator;
}

void* SPVM_PARSER_ALLOCATOR_alloc_memory_pool(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator, int32_t size) {
  (void)parser;
  return SPVM_MEMORY_POOL_alloc(allocator->memory_pool, size);
}

SPVM_ARRAY* SPVM_PARSER_ALLOCATOR_alloc_array(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator, int32_t capacity) {
  (void)parser;
  
  SPVM_ARRAY* array = SPVM_ARRAY_new(capacity);
  
  SPVM_ARRAY_push(allocator->arrays, array);
  
  return array;
}

SPVM_HASH* SPVM_PARSER_ALLOCATOR_alloc_hash(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator, int32_t capacity) {
  (void)parser;
  
  SPVM_HASH* hash = SPVM_HASH_new(capacity);
  
  SPVM_ARRAY_push(allocator->hashes, hash);
  
  return hash;
}

int32_t* SPVM_PARSER_ALLOCATOR_alloc_int(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator) {
  (void)parser;
  
  int32_t* value = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, sizeof(int32_t));
  
  return value;
}

char* SPVM_PARSER_ALLOCATOR_alloc_string(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator, int32_t length) {
  (void)parser;
  
  assert(length > 0);
  assert(length <= 0xFFFF);
  
  char* str = SPVM_MEMORY_POOL_alloc(allocator->memory_pool, length + 1);
  
  return str;
}

void SPVM_PARSER_ALLOCATOR_free(SPVM_PARSER* parser, SPVM_PARSER_ALLOCATOR* allocator) {
  (void)parser;
  
  // Free memory pool */
  SPVM_MEMORY_POOL_free(allocator->memory_pool);
  
  // Free arrays
  for (int32_t i = 0, len = allocator->arrays->length; i < len; i++) {
    SPVM_ARRAY* array = SPVM_ARRAY_fetch(allocator->arrays, i);
    SPVM_ARRAY_free(array);
  }
  SPVM_ARRAY_free(allocator->arrays);
  
  // Free hashes
  for (int32_t i = 0, len = allocator->hashes->length; i < len; i++) {
    SPVM_HASH* hash = SPVM_ARRAY_fetch(allocator->hashes, i);
    SPVM_HASH_free(hash);
  }
  SPVM_ARRAY_free(allocator->hashes);
  
  free(allocator);
}
