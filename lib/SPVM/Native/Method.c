// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/Method.c";

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

int32_t SPVM__Native__Method__get_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t index = env->api->method->get_index(runtime, method);
  
  stack[0].ival = index;
  
  return 0;
}

int32_t SPVM__Native__Method__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* name = env->api->method->get_name(runtime, method);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type = env->api->method->get_return_basic_type(runtime, method);
  
  void* obj_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_dimension = env->api->method->get_return_type_dimension(runtime, method);
  
  stack[0].ival = type_dimension;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_type_flag(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_flag = env->api->method->get_return_type_flag(runtime, method);
  
  stack[0].ival = type_flag;
  
  return 0;
}

int32_t SPVM__Native__Method__get_current_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* current_basic_type = env->api->method->get_current_basic_type(runtime, method);
  
  void* obj_current_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", current_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_current_basic_type, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_current_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Method__get_arg_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  int32_t arg_index = stack[1].ival;
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* arg = env->api->method->get_arg_by_index(runtime, method, arg_index);
  if (!arg) {
    return env->die(env, stack, "The argument is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_arg = env->new_pointer_object_by_name(env, stack, "Native::Arg", arg, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_arg, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_arg;
  
  return 0;
}

int32_t SPVM__Native__Method__get_args_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_args_length = env->api->method->get_args_length(runtime, method);
  
  stack[0].ival = get_args_length;
  
  return 0;
}

int32_t SPVM__Native__Method__get_required_args_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_required_args_length = env->api->method->get_required_args_length(runtime, method);
  
  stack[0].ival = get_required_args_length;
  
  return 0;
}

int32_t SPVM__Native__Method__is_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_class_method = env->api->method->is_class_method(runtime, method);
  
  stack[0].ival = is_class_method;
  
  return 0;
}

int32_t SPVM__Native__Method__is_anon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_anon = env->api->method->is_anon(runtime, method);
  
  stack[0].ival = is_anon;
  
  return 0;
}

int32_t SPVM__Native__Method__is_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_native = env->api->method->is_native(runtime, method);
  
  stack[0].ival = is_native;
  
  return 0;
}

int32_t SPVM__Native__Method__is_precompile(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_precompile = env->api->method->is_precompile(runtime, method);
  
  stack[0].ival = is_precompile;
  
  return 0;
}

int32_t SPVM__Native__Method__is_enum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_enum = env->api->method->is_enum(runtime, method);
  
  stack[0].ival = is_enum;
  
  return 0;
}

int32_t SPVM__Native__Method__get_native_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* native_address = env->api->method->get_native_address(runtime, method);
  
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Address", native_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Native__Method__set_native_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_native_address = stack[1].oval;
  
  void* native_address = env->get_pointer(env, stack, obj_native_address);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_native_address(runtime, method, native_address);
  
  return 0;
}

int32_t SPVM__Native__Method__get_precompile_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* Precompile_address = env->api->method->get_precompile_address(runtime, method);
  
  void* obj_precompile_address = env->new_pointer_object_by_name(env, stack, "Address", Precompile_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_precompile_address;
  
  return 0;
}

int32_t SPVM__Native__Method__set_precompile_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_precompile_address = stack[1].oval;
  
  void* precompile_address = env->get_pointer(env, stack, obj_precompile_address);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_precompile_address(runtime, method, precompile_address);
  
  return 0;
}

int32_t SPVM__Native__Method__is_precompile_fallback(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_precompile = env->api->method->is_precompile_fallback(runtime, method);
  
  stack[0].ival = is_precompile;
  
  return 0;
}

int32_t SPVM__Native__Method__set_is_precompile_fallback(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* method = env->get_pointer(env, stack, obj_self);
  
  int32_t is_precompile_fallback = stack[1].ival;
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_is_precompile_fallback(runtime, method, is_precompile_fallback);
  
  return 0;
}

