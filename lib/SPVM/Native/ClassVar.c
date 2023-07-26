// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/ClassVar.c";

static void* get_field_native_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line) {
  
  *error_id = 0;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file_name, line);
  
  if (*error_id) { return NULL; }
  
  if (!obj_runtime) {
    *error_id = env->die(env, stack, "The %s cannot be got.", field_name, func_name, file_name, line);
    return NULL;
  }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    *error_id = env->die(env, stack, "The pointer to the native %s cannot be got.", field_name, func_name, file_name, line);
    return NULL;
  }
  
  return obj_runtime;
}

int32_t SPVM__Native__ClassVar__get_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t index = env->api->class_var->get_index(runtime, class_var);
  
  stack[0].ival = index;
  
  return 0;
}

int32_t SPVM__Native__ClassVar__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* name = env->api->class_var->get_name(runtime, class_var);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__ClassVar__get_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type = env->api->class_var->get_basic_type(runtime, class_var);
  
  void* obj_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_basic_type;
  
  return 0;
}

int32_t SPVM__Native__ClassVar__get_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_dimension = env->api->class_var->get_type_dimension(runtime, class_var);
  
  stack[0].ival = type_dimension;
  
  return 0;
}

int32_t SPVM__Native__ClassVar__get_type_flag(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_flag = env->api->class_var->get_type_flag(runtime, class_var);
  
  stack[0].ival = type_flag;
  
  return 0;
}

int32_t SPVM__Native__ClassVar__get_current_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* class_var = env->get_pointer(env, stack, obj_self);
  
  if (!class_var) {
    return env->die(env, stack, "The class variable was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* current_basic_type = env->api->class_var->get_current_basic_type(runtime, class_var);
  
  void* obj_current_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", current_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_current_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_current_basic_type;
  
  return 0;
}
