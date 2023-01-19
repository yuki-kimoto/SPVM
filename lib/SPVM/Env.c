#include "spvm_native.h"

static const char* FILE_NAME = "Env.c";

int32_t SPVM__Env__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_runtime = stack[0].oval;
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_ENV* my_env = env->new_env_raw(env);
  
  // Set runtime information
  my_env->runtime = runtime;
  
  // Initialize env
  my_env->init_env(my_env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Env", my_env, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_field_object_by_name(env, stack, obj_self, "runtime", obj_runtime, &e, FILE_NAME, __LINE__);
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
