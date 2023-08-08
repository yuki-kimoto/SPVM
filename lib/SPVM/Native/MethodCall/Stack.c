// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native/MethodCall/Stack.c";

int32_t SPVM__Native__MethodCall__Stack__call_callback(SPVM_ENV* current_env, SPVM_VALUE* current_stack) {

  int32_t current_error_id = 0;
  
  void* obj_stack = current_stack[0].oval;
  
  if (!obj_stack) {
    return current_env->die(current_env, current_stack, "The $stack must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_callback = current_stack[1].oval;
  
  if (!obj_callback) {
    return current_env->die(current_env, current_stack, "The $callback must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_VALUE* stack = current_env->get_pointer(current_env, current_stack, obj_stack);
  
  SPVM_ENV* env = current_env;
  
  int32_t error_id = 0;
  
  *current_stack[2].iref = 0;
  
  stack[0].oval = obj_callback;
  env->call_instance_method_by_name(env, stack, "", 0, &error_id, __func__, FILE_NAME, __LINE__);
  
  *current_stack[2].iref = error_id;
  
  return 0;
}

int32_t SPVM__Native__MethodCall__Stack__get_exception(SPVM_ENV* current_env, SPVM_VALUE* current_stack) {

  int32_t current_error_id = 0;
  
  void* obj_stack = current_stack[0].oval;
  
  if (!obj_stack) {
    return current_env->die(current_env, current_stack, "The $stack must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_VALUE* stack = current_env->get_pointer(current_env, current_stack, obj_stack);
  
  SPVM_ENV* env = current_env;
  
  void* obj_exception = env->get_exception(env, stack);
  
  void* obj_exception_clone = NULL;
  if (obj_exception) {
    const char* exception = env->get_chars(env, stack, obj_exception);
    
    int32_t exception_length = env->length(env, stack, obj_exception);
    
    obj_exception_clone = current_env->new_string(current_env, current_stack, exception, exception_length);
  }
  
  current_stack[0].oval = obj_exception_clone;
  
  return 0;
}

int32_t SPVM__Native__MethodCall__Stack__set_exception(SPVM_ENV* current_env, SPVM_VALUE* current_stack) {
  
  int32_t current_error_id = 0;
  
  void* obj_stack = current_stack[0].oval;
  
  if (!obj_stack) {
    return current_env->die(current_env, current_stack, "The $stack must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_exception = current_stack[1].oval;
  
  SPVM_VALUE* stack = current_env->get_pointer(current_env, current_stack, obj_stack);
  
  SPVM_ENV* env = current_env;
  
  void* obj_exception_clone = NULL;
  if (obj_exception) {
    const char* exception = current_env->get_chars(current_env, current_stack, obj_exception);
    
    int32_t exception_length = current_env->length(current_env, current_stack, obj_exception);
    
    obj_exception_clone = env->new_string(env, stack, exception, exception_length);
  }
  
  env->set_exception(env, stack, obj_exception_clone);
  
  return 0;
}
