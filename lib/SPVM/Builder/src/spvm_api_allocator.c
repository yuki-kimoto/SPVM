#include "spvm_native.h"

#include "spvm_allocator.h"
#include "spvm_api_allocator.h"

SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new_env() {
  
  // Env Allocator
  void* env_allocator_init[]  = {
    SPVM_API_ALLOCATOR_new_allocator,
    SPVM_API_ALLOCATOR_free_allocator,
  };
  SPVM_ENV_ALLOCATOR* env_allocator = calloc(1, sizeof(env_allocator_init));
  memcpy(env_allocator, env_allocator_init, sizeof(env_allocator_init));
  
  return env_allocator;
}

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_allocator() {
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();

  return allocator;
}

void SPVM_API_ALLOCATOR_free_allocator(SPVM_ALLOCATOR* allocator) {
  SPVM_ALLOCATOR_free(allocator);
}
