// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/ModuleFile.c";

/*
  const char* (*get_module_name)(void* compiler, void* module_file);
  void (*set_module_name)(void* compiler, void* module_file, void* module_name);
  const char* (*get_file)(void* compiler, void* module_file);
  void (*set_file)(void* compiler, void* module_file, void* file);
  const char* (*get_dir)(void* compiler, void* module_file);
  void (*set_dir)(void* compiler, void* module_file, void* dir);
  const char* (*get_rel_file)(void* compiler, void* module_file);
  void (*set_rel_file)(void* compiler, void* module_file, void* rel_file);
  const char* (*get_content)(void* compiler, void* module_file);
  void (*set_content)(void* compiler, void* module_file, void* content);
  int32_t (*get_content_length)(void* compiler, void* module_file);
  void (*set_content_length)(void* compiler, void* module_file, int32_t content_length);
*/

int32_t SPVM__Native__ModuleFile__get_module_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  if (!module_file) {
    return env->die(env, stack, "The module file was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  if (!compiler) {
    return env->die(env, stack, "The compiler was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_name = env->api->module_file->get_module_name(compiler, module_file);
  
  void* obj_module_name = env->new_string_nolen(env, stack, module_name);
  
  stack[0].oval = obj_module_name;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_module_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  if (!module_file) {
    return env->die(env, stack, "The module file was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_module_name = stack[1].oval;
  
  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  if (!compiler) {
    return env->die(env, stack, "The compiler was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_name = NULL;
  if (obj_module_name) {
    module_name = env->get_chars(env, stack, obj_module_name);
  }
  
  env->api->module_file->set_module_name(compiler, module_file, module_name);
  
  return 0;
}
