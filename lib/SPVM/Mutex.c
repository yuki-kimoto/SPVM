// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Mutex.c";

int32_t SPVM__Mutex__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* mutex = env->api->mutex->new_instance(env, stack);
  
  void* obj_mutex = env->new_pointer_object_by_name(env, stack, "Mutex", mutex, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_mutex;
  
  return 0;
}

int32_t SPVM__Mutex__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_mutex = stack[0].oval;
  
  void* mutex = env->get_pointer(env, stack, obj_mutex);
  
  env->api->mutex->free_instance(env, stack, obj_mutex);
  
  return 0;
}

int32_t SPVM__Mutex__lock(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_mutex = stack[0].oval;
  
  void* mutex = env->get_pointer(env, stack, obj_mutex);
  
  env->api->mutex->lock(env, stack, mutex);
  
  return 0;
}

int32_t SPVM__Mutex__unlock(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_mutex = stack[0].oval;
  
  void* mutex = env->get_pointer(env, stack, obj_mutex);
  
  env->api->mutex->unlock(env, stack, mutex);
  
  return 0;
}

int32_t SPVM__Mutex__reader_lock(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_mutex = stack[0].oval;
  
  void* mutex = env->get_pointer(env, stack, obj_mutex);
  
  env->api->mutex->reader_lock(env, stack, mutex);
  
  return 0;
}

int32_t SPVM__Mutex__reader_unlock(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_mutex = stack[0].oval;
  
  void* mutex = env->get_pointer(env, stack, obj_mutex);
  
  env->api->mutex->reader_unlock(env, stack, mutex);
  
  return 0;
}

