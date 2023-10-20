#include "spvm_native.h"

#include <assert.h>

#include <iostream>
#include <thread>

extern "C" {

static const char* FILE_NAME = "TestCase/Util/Thread/ThisThread.cpp";

int32_t SPVM__TestCase__Util__Thread__ThisThread__get_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  std::thread::id* thread_id = (std::thread::id*)env->new_memory_block(env, stack, sizeof(std::thread::id));
  
  *thread_id = std::this_thread::get_id();
  
  void* obj_thread_id = env->new_object_by_name(env, stack, "TestCase::Util::Thread::ID", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_pointer(env, stack, obj_thread_id, (void*)thread_id);
  
  stack[0].oval = obj_thread_id;
  
  return 0;
}

}
