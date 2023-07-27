// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/ModuleFile.c";

int32_t SPVM__Native__ModuleFile__get_module_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* module_name = env->api->module_file->get_module_name(compiler, module_file);
  
  void* obj_module_name = env->new_string_nolen(env, stack, module_name);
  
  stack[0].oval = obj_module_name;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__get_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* file = env->api->module_file->get_file(compiler, module_file);
  
  void* obj_file = env->new_string_nolen(env, stack, file);
  
  stack[0].oval = obj_file;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_file = stack[1].oval;
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* file = NULL;
  if (obj_file) {
    file = env->get_chars(env, stack, obj_file);
  }
  
  env->api->module_file->set_file(compiler, module_file, file);
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__get_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* dir = env->api->module_file->get_dir(compiler, module_file);
  
  void* obj_dir = env->new_string_nolen(env, stack, dir);
  
  stack[0].oval = obj_dir;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_dir = stack[1].oval;
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* dir = NULL;
  if (obj_dir) {
    dir = env->get_chars(env, stack, obj_dir);
  }
  
  env->api->module_file->set_dir(compiler, module_file, dir);
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__get_rel_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* rel_file = env->api->module_file->get_rel_file(compiler, module_file);
  
  void* obj_rel_file = env->new_string_nolen(env, stack, rel_file);
  
  stack[0].oval = obj_rel_file;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_rel_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_rel_file = stack[1].oval;
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* rel_file = NULL;
  if (obj_rel_file) {
    rel_file = env->get_chars(env, stack, obj_rel_file);
  }
  
  env->api->module_file->set_rel_file(compiler, module_file, rel_file);
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__get_content(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* content = env->api->module_file->get_content(compiler, module_file);
  
  void* obj_content = env->new_string_nolen(env, stack, content);
  
  stack[0].oval = obj_content;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_content(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_content = stack[1].oval;
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  const char* content = NULL;
  if (obj_content) {
    content = env->get_chars(env, stack, obj_content);
  }
  
  env->api->module_file->set_content(compiler, module_file, content);
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__get_content_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  int32_t content_length = env->api->module_file->get_content_length(compiler, module_file);
  
  stack[0].ival = content_length;
  
  return 0;
}

int32_t SPVM__Native__ModuleFile__set_content_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* module_file = env->get_pointer(env, stack, obj_self);
  
  int32_t content_length = stack[1].ival;
  
  void* obj_compiler = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* compiler = env->get_pointer(env, stack, obj_compiler);
  
  env->api->module_file->set_content_length(compiler, module_file, content_length);
  
  return 0;
}

