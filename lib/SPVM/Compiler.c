#include "spvm_native.h"



static const char* FILE_NAME = "Compiler.c";

int32_t SPVM__Compiler__compile(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPVM__Compiler__call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  my_env->call_init_blocks(my_env);
  
  return 0;
}

int32_t SPVM__Compiler__set_command_info(SPVM_ENV* env, SPVM_VALUE* stack) {
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

int32_t SPVM__Compiler__call_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}
