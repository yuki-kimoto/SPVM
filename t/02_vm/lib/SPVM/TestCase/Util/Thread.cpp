#include "spvm_native.h"

#include <assert.h>

#include <iostream>
#include <thread>

extern "C" {

static const char* FILE_NAME = "TestCase/Util/Thread.cpp";

static void thread_handler (SPVM_ENV* env, void* obj_self, void* obj_task) {
  
  int32_t error_id = 0;
  
  SPVM_VALUE* stack = env->new_stack(env);
  
  stack[0].oval = obj_task;
  env->call_instance_method_by_name(env, stack, "", 1, &error_id, __func__, FILE_NAME, __LINE__);
  
  if (error_id) {
    
    void* obj_exception = env->get_exception(env, stack);
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    env->set_field_object_by_name(env, stack, obj_self, "exception", obj_exception, &error_id, __func__, FILE_NAME, __LINE__);
    assert(error_id == 0);
    
    env->set_field_int_by_name(env, stack, obj_self, "error_id", error_id, &error_id, __func__, FILE_NAME, __LINE__);
    assert(error_id == 0);
  }
  
  env->free_stack(env, stack);
  
  return;
}

int32_t SPVM__TestCase__Util__Thread__create(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_task = env->get_field_object_by_name(env, stack, obj_self, "task", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  std::thread* nt_thread = (std::thread*)env->new_memory_block(env, stack, sizeof(std::thread));
  
  *nt_thread = std::thread(thread_handler, env, obj_self, obj_task);
  
  env->set_pointer(env, stack, obj_self, nt_thread);
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__joinable(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  int32_t joinable = nt_thread->joinable();
  
  stack[0].ival = joinable;
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__join(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  try {
    nt_thread->join();
  }
  catch (std::exception& cpp_exception){
    env->die(env, stack, "[System Error]join failed:%s", __func__, FILE_NAME, __LINE__, cpp_exception.what());
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}


int32_t SPVM__TestCase__Util__Thread__detach(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  try {
    nt_thread->detach();
  }
  catch (std::exception& cpp_exception){
    env->die(env, stack, "[System Error]detach failed:%s", __func__, FILE_NAME, __LINE__, cpp_exception.what());
    return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS;
  }
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  if (nt_thread->joinable()) {
    nt_thread->detach();
  }
  
  env->free_memory_block(env, stack, nt_thread);
  
  return 0;
}

int32_t SPVM__TestCase__Util__Thread__get_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_thread = stack[0].oval;
  
  std::thread* nt_thread = (std::thread*)env->get_pointer(env, stack, obj_thread);
  
  std::thread::id* thread_id = (std::thread::id*)env->new_memory_block(env, stack, sizeof(std::thread::id));
  
  *thread_id = nt_thread->get_id();
  
  void* obj_thread_id = env->new_object_by_name(env, stack, "TestCase::Util::Thread::ID", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_pointer(env, stack, obj_thread_id, (void*)thread_id);
  
  stack[0].oval = obj_thread_id;
  
  return 0;
}

}