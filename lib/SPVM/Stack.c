#include "spvm_native.h"

static const char* FILE_NAME = "Stack.c";

int32_t SPVM__Stack__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
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
