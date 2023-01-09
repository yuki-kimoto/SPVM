#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Runtime.c";

int32_t SPVM__Runtime__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  env->api->runtime->free_object(runtime);
  
  return 0;
}


int32_t SPVM__Compiler__get_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_class_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  void* native_address = env->api->runtime->get_native_method_address(runtime, method_id);
  
  // Native address
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Native::Address", native_address, &e, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Compiler__get_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_class_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  void* native_address = env->api->runtime->get_precompile_method_address(runtime, method_id);
  
  // Native address
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Native::Address", native_address, &e, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Compiler__set_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_class_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;
  void* obj_native_address = stack[3].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  // Native address
  void* native_address = env->get_pointer(env, stack, obj_native_address);
  
  env->api->runtime->set_precompile_method_address(runtime, method_id, native_address);

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

