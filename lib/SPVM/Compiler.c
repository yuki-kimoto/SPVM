#include "spvm_native.h"

static const char* FILE_NAME = "Compiler.c";

int32_t SPVM__Compiler__compile(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "native_compiler", &e, FILE_NAME, __LINE__);
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  // Compile SPVM
  int32_t compile_error_code = env->api->compiler->compile(compiler, class_name);
  
  void* obj_runtime = NULL;
  if (compile_error_code == 0) {

    // Build runtime information
    void* runtime = env->api->runtime->new_object(env);

    // Runtime allocator
    void* runtime_allocator = env->api->runtime->get_allocator(runtime);
    
    // SPVM 32bit codes
    int32_t* runtime_codes = env->api->compiler->create_runtime_codes(compiler, runtime_allocator);
    
    // Build runtime
    env->api->runtime->build(runtime, runtime_codes);

    // Prepare runtime
    env->api->runtime->prepare(runtime);
    
    obj_runtime = env->new_pointer_object_by_name(env, stack, "Runtime", runtime, &e, FILE_NAME, __LINE__);
  }
  
  stack[0].oval = obj_runtime;
  
  return 0;
}

int32_t SPVM__Compiler__set_start_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_start_file = stack[1].oval;

  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "native_compiler", &e, FILE_NAME, __LINE__);
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  const char* start_file = NULL;
  if (obj_start_file) {
    start_file = env->get_chars(env, stack, obj_start_file);
  }
  env->api->compiler->set_start_file(compiler, start_file);
  
  return 0;
}

int32_t SPVM__Compiler__set_start_line(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t start_line = stack[1].ival;

  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "native_compiler", &e, FILE_NAME, __LINE__);
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  env->api->compiler->set_start_line(compiler, start_line);
  
  return 0;
}

int32_t SPVM__Compiler__get_error_messages(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "native_compiler", &e, FILE_NAME, __LINE__);
  void* compiler = env->get_pointer(env, stack, obj_self);

  int32_t error_messages_length = env->api->compiler->get_error_messages_length(compiler);
  
  void* obj_error_messages = env->new_string_array(env, stack, error_messages_length);
  for (int32_t i = 0; i < error_messages_length; i++) {
    const char* error_message = env->api->compiler->get_error_message(compiler, i);
    void* obj_error_message = env->new_string_nolen(env, stack, error_message);
    env->set_elem_object(env, stack, obj_error_messages, i, obj_error_message);
  }
  
  stack[0].oval = obj_error_messages;
  
  return 0;
}
