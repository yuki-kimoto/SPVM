// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native/MethodCall/EnvStack.c";

int32_t SPVM__Native__MethodCall__EnvStack__call_class_method(SPVM_ENV* current_env, SPVM_VALUE* current_stack) {
  
  int32_t current_error_id = 0;
  
  void* obj_env = current_stack[0].oval;
  
  if (!obj_env) {
    return current_env->die(current_env, current_stack, "The $env must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_ENV* env = env->get_pointer(current_env, current_stack, obj_env);
  
  void* obj_stack = current_stack[1].oval;
  
  if (!obj_stack) {
    return current_env->die(current_env, current_stack, "The $stack must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  SPVM_VALUE* stack = env->get_pointer(current_env, current_stack, obj_stack);
  
  void* obj_basic_type_name = current_stack[2].oval;
  
  if (!obj_basic_type_name) {
    return current_env->die(current_env, current_stack, "The $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = current_env->get_chars(current_env, current_stack, obj_basic_type_name);
  
  void* obj_method_name = current_stack[3].oval;
  
  if (!obj_method_name) {
    return current_env->die(current_env, current_stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = current_env->get_chars(current_env, current_stack, obj_method_name);
  
  void* method = env->get_class_method(env, stack, basic_type_name, method_name);
  if (!method) {
    return current_env->die(current_env, current_stack, "The \"%s\" method in the \"%s\" class cannot be found.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t error_id = 0;
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) {
    void* obj_exception = env->get_exception(env, stack);
    const char* exception = env->get_chars(env, stack, obj_exception);
    return current_env->die(current_env, current_stack, "%s", method_name, basic_type_name, exception, __func__, FILE_NAME, __LINE__);
  }
  
  int32_t method_args_length = env->api->method->get_args_length(env->runtime, method);
  
  if (!(method_args_length == 0)) {
    return current_env->die(current_env, current_stack, "The length of the arguments of the \"%s\" method in the \"%s\" class must be 0.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* return_basic_type = env->api->method->get_return_basic_type(env->runtime, method);
  int32_t return_basic_type_id = env->api->basic_type->get_id(env->runtime, return_basic_type);
  
  if (!(return_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID)) {
    return current_env->die(current_env, current_stack, "The return type of the \"%s\" method in the \"%s\" must be the void type.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  error_id = env->call_method(env, stack, method, 0);
  if (error_id) {
    void* obj_exception = env->get_exception(env, stack);
    const char* exception = env->get_chars(env, stack, obj_exception);
    return current_env->die(current_env, current_stack, "The method call of the \"%s\" method in the \"%s\" failed:%s", method_name, basic_type_name, exception, __func__, FILE_NAME, __LINE__);
  }
  
  return 0;
}
