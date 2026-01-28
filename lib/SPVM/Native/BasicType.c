// Copyright (c) 2023 Yuki Kimot
// MIT License

#include <assert.h>
#include "spvm_native.h"


static const char* FILE_NAME = "Native/BasicType.c";

int32_t SPVM__Native__BasicType__get_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t id = env->api->basic_type->get_id(runtime, self);
  
  stack[0].ival = id;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* name = env->api->basic_type->get_name(runtime, self);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* class_dir = env->api->basic_type->get_class_dir(runtime, self);
  
  void* obj_class_dir = NULL;
  if (class_dir) {
    obj_class_dir = env->new_string_nolen(env, stack, class_dir);
  }
  
  stack[0].oval = obj_class_dir;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_rel_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* class_rel_file = env->api->basic_type->get_class_rel_file(runtime, self);
  
  void* obj_class_rel_file = NULL;
  if (class_rel_file) {
    obj_class_rel_file = env->new_string_nolen(env, stack, class_rel_file);
  }
  
  stack[0].oval = obj_class_rel_file;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_parent(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* parent = env->api->basic_type->get_parent(runtime, self);
  
  void* obj_parent = NULL;
  if (parent) {
    void* obj_address_parent = env->new_pointer_object_by_name(env, stack, "Address", parent, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    stack[0].oval = obj_address_parent;
    env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    obj_parent = stack[0].oval;
    env->set_no_free(env, stack, obj_parent, 1);
    
    env->set_field_object_by_name(env, stack, obj_parent, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].oval = obj_parent;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_category(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t category = env->api->basic_type->get_category(runtime, self);
  
  stack[0].ival = category;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  const char* version_string = env->api->basic_type->get_version_string(runtime, self);
  
  void* obj_version_string = NULL;
  
  if (version_string) {
    obj_version_string = env->new_string_nolen(env, stack, version_string);
  }
  
  stack[0].oval = obj_version_string;
  
  return 0;
}

int32_t SPVM__Native__BasicType__is_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_pointer = env->api->basic_type->is_pointer(runtime, self);
  
  stack[0].ival = is_pointer;
  
  return 0;
}


int32_t SPVM__Native__BasicType__is_anon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t is_anon = env->api->basic_type->is_anon(runtime, self);
  
  stack[0].ival = is_anon;
  
  return 0;
}


int32_t SPVM__Native__BasicType__get_class_var_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t class_var_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* class_var = env->api->basic_type->get_class_var_by_index(runtime, self, class_var_index);
  if (!class_var) {
    return env->die_v2(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_class_var = env->new_pointer_object_by_name(env, stack, "Address", class_var, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_class_var;
  env->call_class_method_by_name(env, stack, "Native::ClassVar", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_class_var = stack[0].oval;
  env->set_no_free(env, stack, obj_class_var, 1);
  
  env->set_field_object_by_name(env, stack, obj_class_var, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_class_var;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_var_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_class_var_name = stack[1].oval;
  
  if (!obj_class_var_name) {
    return env->die_v2(env, stack, "The class variable name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* class_var_name = env->get_chars(env, stack, obj_class_var_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* class_var = env->api->basic_type->get_class_var_by_name(runtime, self, class_var_name);
  if (!class_var) {
    return env->die_v2(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_class_var = env->new_pointer_object_by_name(env, stack, "Address", class_var, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_class_var;
  env->call_class_method_by_name(env, stack, "Native::ClassVar", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_class_var = stack[0].oval;
  env->set_no_free(env, stack, obj_class_var, 1);
  
  env->set_field_object_by_name(env, stack, obj_class_var, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_class_var;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_vars_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t class_vars_length = env->api->basic_type->get_class_vars_length(runtime, self);
  
  stack[0].ival = class_vars_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_field_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t field_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* field = env->api->basic_type->get_field_by_index(runtime, self, field_index);
  if (!field) {
    return env->die_v2(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_field = env->new_pointer_object_by_name(env, stack, "Address", field, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_field;
  env->call_class_method_by_name(env, stack, "Native::Field", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_field = stack[0].oval;
  env->set_no_free(env, stack, obj_field, 1);
  
  env->set_field_object_by_name(env, stack, obj_field, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_field;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_field_name = stack[1].oval;
  
  if (!obj_field_name) {
    return env->die_v2(env, stack, "The field name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* field_name = env->get_chars(env, stack, obj_field_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* field = env->api->basic_type->get_field_by_name(runtime, self, field_name);
  if (!field) {
    return env->die_v2(env, stack, "The field is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_field = env->new_pointer_object_by_name(env, stack, "Address", field, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_field;
  env->call_class_method_by_name(env, stack, "Native::Field", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_field = stack[0].oval;
  env->set_no_free(env, stack, obj_field, 1);
  
  env->set_field_object_by_name(env, stack, obj_field, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_field;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_fields_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_fields_length = env->api->basic_type->get_fields_length(runtime, self);
  
  stack[0].ival = get_fields_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_method_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t method_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* method = env->api->basic_type->get_method_by_index(runtime, self, method_index);
  if (!method) {
    return env->die_v2(env, stack, "The method is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_method = env->new_pointer_object_by_name(env, stack, "Address", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_method;
  env->call_class_method_by_name(env, stack, "Native::Method", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_method = stack[0].oval;
  env->set_no_free(env, stack, obj_method, 1);
  
  env->set_field_object_by_name(env, stack, obj_method, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_method;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die_v2(env, stack, "The method name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* method = env->api->basic_type->get_method_by_name(runtime, self, method_name);
  if (!method) {
    return env->die_v2(env, stack, "The method is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_method = env->new_pointer_object_by_name(env, stack, "Address", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_method;
  env->call_class_method_by_name(env, stack, "Native::Method", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_method = stack[0].oval;
  env->set_no_free(env, stack, obj_method, 1);
  
  env->set_field_object_by_name(env, stack, obj_method, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_method;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_methods_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t get_methods_length = env->api->basic_type->get_methods_length(runtime, self);
  
  stack[0].ival = get_methods_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_anon_basic_type_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  int32_t anon_basic_type_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* anon_basic_type = env->api->basic_type->get_anon_basic_type_by_index(runtime, self, anon_basic_type_index);
  if (!anon_basic_type) {
    return env->die_v2(env, stack, "The basic type is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_address_anon_basic_type = env->new_pointer_object_by_name(env, stack, "Address", anon_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  stack[0].oval = obj_address_anon_basic_type;
  env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  void* obj_anon_basic_type = stack[0].oval;
  env->set_no_free(env, stack, obj_anon_basic_type, 1);
  
  env->set_field_object_by_name(env, stack, obj_anon_basic_type, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_anon_basic_type;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_anon_basic_types_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  int32_t anon_basic_types_length = env->api->basic_type->get_anon_basic_types_length(runtime, self);
  
  stack[0].ival = anon_basic_types_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_basic_type_in_version_from(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* self = env->get_pointer(env, stack, obj_self);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  void* basic_type_in_version_from = env->api->basic_type->get_basic_type_in_version_from(runtime, self);
  
  void* obj_basic_type_in_version_from = NULL;
  if (basic_type_in_version_from) {
    void* obj_address_basic_type_in_version_from = env->new_pointer_object_by_name(env, stack, "Address", basic_type_in_version_from, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    stack[0].oval = obj_address_basic_type_in_version_from;
    env->call_class_method_by_name(env, stack, "Native::BasicType", "new_with_pointer", 1, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    obj_basic_type_in_version_from = stack[0].oval;
    env->set_no_free(env, stack, obj_basic_type_in_version_from, 1);
    
    env->set_field_object_by_name(env, stack, obj_basic_type_in_version_from, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].oval = obj_basic_type_in_version_from;
  
  return 0;
}

