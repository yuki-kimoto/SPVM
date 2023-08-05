// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native.c";

int32_t SPVM__Native__get_current_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_env = env->new_pointer_object_by_name(env, stack, "Native::Env", env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, obj_env, "no_destroy", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_env;
  
  return 0;
}

int32_t SPVM__Native__get_current_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_stack = env->new_pointer_object_by_name(env, stack, "Native::Stack", stack, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_byte_by_name(env, stack, obj_stack, "no_destroy", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_stack;
  
  return 0;
}

