#include "spvm_native.h"

#include "spvm_allocator.h"
#include "spvm_api_allocator.h"

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_allocator() {
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new(allocator);

  return allocator;
}

void SPVM_API_ALLOCATOR_free_allocator(SPVM_ALLOCATOR* allocator) {
  SPVM_ALLOCATOR_free(allocator);
}
