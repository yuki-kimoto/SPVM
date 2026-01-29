// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native.c";

int32_t SPVM__Native__get_current_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_address_env = env->new_pointer_object_by_name(env, stack, "Address", env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_env;
  env->call_class_method_by_name(env, stack, "Native::Env", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_env = stack[0].oval;
  
  void* obj_address_runtime = env->new_pointer_object_by_name(env, stack, "Address", env->runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_runtime;
  env->call_class_method_by_name(env, stack, "Native::Runtime", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_runtime = stack[0].oval;
  
  env->set_field_object_by_name(env, stack, obj_env, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_address_compiler = env->new_pointer_object_by_name(env, stack, "Address", env->api->runtime->get_compiler(env->runtime), &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_compiler;
  env->call_class_method_by_name(env, stack, "Native::Compiler", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_compiler = stack[0].oval;
  
  env->set_field_object_by_name(env, stack, obj_runtime, "compiler", obj_compiler, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_compiler, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void** obj_runtime_ref = env->get_field_object_ref_by_name(env, stack, obj_compiler, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->weaken(env, stack, obj_runtime_ref);
  
  env->set_no_free(env, stack, obj_env, 1);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_env;
  
  return 0;
}

int32_t SPVM__Native__get_current_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_address_stack = env->new_pointer_object_by_name(env, stack, "Address", stack, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_stack;
  env->call_class_method_by_name(env, stack, "Native::Stack", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_stack = stack[0].oval;
  
  env->set_no_free(env, stack, obj_stack, 1);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_stack;
  
  return 0;
}

int32_t SPVM__Native__check_bootstrap_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The basic type name $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  error_id = env->check_bootstrap_method(env, stack, basic_type_name);
  if (error_id) {
    return env->die(env, stack, env->get_chars(env, stack, env->get_exception(env, stack)), __func__, FILE_NAME, __LINE__);
  }
  
  return 0;
}

