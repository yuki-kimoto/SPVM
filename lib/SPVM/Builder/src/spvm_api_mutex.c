// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_mutex.h"
#include "spvm_api.h"
#include "spvm_api_mutex.h"

SPVM_API_MUTEX* SPVM_API_MUTEX_new_api() {
  
  // Env Allocator
  void* env_mutex_init[]  = {
    SPVM_API_MUTEX_new_instance,
    SPVM_API_MUTEX_free_instance,
    SPVM_API_MUTEX_lock,
    SPVM_API_MUTEX_unlock,
    SPVM_API_MUTEX_reader_lock,
    SPVM_API_MUTEX_reader_unlock,
  };
  SPVM_API_MUTEX* env_mutex = calloc(1, sizeof(env_mutex_init));
  memcpy(env_mutex, env_mutex_init, sizeof(env_mutex_init));
  
  return env_mutex;
}

void SPVM_API_MUTEX_free_api(SPVM_API_MUTEX* api) {
  free(api);
}

SPVM_MUTEX* SPVM_API_MUTEX_new_instance(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t mutex_size = SPVM_MUTEX_size();
  
  void* mutex = SPVM_API_new_memory_block(env, stack, mutex_size);
  
  SPVM_MUTEX_init(mutex);
  
  return mutex;
}

void SPVM_API_MUTEX_free_instance(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_MUTEX* mutex) {
  
  int32_t mutex__size = SPVM_MUTEX_size();
  
  SPVM_MUTEX_destroy(mutex);
  
  SPVM_API_free_memory_block(env, stack, mutex);
}

void SPVM_API_MUTEX_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex) {
  
  SPVM_MUTEX_lock(mutex);
}

void SPVM_API_MUTEX_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex) {
  
  SPVM_MUTEX_unlock(mutex);
}

void SPVM_API_MUTEX_reader_lock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex) {
  
  SPVM_MUTEX_reader_lock(mutex);
}

void SPVM_API_MUTEX_reader_unlock(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex) {
  
  SPVM_MUTEX_reader_unlock(mutex);
}

