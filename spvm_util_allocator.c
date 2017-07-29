#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "spvm_util_allocator.h"

void* SPVM_UTIL_ALLOCATOR_safe_malloc(int64_t byte_size) {
  
  if (byte_size < 1) {
    fprintf(stderr, "Failed to allocate memory. Size must be more than 0(SPVM_UTIL_ALLOCATOR_safe_malloc)\n");
    abort();
  }
  
  if ((size_t)byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Size is too big(SPVM_UTIL_ALLOCATOR_safe_malloc)\n");
    abort();
  }
  
  void* block = malloc((size_t)byte_size);
  
  if (!block) {
    fprintf(stderr, "Failed to allocate memory. malloc function return NULL(SPVM_UTIL_ALLOCATOR_safe_malloc)\n");
    abort();
  }
  
  return block;
}

void* SPVM_UTIL_ALLOCATOR_safe_malloc_zero(int64_t byte_size) {

  void* block = SPVM_UTIL_ALLOCATOR_safe_malloc(byte_size);
  memset(block, 0, byte_size);
  
  return block;
}
