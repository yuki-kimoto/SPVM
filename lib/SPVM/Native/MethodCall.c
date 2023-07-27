// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/MethodCall.c";

int32_t SPVM__Native__MethodCall__new_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_runtime = stack[0].oval;
  
  if (!obj_runtime) {
    return env->die(env, stack, "The $runtime must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_basic_type_name = stack[0].oval;
  
  if (!obj_basic_type_name) {
    return env->die(env, stack, "The $basic_type_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* obj_method_name = stack[0].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The $method_name must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* method = env->get_class_method(env, stack, basic_type_name, method_name);
  if (!method) {
    return env->die(env, stack, "The \"%s\" method in the \"%s\" class cannot be found.", method_name, basic_type_name, __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method_call = env->new_pointer_object_by_name(env, stack, "Native::MethodCall", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method_call, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  return 0;
}

int32_t SPVM__Native__MethodCall__new_instance_method_static(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__new_instance_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__init(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_byte_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_short_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_int_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_long_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_float_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_double_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_byte_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_short_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_int_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_long_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_float_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__set_stack_mulnum_double_ref(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__call(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

int32_t SPVM__Native__MethodCall__get_stack_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}

