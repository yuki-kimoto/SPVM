// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Env.c";

int32_t SPVM__Env__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_runtime = stack[0].oval;
  
  SPVM_ENV* new_env = env->new_env(env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Env", new_env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (obj_runtime) {
    env->set_field_object_by_name(env, stack, obj_self, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    void* runtime = env->get_pointer(env, stack, obj_runtime);
    new_env->runtime = runtime;
  }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Env__call_init_methods(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  my_env->call_init_methods(my_env, my_stack);
  
  return 0;
}

int32_t SPVM__Env__cleanup_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  my_env->cleanup_env(my_env, my_stack);
  
  return 0;
}

int32_t SPVM__Env__set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  void* obj_program_name = stack[2].oval;
  
  error_id = my_env->set_command_info_program_name(my_env, my_stack, obj_program_name);
  if (error_id) { return error_id; }
  
  return 0;
}


int32_t SPVM__Env__set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  void* obj_argv = stack[2].oval;

  error_id = my_env->set_command_info_argv(my_env, my_stack, obj_argv);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Env__set_command_info_base_time(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  int64_t base_time = stack[2].lval;
  
  error_id = my_env->set_command_info_base_time(my_env, my_stack, base_time);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Env__get_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].oval = env->get_exception(env, stack);
  
  return 0;
}

int32_t SPVM__Env__set_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_exception = stack[0].oval;
  
  env->set_exception(env, stack, obj_exception);
  
  return 0;
}

int32_t SPVM__Env__new_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_my_env = stack[0].oval;
  
  SPVM_ENV* my_env = env->get_pointer(my_env, stack, obj_my_env);
  
  SPVM_VALUE* my_stack = my_env->new_stack(my_env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Stack", my_stack, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_self, "env", obj_my_env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Env__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_self);
  
  void* runtime = env->runtime;
  
  // If the runtime exists, this env was freed by the runtime
  if (!runtime) {
    my_env->free_env(my_env);
  }
  
  return 0;
}
