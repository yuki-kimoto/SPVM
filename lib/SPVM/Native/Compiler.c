#include "spvm_native.h"



static const char* FILE_NAME = "Native/Compiler.c";

int32_t SPVM__Native__Compiler__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  // Create compiler
  void* compiler = env->api->compiler->new_object();
  
  void* obj_compiler = env->new_pointer_object_by_name(env, stack, "Native::Compiler", compiler, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_compiler;
  
  return 0;
}

int32_t SPVM__Native__Compiler__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_compiler = stack[0].oval;
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  env->api->compiler->free_object(compiler);
  
  return 0;
}
