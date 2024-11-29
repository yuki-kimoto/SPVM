// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/Field.c";

int32_t SPVM__Native__Field__get_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t index = env->api->field->get_index(runtime, field);
  
  stack[0].ival = index;
  
  return 0;
}

int32_t SPVM__Native__Field__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* name = env->api->field->get_name(runtime, field);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__Field__get_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type = env->api->field->get_basic_type(runtime, field);
  
  void* obj_address_basic_type = env->new_pointer_object_by_name(env, stack, "Address", basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_basic_type;
  env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_basic_type = stack[0].oval;
  env->set_no_free(env, stack, obj_basic_type, 1);
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Field__get_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_dimension = env->api->field->get_type_dimension(runtime, field);
  
  stack[0].ival = type_dimension;
  
  return 0;
}

int32_t SPVM__Native__Field__get_type_flag(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_flag = env->api->field->get_type_flag(runtime, field);
  
  stack[0].ival = type_flag;
  
  return 0;
}

int32_t SPVM__Native__Field__get_current_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* field = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* current_basic_type = env->api->field->get_current_basic_type(runtime, field);
  
  void* obj_address_current_basic_type = env->new_pointer_object_by_name(env, stack, "Address", current_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_current_basic_type;
  env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_current_basic_type = stack[0].oval;
  env->set_no_free(env, stack, obj_current_basic_type, 1);
  
  env->set_field_object_by_name(env, stack, obj_current_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_current_basic_type;
  
  return 0;
}
