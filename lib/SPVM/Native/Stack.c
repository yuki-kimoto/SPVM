// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native::Stack.c";

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

int32_t SPVM__Native__Stack__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_my_env = get_field_native_object_by_name(env, stack, obj_self, "env", &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* my_stack= env->get_pointer(env, stack, obj_self);
  
  my_env->free_stack(my_env, my_stack);
  
  return 0;
}
