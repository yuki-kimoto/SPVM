// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/Arg.c";

int32_t SPVM__Native__Arg__get_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t index = env->api->arg->get_index(runtime, arg);
  
  stack[0].ival = index;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type = env->api->arg->get_basic_type(runtime, arg);
  
  void* obj_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_dimension = env->api->arg->get_type_dimension(runtime, arg);
  
  stack[0].ival = type_dimension;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_type_flag(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_flag = env->api->arg->get_type_flag(runtime, arg);
  
  stack[0].ival = type_flag;
  
  return 0;
}

int32_t SPVM__Native__Arg__is_optional(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_optional = env->api->arg->is_optional(runtime, arg);
  
  stack[0].ival = is_optional;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].bval = default_value.bval;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].sval = default_value.sval;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].ival = default_value.ival;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].lval = default_value.lval;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].fval = default_value.fval;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].dval = default_value.dval;
  
  return 0;
}

int32_t SPVM__Native__Arg__get_default_value_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* arg = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_defined_and_has_pointer_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_VALUE default_value = env->api->arg->get_default_value(runtime, arg);
  
  stack[0].oval = default_value.oval;
  
  return 0;
}
