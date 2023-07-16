// Copyright (c) 2023 Yuki Kimot
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/BasicType.c";

int32_t SPVM__Native__BasicType__get_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t id = env->api->basic_type->get_id(runtime, basic_type);
  
  stack[0].ival = id;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* name = env->api->basic_type->get_name(runtime, basic_type);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_module_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_dir = env->api->basic_type->get_module_dir(runtime, basic_type);
  
  void* obj_module_dir = env->new_string_nolen(env, stack, module_dir);
  
  stack[0].oval = obj_module_dir;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_module_rel_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_rel_file = env->api->basic_type->get_module_rel_file(runtime, basic_type);
  
  void* obj_module_rel_file = env->new_string_nolen(env, stack, module_rel_file);
  
  stack[0].oval = obj_module_rel_file;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_parent(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* parent = env->api->basic_type->get_parent(runtime, basic_type);
  
  void* obj_parent = env->new_pointer_object_by_name(env, stack, "Native::BasicType", parent, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_parent;
  
  return 0;
}
