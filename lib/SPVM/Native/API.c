// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native/API.c";

int32_t SPVM__Native__API__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self= env->new_object_by_name(env, stack, "Native::API", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* obj_api_env = stack[0].oval;
  
  if (!obj_api_env) {
    return env->die(env, stack, "The runtime environemnt $env must be defined.", __func__, __FILE__, __LINE__);
  }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  env->set_field_object_by_name(env, stack, obj_self, "env", obj_api_env, &error_id, __func__, FILE_NAME, __LINE__);
  
  void* obj_api_stack = stack[1].oval;
  
  if (!obj_api_stack) {
    return env->die(env, stack, "The runtime stack $stack must be defined.", __func__, __FILE__, __LINE__);
  }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  env->set_field_object_by_name(env, stack, obj_self, "stack", obj_api_stack, &error_id, __func__, FILE_NAME, __LINE__);
  
  int32_t check_ok = env->check_stack_env(api_env, api_stack);
  
  if (!check_ok) {
    return env->die(env, stack, "The runtime stack $stack must be created by the runtime environemnt $env.", __func__, __FILE__, __LINE__);
  }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Native__API__call_init_methods(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  api_env->call_init_methods(api_env, api_stack);
  
  return 0;
}

int32_t SPVM__Native__API__destroy_class_vars(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  api_env->destroy_class_vars(api_env, api_stack);
  
  return 0;
}

int32_t SPVM__Native__API__set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  void* obj_program_name = stack[1].oval;
  
  void* obj_probram_name_copy = env->copy(env, stack, obj_program_name);
  
  error_id = api_env->set_command_info_program_name(api_env, api_stack, obj_probram_name_copy);
  if (error_id) { return error_id; }
  
  return 0;
}


int32_t SPVM__Native__API__set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  void* obj_argv = stack[1].oval;
  
  void* obj_argv_copy = NULL;
  {
    stack[0].oval = obj_program_name;
    env->call_class_method_by_name(env, stack, "Array", "copy_string", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    obj_argv_copy = stack[0].oval;
  }
  
  error_id = api_env->set_command_info_argv(api_env, api_stack, obj_argv_copy);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__API__set_command_info_base_time(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  int64_t base_time = stack[1].lval;
  
  error_id = api_env->set_command_info_base_time(api_env, api_stack, base_time);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__API__get_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_api_env = env->get_field_object_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_ENV* api_env = env->get_pointer(env, stack, obj_api_env);
  
  void* obj_api_stack = stack->get_field_object_by_name(stack, stack, obj_self, "stack", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  SPVM_VALUE* api_stack = stack->get_pointer(stack, stack, obj_api_stack);
  
  void* obj_exception = api_env->get_exception(api_env, api_stack);
  
  void* obj_exception_copy = env->copy(env, stack, obj_exception_copy);
  
  stack[0].oval = obj_exception_copy;
  
  return 0;
}

int32_t SPVM__Native__API__set_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_exception = stack[0].oval;
  
  void* obj_exception_copy = env->copy(env, stack, obj_exception);
  
  env->set_exception(env, stack, obj_exception_copy);
  
  return 0;
}

