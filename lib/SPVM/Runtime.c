#include "spvm_native.h"

#include <assert.h>

static const char* FILE_NAME = "Runtime.c";

int32_t SPVM__Runtime__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  env->api->runtime->free_object(runtime);
  
  return 0;
}

int32_t SPVM__Compiler__get_native_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_class_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  void* native_address = env->api->runtime->get_native_method_address(runtime, method_id);
  
  // Native address
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Native::Address", native_address, &e, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Compiler__get_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;
  void* obj_class_name = stack[1].oval;
  void* obj_method_name = stack[2].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  void* native_address = env->api->runtime->get_precompile_method_address(runtime, method_id);
  
  // Native address
  void* obj_native_address = env->new_pointer_object_by_name(env, stack, "Native::Address", native_address, &e, FILE_NAME, __LINE__);
  
  stack[0].oval = obj_native_address;
  
  return 0;
}

int32_t SPVM__Compiler__set_precompile_method_address(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  void* obj_native_address = stack[3].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  // Native address
  void* native_address = env->get_pointer(env, stack, obj_native_address);
  
  env->api->runtime->set_precompile_method_address(runtime, method_id, native_address);

  return 0;
}

int32_t SPVM__Compiler__build_precompile_class_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);

  // New allocator
  void* allocator = env->api->allocator->new_object();
  
  // New string buffer
  void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

  void* precompile = env->api->precompile->new_object();
  
  env->api->precompile->set_runtime(precompile, runtime);
  
  env->api->precompile->build_class_source(precompile, string_buffer, class_name);
  
  env->api->precompile->free_object(precompile);

  const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_class_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);

  // Free string buffer
  env->api->string_buffer->free_object(string_buffer);

  // Free allocator
  env->api->allocator->free_object(allocator);

  // Free env
  env->free_env_raw(env);
  
  stack[0].oval = obj_precompile_class_source;
  
  return 0;
}

int32_t SPVM__Compiler__build_precompile_method_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;

  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  void* obj_method_name = stack[2].oval;
  const char* method_name = env->get_chars(env, stack, obj_method_name);

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);

  // New allocator
  void* allocator = env->api->allocator->new_object();
  
  // New string buffer
  void* string_buffer = env->api->string_buffer->new_object(allocator, 0);

  void* precompile = env->api->precompile->new_object();
  
  env->api->precompile->set_runtime(precompile, runtime);
  
  env->api->precompile->build_method_source(precompile, string_buffer, class_name, method_name);
  
  env->api->precompile->free_object(precompile);

  const char* string_buffer_value = env->api->string_buffer->get_value(string_buffer);
  int32_t string_buffer_length = env->api->string_buffer->get_length(string_buffer);
  void* obj_precompile_method_source = env->new_string(env, stack, string_buffer_value, string_buffer_length);

  // Free string buffer
  env->api->string_buffer->free_object(string_buffer);

  // Free allocator
  env->api->allocator->free_object(allocator);

  // Free env
  env->free_env_raw(env);
  
  stack[0].oval = obj_precompile_method_source;
  
  return 0;
}

int32_t SPVM__Compiler__call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  my_env->call_init_blocks(my_env);
  
  return 0;
}

int32_t SPVM__Compiler__set_command_info(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* obj_my_env = stack[0].oval;
  SPVM_ENV* my_env = env->get_pointer(env, stack, obj_my_env);
  
  void* obj_program_name = stack[1].oval;
  
  void* obj_argv = stack[2].oval;

  e = my_env->set_command_info_program_name(my_env, obj_program_name);
  if (e) { return e; }
  
  e = my_env->set_command_info_argv(my_env, obj_argv);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM__Compiler__call_method(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__get_spvm_32bit_codes(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // SPVM 32bit codes
  int32_t* runtime_spvm_32bit_codes = env->api->runtime->get_spvm_32bit_codes(runtime);
  int32_t spvm_32bit_codes_length = env->api->runtime->get_spvm_32bit_codes_length(runtime);
  
  void* obj_spvm_32bit_codes = env->new_int_array(env, stack, spvm_32bit_codes_length);
  int32_t* spvm_32bit_codes = env->get_elems_int(env, stack, obj_spvm_32bit_codes);
  memcpy(spvm_32bit_codes, runtime_spvm_32bit_codes, sizeof(int32_t) * spvm_32bit_codes_length);
  
  stack[0].oval = obj_spvm_32bit_codes;
  
  return 0;
}

int32_t SPVM__Compiler__get_classes_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  int32_t classes_length = env->api->runtime->get_classes_length(runtime);
  
  stack[0].ival = classes_length;
  
  return 0;
}

int32_t SPVM__Compiler__get_class_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  int32_t classes_length = env->api->runtime->get_classes_length(runtime);
  
  void* obj_class_names = env->new_string_array(env, stack, classes_length);
  for (int32_t class_id = 0; class_id < classes_length; class_id++) {
    const char* class_name = env->api->runtime->get_name(runtime, env->api->runtime->get_class_name_id(runtime, class_id));
    void* obj_class_name = env->new_string_nolen(env, stack, class_name);
    env->set_elem_object(env, stack, obj_class_names, class_id, obj_class_name);
  }
  
  stack[0].oval = obj_class_names;
  
  return 0;
}


