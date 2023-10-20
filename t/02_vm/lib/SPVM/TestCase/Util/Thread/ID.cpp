#include "spvm_native.h"

#include <assert.h>

#include <iostream>
#include <thread>

extern "C" {

static const char* FILE_NAME = "TestCase/Util/Thread/ID.cpp";

int32_t SPVM__TestCase__Util__Thread__ID__eq(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id == *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__ne(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id != *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__gt(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id > *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__ge(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id >= *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__lt(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id < *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__le(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  void* obj_thread_id = stack[1].oval;
  
  std::thread::id* self_thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_thread_id);
  
  int32_t ok = *self_thread_id <= *thread_id;
  
  stack[0].ival = ok;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__ID__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_self = stack[0].oval;
  
  std::thread::id* thread_id = (std::thread::id*)env->get_pointer(env, stack, obj_self);
  
  env->free_memory_block(env, stack, thread_id);
  
  return 0;
}

}
