#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "spvm_util_allocator.h"

void* SPVM_UTIL_ALLOCATOR_safe_malloc_i32(int32_t count, int32_t size) {
  
  assert(count >= 0);
  assert(size >= 0);
  assert(count <= INT32_MAX / size);
  
  int32_t block_size = count * size;
  void* block = malloc(block_size);
  
  if (!block) {
    fprintf(stderr, "Failed to allocate memory. Sperl will abort.\n");
    abort();
  }
  
  return block;
}

void* SPVM_UTIL_ALLOCATOR_safe_malloc_i32_zero(int32_t count, int32_t size) {

  int32_t block_size = count * size;
  void* block = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(count, size);
  memset(block, 0, block_size);
}

void* SPVM_UTIL_ALLOCATOR_safe_realloc_i32(void* ptr, int32_t count, int32_t size) {

  assert(count >= 0);
  assert(size >= 0);
  assert(count <= INT32_MAX / size);

  int32_t block_size = count * size;
  void* block = realloc(ptr, block_size);
  
  if (!block) {
    fprintf(stderr, "Failed to reallocate memory. Sperl will abort.\n");
    abort();
  }

  return block;
}
