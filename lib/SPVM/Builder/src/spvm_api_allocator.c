#include "spvm_allocator.h"
#include "spvm_env_allocator.h"
#include "spvm_api_allocator.h"

SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new_env_raw() {
  
  return NULL;
}

SPVM_ENV_ALLOCATOR* SPVM_API_ALLOCATOR_new() {
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new(allocator);

  SPVM_ENV_ALLOCATOR* env_allocator = SPVM_API_ALLOCATOR_new_env_raw();
  env_allocator->allocator = allocator;
  
  return env_allocator;
}

void SPVM_API_ALLOCATOR_free(SPVM_ENV_ALLOCATOR* env_allocator) {
  SPVM_ALLOCATOR_free(allocator);
}
