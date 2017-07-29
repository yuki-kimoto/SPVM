#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "spvm_util_allocator.h"

void* SPVM_UTIL_ALLOCATOR_safe_malloc(int64_t byte_size) {

  assert(byte_size > 0);

  if (byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Size is too big(SPVM_UTIL_ALLOCATOR_safe_malloc)\n");
    abort();
  }
  
  void* block = malloc(byte_size);
  
  if (!block) {
    fprintf(stderr, "Failed to allocate memory. malloc function return NULL(SPVM_UTIL_ALLOCATOR_safe_malloc)\n");
    abort();
  }
  
  return block;
}

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
  
  return block;
}
