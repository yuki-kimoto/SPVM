// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Native::Runtime.c";

int32_t SPVM__Native__Runtime__build_precompile_class_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type = stack[1].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->get_pointer(env, stack, obj_basic_type);
  
  void* allocator = env->api->allocator->new_instance();
  
  void* string_buffer = env->api->string_buffer->new_instance(allocator, 0);
  
  env->api->runtime->build_precompile_class_source(self, string_buffer, basic_type);
  
  const char* string_buffer_value = env->api->string_buffer->get_string(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);
  
  env->api->string_buffer->free_instance(string_buffer);
  
  env->api->allocator->free_instance(allocator);
  
  stack[0].oval = obj_precompile_source;
  
  return 0;
}

int32_t SPVM__Native__Runtime__build_precompile_method_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_method = stack[1].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* method = env->get_pointer(env, stack, obj_method);
  
  void* allocator = env->api->allocator->new_instance();
  
  void* string_buffer = env->api->string_buffer->new_instance(allocator, 0);
  
  env->api->runtime->build_precompile_method_source(self, string_buffer, method);
  
  const char* string_buffer_value = env->api->string_buffer->get_string(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_method_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);
  
  env->api->string_buffer->free_instance(string_buffer);
  
  env->api->allocator->free_instance(allocator);
  
  stack[0].oval = obj_precompile_method_source;
  
  return 0;
}

int32_t SPVM__Native__Runtime__set_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_address = stack[3].oval;

  void* self = env->get_pointer(env, stack, obj_self);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(self, basic_type, method_name);
  
  // Native address
  void* address = env->get_pointer(env, stack, obj_address);
  
  env->api->method->set_native_address(self, method, address);

  return 0;
}

int32_t SPVM__Native__Runtime__get_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* self = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(self, basic_type, method_name);
  
  void* address = env->api->method->get_native_address(self, method);
  
  // Native address
  void* obj_address = env->new_pointer_object_by_name(env, stack, "Native::Address", address, &error_id, __func__, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Native__Runtime__get_method_is_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* self = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(self, basic_type, method_name);
  
  int32_t is_class_method = env->api->method->is_class_method(self, method);
  
  stack[0].ival = is_class_method;
  
  return 0;
}


int32_t SPVM__Native__Runtime__get_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* self = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(self, basic_type, method_name);
  
  void* address = env->api->method->get_precompile_address(self, method);
  
  // Native address
  void* obj_address = env->new_pointer_object_by_name(env, stack, "Native::Address", address, &error_id, __func__, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Native__Runtime__set_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_address = stack[3].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* method = env->api->basic_type->get_method_by_name(self, basic_type, method_name);
  
  // Native address
  void* address = env->get_pointer(env, stack, obj_address);
  
  env->api->method->set_precompile_address(self, method, address);

  return 0;
}

int32_t SPVM__Native__Runtime__get_basic_types_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t basic_types_length = env->api->runtime->get_basic_types_length(self);
  
  stack[0].ival = basic_types_length;
  
  return 0;
}

int32_t SPVM__Native__Runtime__get_basic_type_by_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  int32_t index = stack[1].ival;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_id(self, index);
  
  if (!basic_type) {
    return env->die_v2(env, stack, "The basic type cannot be found.", __func__, FILE_NAME, __LINE__);
  }
  
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

int32_t SPVM__Native__Runtime__get_basic_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_name = stack[1].oval;
  
  if (!obj_name) {
    return env->die_v2(env, stack, "The basic type cannot be found.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* name = env->get_chars(env, stack, obj_name);
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, name);
  
  if (!basic_type) {
    return env->die_v2(env, stack, "The basic type cannot be found.", __func__, FILE_NAME, __LINE__);
  }
  
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

int32_t SPVM__Native__Runtime__get_basic_type_parent_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  void* parent_basic_type = env->api->basic_type->get_parent(self, basic_type);
  
  void* obj_parent_basic_type_name = NULL;
  if (parent_basic_type) {
    const char* parent_basic_type_name = env->api->basic_type->get_name(self, parent_basic_type);
    obj_parent_basic_type_name = env->new_string_nolen(env, stack, parent_basic_type_name);
  }
  
  stack[0].oval = obj_parent_basic_type_name;
  
  return 0;
}

int32_t SPVM__Native__Runtime___get_method_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  int32_t native_flag = stack[2].ival;
  int32_t precompile_flag = stack[3].ival;
  int32_t enum_flag = stack[4].ival;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(self, basic_type_name);
  
  int32_t methods_length = env->api->basic_type->get_methods_length(self, basic_type);
  
  int32_t match_methodes_length = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env->api->basic_type->get_method_by_index(self, basic_type, method_index);
    int32_t match = 0;
    if (native_flag) {
      if (env->api->method->is_native(self, method)) {
        match = 1;
      }
    }
    else if (precompile_flag) {
      if (env->api->method->is_precompile(self, method)) {
        match = 1;
      }
    }
    else if (enum_flag) {
      if (env->api->method->is_enum(self, method)) {
        match = 1;
      }
    }
    else {
      match = 1;
    }

    if (match) {
      match_methodes_length++;
    }
  }
  
  void* obj_method_names = env->new_string_array(env, stack, match_methodes_length);
  int32_t match_method_index = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env->api->basic_type->get_method_by_index(self, basic_type, method_index);
    int32_t match = 0;
    if (native_flag) {
      if (env->api->method->is_native(self, method)) {
        match = 1;
      }
    }
    else if (precompile_flag) {
      if (env->api->method->is_precompile(self, method)) {
        match = 1;
      }
    }
    else if (enum_flag) {
      if (env->api->method->is_enum(self, method)) {
        match = 1;
      }
    }
    else {
      match = 1;
    }
    
    if (match) {
      const char* method_name = env->api->method->get_name(self, method);
      void* obj_method_name = env->new_string_nolen(env, stack, method_name);
      env->set_elem_object(env, stack, obj_method_names, match_method_index, obj_method_name);
      match_method_index++;
    }
  }
  
  stack[0].oval = obj_method_names;
  
  return 0;
}

int32_t SPVM__Native__Runtime__get_compiler(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type = stack[1].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_compiler = env->get_field_object_by_name(env, stack, obj_self, "compiler", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_compiler;
  
  return 0;
}

