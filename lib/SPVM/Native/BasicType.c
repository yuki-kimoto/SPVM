// Copyright (c) 2023 Yuki Kimot
// MIT License

#include <assert.h>
#include "spvm_native.h"


static const char* FILE_NAME = "Native/BasicType.c";

static void* get_field_native_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line) {
  
  *error_id = 0;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, object, field_name, error_id, func_name, file_name, line);
  if (error_id) { return NULL; }
  
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

int32_t SPVM__Native__BasicType__get_id(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t id = env->api->basic_type->get_id(runtime, basic_type);
  
  stack[0].ival = id;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* name = env->api->basic_type->get_name(runtime, basic_type);
  
  void* obj_name = env->new_string_nolen(env, stack, name);
  
  stack[0].oval = obj_name;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_module_dir(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_dir = env->api->basic_type->get_module_dir(runtime, basic_type);
  
  void* obj_module_dir = NULL;
  if (module_dir) {
    obj_module_dir = env->new_string_nolen(env, stack, module_dir);
  }
  
  stack[0].oval = obj_module_dir;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_module_rel_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* module_rel_file = env->api->basic_type->get_module_rel_file(runtime, basic_type);
  
  void* obj_module_rel_file = NULL;
  if (module_rel_file) {
    obj_module_rel_file = env->new_string_nolen(env, stack, module_rel_file);
  }
  
  stack[0].oval = obj_module_rel_file;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_parent(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* parent = env->api->basic_type->get_parent(runtime, basic_type);
  
  void* obj_parent = NULL;
  if (parent) {
    void* obj_parent = env->new_pointer_object_by_name(env, stack, "Native::BasicType", parent, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
    
    env->set_field_object_by_name(env, stack, obj_parent, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
    if (error_id) { return error_id; }
  }
  
  stack[0].oval = obj_parent;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_category(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t category = env->api->basic_type->get_category(runtime, basic_type);
  
  stack[0].ival = category;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* version_string = env->api->basic_type->get_version_string(runtime, basic_type);
  
  void* obj_version_string = env->new_string_nolen(env, stack, version_string);
  
  stack[0].oval = obj_version_string;
  
  return 0;
}


int32_t SPVM__Native__BasicType__is_pointer(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t is_pointer = env->api->basic_type->is_pointer(runtime, basic_type);
  
  stack[0].ival = is_pointer;
  
  return 0;
}


int32_t SPVM__Native__BasicType__is_anon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t is_anon = env->api->basic_type->is_anon(runtime, basic_type);
  
  stack[0].ival = is_anon;
  
  return 0;
}


int32_t SPVM__Native__BasicType__get_class_var_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t class_var_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* class_var = env->api->basic_type->get_class_var_by_index(runtime, basic_type, class_var_index);
  if (!class_var) {
    return env->die(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_class_var = env->new_pointer_object_by_name(env, stack, "Native::ClassVar", class_var, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_class_var, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_class_var;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_var_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_class_var_name = stack[1].oval;
  
  if (!obj_class_var_name) {
    return env->die(env, stack, "The class variable name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* class_var_name = env->get_chars(env, stack, obj_class_var_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* class_var = env->api->basic_type->get_class_var_by_name(runtime, basic_type, class_var_name);
  if (!class_var) {
    return env->die(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_class_var = env->new_pointer_object_by_name(env, stack, "Native::ClassVar", class_var, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_class_var, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_class_var;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_class_vars_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t class_vars_length = env->api->basic_type->get_class_vars_length(runtime, basic_type);
  
  stack[0].ival = class_vars_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_field_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t field_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* field = env->api->basic_type->get_field_by_index(runtime, basic_type, field_index);
  if (!field) {
    return env->die(env, stack, "The class variable is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_field = env->new_pointer_object_by_name(env, stack, "Native::Field", field, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_field, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_field;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_field_name = stack[1].oval;
  
  if (!obj_field_name) {
    return env->die(env, stack, "The field name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* field_name = env->get_chars(env, stack, obj_field_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* field = env->api->basic_type->get_field_by_name(runtime, basic_type, field_name);
  if (!field) {
    return env->die(env, stack, "The field is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_field = env->new_pointer_object_by_name(env, stack, "Native::Field", field, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_field, "runtime", obj_self, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_field;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_fields_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t get_fields_length = env->api->basic_type->get_fields_length(runtime, basic_type);
  
  stack[0].ival = get_fields_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_method_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t method_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* method = env->api->basic_type->get_method_by_index(runtime, basic_type, method_index);
  if (!method) {
    return env->die(env, stack, "The method is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_method;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method_name = stack[1].oval;
  
  if (!obj_method_name) {
    return env->die(env, stack, "The method name must be specified.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* method = env->api->basic_type->get_method_by_name(runtime, basic_type, method_name);
  if (!method) {
    return env->die(env, stack, "The method is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_method = env->new_pointer_object_by_name(env, stack, "Native::Method", method, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_method, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_method;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_methods_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t get_methods_length = env->api->basic_type->get_methods_length(runtime, basic_type);
  
  stack[0].ival = get_methods_length;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_anon_basic_type_by_index(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic_type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t anon_basic_type_index = stack[1].ival;
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* anon_basic_type = env->api->basic_type->get_anon_basic_type_by_index(runtime, basic_type, anon_basic_type_index);
  if (!anon_basic_type) {
    return env->die(env, stack, "The basic type is not found.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_anon_basic_type = env->new_pointer_object_by_name(env, stack, "Native::BasicType", anon_basic_type, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  env->set_field_object_by_name(env, stack, obj_anon_basic_type, "runtime", obj_runtime, &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  stack[0].oval = obj_anon_basic_type;
  
  return 0;
}

int32_t SPVM__Native__BasicType__get_anon_basic_types_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_id = 0;
  
  void* obj_self = stack[0].oval;
  
  void* basic_type = env->get_pointer(env, stack, obj_self);
  
  if (!basic_type) {
    return env->die(env, stack, "The basic type was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  void* obj_runtime = env->get_field_object_by_name(env, stack, obj_self, "runtime", &error_id, __func__, FILE_NAME, __LINE__);
  if (error_id) { return error_id; }
  
  void* runtime = env->get_pointer(env, stack, obj_runtime);
  
  if (!runtime) {
    return env->die(env, stack, "The runtime was already destroyed.", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t anon_basic_types_length = env->api->basic_type->get_anon_basic_types_length(runtime, basic_type);
  
  stack[0].ival = anon_basic_types_length;
  
  return 0;
}

