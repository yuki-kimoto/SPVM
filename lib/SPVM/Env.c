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

int32_t SPVM__Env__set_command_info(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_program_name = stack[1].oval;
  
  void* obj_argv = stack[2].oval;

  e = my_env->set_command_info_program_name(my_env, obj_program_name);
  if (e) { return e; }
  
  e = my_env->set_command_info_argv(my_env, obj_argv);
  if (e) { return e; }
  
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
