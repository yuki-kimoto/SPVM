#include "spvm_native.h"

static const char* FILE_NAME = "Env.c";

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
