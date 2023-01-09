#include "spvm_native.h"

static const char* FILE_NAME = "Compiler.c";

int32_t SPVM__Compiler__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_native_compiler = env->get_field_object_by_name(env, stack, obj_self, "native_compiler", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  void* compiler = env->get_pointer(env, stack, obj_native_compiler);
  
  env->api->compiler->free_object(compiler);
  
  return 0;
}

int32_t SPVM__Compiler__compile(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}
