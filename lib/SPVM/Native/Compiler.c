// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native::Compiler.c";

int32_t SPVM__Native__Compiler__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  // Create compiler
  void* compiler = env->api->compiler->new_instance();
  
  void* obj_self = env->new_pointer_object_by_name(env, stack, "Native::Compiler", compiler, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->api->compiler->get_runtime(compiler);
  
  void* obj_runtime = env->new_pointer_object_by_name(env, stack, "Native::Runtime", runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_runtime, "compiler", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void** obj_compiler_address = env->get_field_object_address_by_name(env, stack, obj_runtime, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  env->weaken(env, stack, obj_compiler_address);
  
  env->set_field_object_by_name(env, stack, obj_self, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

int32_t SPVM__Native__Compiler__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  env->set_field_object_by_name(env, stack, obj_self, "runtime", NULL, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  env->api->compiler->free_instance(compiler);
  
  return 0;
}

int32_t SPVM__Native__Compiler__compile(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = NULL;
  if (obj_basic_type_name) {
    basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  }
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  // Compile SPVM
  int32_t compile_die_error_id = env->api->compiler->compile(compiler, basic_type_name);
  
  int32_t success = 0;
  if (compile_die_error_id == 0) {
    success = 1;
  }
  
  stack[0].ival = success;
  
  return 0;
}

int32_t SPVM__Native__Compiler__get_runtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_runtime;
  
  return 0;
}

int32_t SPVM__Native__Compiler__set_start_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_start_file = stack[1].oval;
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  const char* start_file = NULL;
  if (obj_start_file) {
    start_file = env->get_chars(env, stack, obj_start_file);
  }
  env->api->compiler->set_start_file(compiler, start_file);
  
  return 0;
}

int32_t SPVM__Native__Compiler__set_start_line(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t start_line = stack[1].ival;
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  env->api->compiler->set_start_line(compiler, start_line);
  
  return 0;
}

int32_t SPVM__Native__Compiler__get_error_messages(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
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

int32_t SPVM__Native__Compiler__add_include_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_include_dir = stack[1].oval;
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  const char* include_dir = NULL;
  if (obj_include_dir) {
    include_dir = env->get_chars(env, stack, obj_include_dir);
  }
  env->api->compiler->add_include_dir(compiler, include_dir);
  
  return 0;
}

int32_t SPVM__Native__Compiler__get_class_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_class_name = stack[1].oval;
  
  if (!obj_class_name) {
    return env->die(env, stack, "The $class_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  void* compiler = env->get_pointer(env, stack, obj_self);
  
  void* class_file = env->api->compiler->get_class_file(compiler, class_name);
  
  void* obj_class_file = NULL;
  if (class_file) {
    obj_class_file = env->new_pointer_object_by_name(env, stack, "Native::ClassFile", class_file, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    env->set_field_object_by_name(env, stack, obj_class_file, "compiler", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].oval = obj_class_file;
  
  return 0;
}
