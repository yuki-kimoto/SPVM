// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Runtime.c";

int32_t SPVM__Runtime__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  env->api->runtime->free_object(runtime);
  
  return 0;
}

int32_t SPVM__Runtime__set_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_address = stack[3].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* method = env->api->runtime->get_method_by_name(runtime, basic_type, method_name);
  
  // Native address
  void* address = env->get_pointer(env, stack, obj_address);
  
  env->api->runtime->set_native_method_address(runtime, method, address);

  return 0;
}

int32_t SPVM__Runtime__get_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* method = env->api->runtime->get_method_by_name(runtime, basic_type, method_name);
  
  void* address = env->api->runtime->get_native_method_address(runtime, method);
  
  // Native address
  void* obj_address = env->new_pointer_object_by_name(env, stack, "Native::Address", address, &e, __func__, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Runtime__get_method_is_class_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* method = env->api->runtime->get_method_by_name(runtime, basic_type, method_name);
  
  int32_t is_class_method = env->api->runtime->get_method_is_class_method(runtime, method);
  
  stack[0].ival = is_class_method;
  
  return 0;
}


int32_t SPVM__Runtime__get_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_basic_type_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Basic type name
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* method = env->api->runtime->get_method_by_name(runtime, basic_type, method_name);
  
  void* address = env->api->runtime->get_precompile_method_address(runtime, method);
  
  // Native address
  void* obj_address = env->new_pointer_object_by_name(env, stack, "Native::Address", address, &e, __func__, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_address;
  
  return 0;
}

int32_t SPVM__Runtime__set_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_address = stack[3].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Method id
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* method = env->api->runtime->get_method_by_name(runtime, basic_type, method_name);
  
  // Native address
  void* address = env->get_pointer(env, stack, obj_address);
  
  env->api->runtime->set_precompile_method_address(runtime, method, address);

  return 0;
}

int32_t SPVM__Runtime__build_precompile_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  void* runtime = env->get_pointer(env, stack, obj_self);

  // New allocator
  void* allocator = env->api->allocator->new_object();
  
  // New string buffer
  void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

  void* precompile = env->api->precompile->new_object();
  
  env->api->precompile->set_runtime(precompile, runtime);
  
  env->api->precompile->build_source(precompile, string_buffer, basic_type_name);
  
  env->api->precompile->free_object(precompile);

  const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);
  
  // Free string buffer
  env->api->string_buffer->free_object(string_buffer);

  // Free allocator
  env->api->allocator->free_object(allocator);

  stack[0].oval = obj_precompile_source;
  
  return 0;
}

int32_t SPVM__Runtime__build_precompile_method_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);

  void* runtime = env->get_pointer(env, stack, obj_self);

  // New allocator
  void* allocator = env->api->allocator->new_object();
  
  // New string buffer
  void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

  void* precompile = env->api->precompile->new_object();
  
  env->api->precompile->set_runtime(precompile, runtime);
  
  env->api->precompile->build_method_source(precompile, string_buffer, basic_type_name, method_name);
  
  env->api->precompile->free_object(precompile);

  const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_method_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);

  // Free string buffer
  env->api->string_buffer->free_object(string_buffer);

  // Free allocator
  env->api->allocator->free_object(allocator);

  stack[0].oval = obj_precompile_method_source;
  
  return 0;
}

int32_t SPVM__Runtime__get_runtime_codes(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;

  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // SPVM 32bit codes
  int32_t* runtime_runtime_codes = env->api->runtime->get_runtime_codes(runtime);
  int32_t runtime_codes_length = env->api->runtime->get_runtime_codes_length(runtime);
  
  void* obj_runtime_codes = env->new_int_array(env, stack, runtime_codes_length);
  int32_t* runtime_codes = env->get_elems_int(env, stack, obj_runtime_codes);
  memcpy(runtime_codes, runtime_runtime_codes, sizeof(int32_t) * runtime_codes_length);
  
  stack[0].oval = obj_runtime_codes;
  
  return 0;
}

int32_t SPVM__Runtime__get_basic_type_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  int32_t basic_types_length = env->api->runtime->get_basic_types_length(runtime);
  
  void* obj_basic_type_names = env->new_string_array(env, stack, basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < basic_types_length; basic_type_id++) {
    void* basic_type = env->api->runtime->get_basic_type(runtime, basic_type_id);
    const char* basic_type_name = env->api->runtime->get_basic_type_name_v2(runtime, basic_type);
    void* obj_basic_type_name = env->new_string_nolen(env, stack, basic_type_name);
    env->set_elem_object(env, stack, obj_basic_type_names, basic_type_id, obj_basic_type_name);
  }
  
  stack[0].oval = obj_basic_type_names;
  
  return 0;
}

