// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

static const char* FILE_NAME = "Native::Stack.c";

int32_t SPVM__Native__Stack__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;

  int32_t no_destroy = env->get_field_byte_by_name(env, stack, obj_self, "no_destroy", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  if (!no_destroy) {
  
    void* obj_my_env = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "env", &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
    
    void* my_stack= env->get_pointer(env, stack, obj_self);
    
    my_env->free_stack(my_env, my_stack);
  }
  
  return 0;
}