int32_t SPVM__Compiler__get_module_file(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Copy class load path to builder
  int32_t class_id = env->api->runtime->get_class_id_by_name(runtime, class_name);
  const char* module_file;
  void* sv_module_file;

  void* obj_module_file = NULL;
  if (class_id >= 0) {
    int32_t module_rel_file_id = env->api->runtime->get_class_module_rel_file_id(runtime, class_id);
    int32_t module_dir_id = env->api->runtime->get_class_module_dir_id(runtime, class_id);
    const char* module_dir = NULL;
    const char* module_dir_sep;
    if (module_dir_id >= 0) {
      module_dir_sep = "/";
      module_dir = env->api->runtime->get_constant_string_value(runtime, module_dir_id, NULL);
    }
    else {
      module_dir_sep = "";
      module_dir = "";
    }
    const char* module_rel_file = env->api->runtime->get_constant_string_value(runtime, module_rel_file_id, NULL);
    
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

int32_t SPVM__Compiler__get_parent_class_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;
  
  void* obj_self = stack[0].oval;
  
  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);
  
  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  int32_t class_id = env->api->runtime->get_class_id_by_name(runtime, class_name);
  int32_t parent_class_id = env->api->runtime->get_class_parent_class_id(runtime, class_id);
  
  void* obj_parent_class_name = NULL;
  if (parent_class_id >= 0) {
    int32_t parent_class_name_id = env->api->runtime->get_class_name_id(runtime, parent_class_id);
    const char* parent_class_name = env->api->runtime->get_name(runtime, parent_class_name_id);
    obj_parent_class_name = env->new_string_nolen(env, stack, parent_class_name);
  }
  
  stack[0].oval = obj_parent_class_name;
  
  return 0;
}

int32_t SPVM__Compiler__get_anon_class_names(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e = 0;

  void* obj_self = stack[0].oval;

  void* obj_class_name = stack[1].oval;
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  int32_t class_id = env->api->runtime->get_class_id_by_name(runtime, class_name);

  int32_t methods_length = env->api->runtime->get_class_methods_length(runtime, class_id);
  
  int32_t anon_classes_length = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    int32_t method_id = env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    int32_t is_anon_method = env->api->runtime->get_method_is_anon(runtime, method_id);
    if (is_anon_method) {
      anon_classes_length++;
    }
  }
  
  void* obj_anon_class_names = env->new_string_array(env, stack, anon_classes_length);
  int32_t anon_class_index = 0;
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    int32_t method_id = env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    int32_t is_anon_method = env->api->runtime->get_method_is_anon(runtime, method_id);
    if (is_anon_method) {
      int32_t anon_class_id = env->api->runtime->get_method_class_id(runtime, method_id);
      const char* anon_class_name = env->api->runtime->get_name(runtime, env->api->runtime->get_class_name_id(runtime, anon_class_id));
      void* obj_anon_class_name = env->new_string_nolen(env, stack, anon_class_name);
      env->set_elem_object(env, stack, obj_anon_class_names, anon_class_index, obj_anon_class_name);
      anon_class_index++;
    }
  }
  
  stack[0].oval = obj_anon_class_names;
  
  return 0;
}

/*
SV*
get_method_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_category = ST(2);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  // The compiler_environment
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  AV* av_method_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_method_names = sv_2mortal(newRV_inc((SV*)av_method_names));
  
  // Runtime
  SV** sv_runtime_ptr = hv_fetch(hv_self, "runtime", strlen("runtime"), 0);
  SV* sv_runtime = sv_runtime_ptr ? *sv_runtime_ptr : &PL_sv_undef;
  void* runtime = INT2PTR(void*, SvIV(SvRV(sv_runtime)));
  
  int32_t class_id = compiler_env->api->runtime->get_class_id_by_name(runtime, class_name);
  int32_t methods_length = compiler_env->api->runtime->get_class_methods_length(runtime, class_id);
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    int32_t method_id = compiler_env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    const char* method_name = compiler_env->api->runtime->get_name(runtime, compiler_env->api->runtime->get_method_name_id(runtime, method_id));
    SV* sv_method_name = sv_2mortal(newSVpv(method_name, 0));
    int32_t is_push = 0;
    if (SvOK(sv_category)) {
      if(strEQ(SvPV_nolen(sv_category), "native") && compiler_env->api->runtime->get_method_is_native(runtime, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
      else if (strEQ(SvPV_nolen(sv_category), "precompile") && compiler_env->api->runtime->get_method_is_precompile(runtime, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
    }
    else {
      av_push(av_method_names, SvREFCNT_inc(sv_method_name));
    }
  }
  
  XPUSHs(sv_method_names);
  XSRETURN(1);
}

*/
