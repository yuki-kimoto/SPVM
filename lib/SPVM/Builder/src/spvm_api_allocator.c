// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_allocator.h"
#include "spvm_api_allocator.h"

SPVM_API_ALLOCATOR* SPVM_API_ALLOCATOR_new_api() {
  
  // Env Allocator
  void* env_allocator_init[]  = {
    SPVM_API_ALLOCATOR_new_instance,
    SPVM_API_ALLOCATOR_free_instance,
  };
  SPVM_API_ALLOCATOR* env_allocator = calloc(1, sizeof(env_allocator_init));
  memcpy(env_allocator, env_allocator_init, sizeof(env_allocator_init));
  
  return env_allocator;
}

SPVM_ALLOCATOR* SPVM_API_ALLOCATOR_new_instance() {
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();

  return allocator;
}

void SPVM_API_ALLOCATOR_free_instance(SPVM_ALLOCATOR* allocator) {
  SPVM_ALLOCATOR_free(allocator);
}

void SPVM_API_ALLOCATOR_free_api(SPVM_API_ALLOCATOR* api) {
  free(api);
}
