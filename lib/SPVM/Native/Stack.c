#include "spvm_native.h"

static const char* FILE_NAME = "Native/Stack.c";

int32_t SPVM__Native__Stack__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_my_env = stack[0].oval;
  
  SPVM_ENV* my_env = env->get_pointer(my_env, stack, obj_my_env);
  
  SPVM_VALUE* my_stack = my_env->new_stack(my_env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Native::Stack", my_stack, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_field_object_by_name(env, stack, obj_self, "env", obj_my_env, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Native__Stack__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_my_env = env->get_field_object_by_name(env, stack, obj_self, "env", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* my_stack= env->get_pointer(env, stack, obj_self);
  
  my_env->free_stack(my_env, my_stack);
  
  return 0;
}