int32_t SPVM__Runtime__get_module_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  // Copy class load path to builder
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  const char* module_file;
  void* sv_module_file;

  void* obj_module_file = NULL;
  if (basic_type) {
    const char* module_dir = env->api->runtime->get_basic_type_module_dir_v2(runtime, basic_type);
    const char* module_dir_sep;
    if (module_dir) {
      module_dir_sep = "/";
    }
    else {
      module_dir_sep = "";
      module_dir = "";
    }
    const char* module_rel_file = env->api->runtime->get_basic_type_module_rel_file_v2(runtime, basic_type);
    
    int32_t module_file_length = strlen(module_dir) + strlen(module_dir_sep) + strlen(module_rel_file);
    obj_module_file = env->new_string(env, stack, NULL, module_file_length);
    char* module_file = (char*)env->get_chars(env, stack, obj_module_file);
    memcpy(module_file, module_dir, strlen(module_dir));
    memcpy(module_file + strlen(module_dir), module_dir_sep, strlen(module_dir_sep));
    memcpy(module_file + strlen(module_dir) + strlen(module_dir_sep), module_rel_file, strlen(module_rel_file));
  }
  
  stack[0].oval = obj_module_file;
  
  return 0;
}

int32_t SPVM__Runtime__get_basic_type_parent_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  void* parent_basic_type = env->api->runtime->get_basic_type_parent(runtime, basic_type);
  
  void* obj_parent_basic_type_name = NULL;
  if (parent_basic_type) {
    const char* parent_basic_type_name = env->api->runtime->get_basic_type_name_v2(runtime, parent_basic_type);
    obj_parent_basic_type_name = env->new_string_nolen(env, stack, parent_basic_type_name);
  }
  
  stack[0].oval = obj_parent_basic_type_name;
  
  return 0;
}

int32_t SPVM__Runtime__get_basic_type_anon_basic_type_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
 
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type);
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  int32_t methods_length = env->api->runtime->get_basic_type_methods_length_v2(runtime, basic_type);
  
  int32_t anon_basic_types_length = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env->api->runtime->get_method(runtime, basic_type, method_index);
    int32_t is_anon_method = env->api->runtime->get_method_is_anon(runtime, method);
    if (is_anon_method) {
      anon_basic_types_length++;
    }
  }
  
  void* obj_anon_basic_type_names = env->new_string_array(env, stack, anon_basic_types_length);
  int32_t anon_basic_type_id = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env->api->runtime->get_method(runtime, basic_type, method_index);
    int32_t is_anon_method = env->api->runtime->get_method_is_anon(runtime, method);
    if (is_anon_method) {
      void* anon_basic_type = env->api->runtime->get_method_current_basic_type(runtime, method);
      const char* anon_basic_type_name = env->api->runtime->get_basic_type_name_v2(runtime, anon_basic_type);
      void* obj_anon_basic_type_name = env->new_string_nolen(env, stack, anon_basic_type_name);
      env->set_elem_object(env, stack, obj_anon_basic_type_names, anon_basic_type_id, obj_anon_basic_type_name);
      anon_basic_type_id++;
    }
  }
  
  stack[0].oval = obj_anon_basic_type_names;
  
  return 0;
}

int32_t SPVM__Runtime___get_method_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_basic_type_name = stack[1].oval;
  const char* basic_type_name = env->get_chars(env, stack, obj_basic_type_name);
  int32_t native_flag = stack[2].ival;
  int32_t precompile_flag = stack[3].ival;
  int32_t enum_flag = stack[4].ival;
  
  void* runtime = env->get_pointer(env, stack, obj_self);
  
  void* basic_type = env->api->runtime->get_basic_type_by_name(runtime, basic_type_name);
  
  int32_t methods_length = env->api->runtime->get_basic_type_methods_length_v2(runtime, basic_type);
  
  int32_t match_methodes_length = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    void* method = env->api->runtime->get_method(runtime, basic_type, method_index);
    int32_t match = 0;
    if (native_flag) {
      if (env->api->runtime->get_method_is_native(runtime, method)) {
        match = 1;
      }
    }
    else if (precompile_flag) {
      if (env->api->runtime->get_method_is_precompile(runtime, method)) {
        match = 1;
      }
    }
    else if (enum_flag) {
      if (env->api->runtime->get_method_is_enum(runtime, method)) {
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
    void* method = env->api->runtime->get_method(runtime, basic_type, method_index);
    int32_t match = 0;
    if (native_flag) {
      if (env->api->runtime->get_method_is_native(runtime, method)) {
        match = 1;
      }
    }
    else if (precompile_flag) {
      if (env->api->runtime->get_method_is_precompile(runtime, method)) {
        match = 1;
      }
    }
    else if (enum_flag) {
      if (env->api->runtime->get_method_is_enum(runtime, method)) {
        match = 1;
      }
    }
    else {
      match = 1;
    }
    
    if (match) {
      const char* method_name = env->api->runtime->get_method_name(runtime, method);
      void* obj_method_name = env->new_string_nolen(env, stack, method_name);
      env->set_elem_object(env, stack, obj_method_names, match_method_index, obj_method_name);
      match_method_index++;
    }
  }
  
  stack[0].oval = obj_method_names;
  
  return 0;
}

int32_t SPVM__Runtime__build_env(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  void* obj_runtime = stack[0].oval;
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  SPVM_ENV* my_env = env->new_env_raw(env);
  
  // Set runtime information
  my_env->runtime = runtime;
  
  // Initialize env
  my_env->init_env(my_env);
  
  void* obj_self= env->new_pointer_object_by_name(env, stack, "Env", my_env, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  env->set_field_object_by_name(env, stack, obj_self, "runtime", obj_runtime, &e, __func__, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_self;
  
  return 0;
}

