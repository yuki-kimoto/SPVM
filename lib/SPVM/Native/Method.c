// Copyright (c) 2023 [--user-name]
// MIT License

#include "spvm_native.h"



static const char* FILE_NAME = "Native/Method.c";

static void* get_field_native_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line) {
  
  *error_id = 0;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file_name, line);
  
  if (*error_id) { return NULL; }
  
  if (!obj_runtime) {
    *error_id = env->die(env, stack, "The %s cannot be got.", func_name, file_name, line, field_name);
    return NULL;
  }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    *error_id = env->die(env, stack, "The pointer to the native %s cannot be got.", func_name, file_name, line, field_name);
    return NULL;
  }
  
  return obj_runtime;
}

int32_t SPVM__Native__Method__get_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t index = env->api->method->get_index(runtime, self);
  
  stack[0].ival = index;
  
  return 0;
}

int32_t SPVM__Native__Method__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* name = env->api->method->get_name(runtime, self);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type = env->api->method->get_return_basic_type(runtime, self);
  
  void* obj_address_basic_type = env->new_pointer_object_by_name(env, stack, "Address", basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_basic_type;
  env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_basic_type = stack[0].oval;
  env->set_no_free(env, stack, obj_basic_type, 1);
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_basic_type, "ref_method", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_dimension = env->api->method->get_return_type_dimension(runtime, self);
  
  stack[0].ival = type_dimension;
  
  return 0;
}

int32_t SPVM__Native__Method__get_return_type_flag(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t type_flag = env->api->method->get_return_type_flag(runtime, self);
  
  stack[0].ival = type_flag;
  
  return 0;
}

int32_t SPVM__Native__Method__get_current_basic_type(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* current_basic_type = env->api->method->get_current_basic_type(runtime, self);
  
  void* obj_address_current_basic_type = env->new_pointer_object_by_name(env, stack, "Address", current_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_current_basic_type;
  env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_current_basic_type = stack[0].oval;
  env->set_no_free(env, stack, obj_current_basic_type, 1);
  
  env->set_field_object_by_name(env, stack, obj_current_basic_type, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_current_basic_type, "ref_method", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_current_basic_type;
  
  return 0;
}

int32_t SPVM__Native__Method__get_arg_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t arg_index = stack[1].ival;
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* arg = env->api->method->get_arg_by_index(runtime, self, arg_index);
  if (!arg) {
    return env->die(env, stack, "The argument is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_arg = env->new_pointer_object_by_name(env, stack, "Address", arg, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_arg;
  env->call_class_method_by_name(env, stack, "Native::Arg", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_arg = stack[0].oval;
  env->set_no_free(env, stack, obj_arg, 1);
  
  env->set_field_object_by_name(env, stack, obj_arg, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_arg, "ref_method", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_arg;
  
  return 0;
}

int32_t SPVM__Native__Method__get_args_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_args_length = env->api->method->get_args_length(runtime, self);
  
  stack[0].ival = get_args_length;
  
  return 0;
}

int32_t SPVM__Native__Method__get_required_args_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_required_args_length = env->api->method->get_required_args_length(runtime, self);
  
  stack[0].ival = get_required_args_length;
  
  return 0;
}

int32_t SPVM__Native__Method__is_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_class_method = env->api->method->is_class_method(runtime, self);
  
  stack[0].ival = is_class_method;
  
  return 0;
}

int32_t SPVM__Native__Method__is_anon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_anon = env->api->method->is_anon(runtime, self);
  
  stack[0].ival = is_anon;
  
  return 0;
}

int32_t SPVM__Native__Method__is_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_native = env->api->method->is_native(runtime, self);
  
  stack[0].ival = is_native;
  
  return 0;
}

int32_t SPVM__Native__Method__is_precompile(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_precompile = env->api->method->is_precompile(runtime, self);
  
  stack[0].ival = is_precompile;
  
  return 0;
}

int32_t SPVM__Native__Method__is_enum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_enum = env->api->method->is_enum(runtime, self);
  
  stack[0].ival = is_enum;
  
  return 0;
}

int32_t SPVM__Native__Method__get_native_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* native_address = env->api->method->get_native_address(runtime, self);
  
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Address", native_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Native__Method__set_native_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_native_address = stack[1].oval;
  
  void* native_address = env->get_pointer(env, stack, obj_native_address);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_native_address(runtime, self, native_address);
  
  return 0;
}

int32_t SPVM__Native__Method__get_precompile_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* Precompile_address = env->api->method->get_precompile_address(runtime, self);
  
  void* obj_precompile_address = env->new_pointer_object_by_name(env, stack, "Address", Precompile_address, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_precompile_address;
  
  return 0;
}

int32_t SPVM__Native__Method__set_precompile_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_precompile_address = stack[1].oval;
  
  void* precompile_address = env->get_pointer(env, stack, obj_precompile_address);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_precompile_address(runtime, self, precompile_address);
  
  return 0;
}

int32_t SPVM__Native__Method__is_precompile_fallback(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_precompile = env->api->method->is_precompile_fallback(runtime, self);
  
  stack[0].ival = is_precompile;
  
  return 0;
}

int32_t SPVM__Native__Method__set_is_precompile_fallback(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t is_precompile_fallback = stack[1].ival;
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  env->api->method->set_is_precompile_fallback(runtime, self, is_precompile_fallback);
  
  return 0;
}

int32_t SPVM__Native__Method__get_args_signature(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = get_field_native_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* args_signature = env->api->method->get_args_signature(runtime, self);
  
  void* obj_args_signature = env->new_string_nolen(env, stack, args_signature);
  
  stack[0].oval = obj_args_signature;
  
  return 0;
}

