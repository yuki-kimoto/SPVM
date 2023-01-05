#include "spvm_native.h"



static const char* FILE_NAME = "Compiler.c";

int32_t SPVM__Compiler__foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}


int32_t SPVM__Compiler__new_native_compiler(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__set_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__get_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__set_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__build_class_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__build_method_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__new_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__new_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_my_stack = stack[1].oval;
  SPVM_VALUE* my_stack = env->get_pointer(env, stack, obj_my_stack);
  
  my_env->call_init_blocks(my_env, my_stack);
  
  return 0;
}

int32_t SPVM__Compiler__set_command_info(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__call_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__compile(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}
