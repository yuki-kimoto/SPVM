// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native/MethodCall/Stack.c";

int32_t SPVM__Native__MethodCall__Stack__new_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* method = env->get_class_method(env, stack, basic_type_name, method_name);
  if (!method) {
    return env->die(env, stack, "The \"%s\" method in the \"%s\" class cannot be found.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_self, "method", obj_method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  int32_t method_args_length = env->api->method->get_args_length(env->runtime, method);
  
  if (!(method_args_length == 0)) {
    return env->die(env, stack, "The length of the arguments of the \"%s\" method in the \"%s\" class must be 0.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* return_basic_type = env->api->method->get_return_basic_type(env->runtime, method);
  int32_t return_basic_type_id = env->api->basic_type->get_id(env->runtime, return_basic_type);
  
  if (!(return_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID)) {
    return env->die(env, stack, "The return type of the \"%s\" method in the \"%s\" must be the void type.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__Stack__call(SPVM_ENV* current_env, SPVM_VALUE* current_stack) {

  int32_t error_id = 0;
  
  void* obj_self = current_stack[0].oval;
  
  void* obj_stack = current_stack[1].oval;
  
  SPVM_VALUE* stack = current_env->get_pointer(current_env, current_stack, obj_stack);
  
  SPVM_ENV* env = current_env;
  
  void* obj_method = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "method", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* method = env->get_pointer(env, stack, obj_method);
  
  env->call_method(env, stack, method, 0);
  
  return 0;
}
