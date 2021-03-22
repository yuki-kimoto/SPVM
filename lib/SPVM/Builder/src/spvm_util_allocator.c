#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "spvm_util_allocator.h"

void* SPVM_UTIL_ALLOCATOR_safe_malloc_zero(size_t byte_size) {
  
  if (byte_size < 1) {
    fprintf(stderr, "Failed to allocate memory. Size must be more than 0(SPVM_UTIL_ALLOCATOR_safe_malloc_zero())\n");
    abort();
  }
  
  if ((size_t)byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Size is too big(SPVM_UTIL_ALLOCATOR_safe_malloc_zero())\n");
    abort();
  }
  
  void* block = calloc(1, (size_t)byte_size);
  
  if (block == NULL) {
    fprintf(stderr, "Failed to allocate memory. malloc function return NULL(SPVM_UTIL_ALLOCATOR_safe_malloc_zero())\n");
    abort();
  }
  
  return block;
}
