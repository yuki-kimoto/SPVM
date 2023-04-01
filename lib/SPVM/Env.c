// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Env.c";

int32_t SPVM__Env__call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  my_env->call_init_blocks(my_env);
  
  return 0;
}

int32_t SPVM__Env__set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_program_name = stack[1].oval;
  
  e = my_env->set_command_info_program_name(my_env, obj_program_name);
  if (e) { return e; }
  
  return 0;
}


int32_t SPVM__Env__set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_argv = stack[1].oval;

  e = my_env->set_command_info_argv(my_env, obj_argv);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__Env__set_command_info_base_time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  int64_t base_time = stack[1].lval;
  
  e = my_env->set_command_info_base_time(my_env, base_time);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__Env__build_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_my_env = stack[0].oval;
  
  SPVM_ENV* my_env = env->get_pointer(my_env, stack, obj_my_env);
  
  SPVM_VALUE* my_stack = my_env->new_stack(my_env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Stack", my_stack, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_field_object_by_name(env, stack, obj_self, "env", obj_my_env, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Env__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  SPVM_ENV* my_env= env->get_pointer(env, stack, obj_self);
  
  // Cleanup global varialbes
  my_env->cleanup_global_vars(my_env);

  my_env->free_env_raw(my_env);
  
  return 0;
}
