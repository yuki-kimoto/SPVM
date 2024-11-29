// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native/Env.c";

int32_t SPVM__Native__Env__new_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_my_env = stack[0].oval;
  
  SPVM_ENV* my_env = env->get_pointer(my_env, stack, obj_my_env);
  
  SPVM_VALUE* my_stack = my_env->new_stack(my_env);
  
  void* obj_address_my_stack = env->new_pointer_object_by_name(env, stack, "Address", my_stack, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_my_stack;
  env->call_class_method_by_name(env, stack, "Native::Stack", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_my_stack = stack[0].oval;
  
  env->set_field_object_by_name(env, stack, obj_my_stack, "env", obj_my_env, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_my_stack;
  
  return 0;
}

int32_t SPVM__Native__Env__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t no_free = env->no_free(env, stack, obj_self);
  if (error_id) { return error_id; }
  
  if (!no_free) {
    SPVM_ENV* self = env->get_pointer(env, stack, obj_self);
    
    self->free_env(self);
  }
  
  return 0;
}
