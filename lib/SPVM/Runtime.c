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
  void* obj_method_name = stack[2].oval;
  void* obj_native_address = stack[3].oval;

  void* obj_native_runtime = env->get_field_object_by_name(env, stack, obj_self, "native_runtime", &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  void* runtime = env->get_pointer(env, stack, obj_native_runtime);
  
  // Class name
  const char* class_name = env->get_chars(env, stack, obj_class_name);

  // Method name
  const char* method_name = env->get_chars(env, stack, obj_method_name);
  
  // Method id
  int32_t method_id = env->api->runtime->get_method_id_by_name(runtime, class_name, method_name);
  
  // Native address
  void* native_address = env->get_pointer(env, stack, obj_native_address);
  
  env->api->runtime->set_precompile_method_address(runtime, method_id, native_address);

  return 0;
}

int32_t SPVM__Compiler__build_class_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return 0;
}

int32_t SPVM__Compiler__build_method_source(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
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

SV*
get_parent_class_name(...)
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
  int32_t parent_class_id = compiler_env->api->runtime->get_class_parent_class_id(runtime, class_id);
  
  SV* sv_parent_class_name = &PL_sv_undef;
  if (parent_class_id >= 0) {
    int32_t parent_class_name_id = compiler_env->api->runtime->get_class_name_id(runtime, parent_class_id);
    const char* parent_class_name = compiler_env->api->runtime->get_name(runtime, parent_class_name_id);
    sv_parent_class_name = sv_2mortal(newSVpv(parent_class_name, 0));
  }
  
  XPUSHs(sv_parent_class_name);
  XSRETURN(1);
}

SV*
get_anon_class_names_by_parent_class_name(...)
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
  
  // Runtime
  SV** sv_runtime_ptr = hv_fetch(hv_self, "runtime", strlen("runtime"), 0);
  SV* sv_runtime = sv_runtime_ptr ? *sv_runtime_ptr : &PL_sv_undef;
  void* runtime = INT2PTR(void*, SvIV(SvRV(sv_runtime)));

  AV* av_anon_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_anon_class_names = sv_2mortal(newRV_inc((SV*)av_anon_class_names));
  
  // Copy class load path to builder
  int32_t class_id = compiler_env->api->runtime->get_class_id_by_name(runtime, class_name);

  int32_t methods_length = compiler_env->api->runtime->get_class_methods_length(runtime, class_id);

  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    
    int32_t method_id = compiler_env->api->runtime->get_method_id_by_index(runtime, class_id, method_index);
    int32_t is_anon_method = compiler_env->api->runtime->get_method_is_anon(runtime, method_id);
    
    if (is_anon_method) {
      int32_t anon_class_id = compiler_env->api->runtime->get_method_class_id(runtime, method_id);
      const char* anon_class_name = compiler_env->api->runtime->get_name(runtime, compiler_env->api->runtime->get_class_name_id(runtime, anon_class_id));
      SV* sv_anon_class_name = sv_2mortal(newSVpv(anon_class_name, 0));
      av_push(av_anon_class_names, SvREFCNT_inc(sv_anon_class_name));
    }
  }
  
  XPUSHs(sv_anon_class_names);
  XSRETURN(1);
}

SV*
get_class_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  // The compiler_environment
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));

  // Runtime
  SV** sv_runtime_ptr = hv_fetch(hv_self, "runtime", strlen("runtime"), 0);
  SV* sv_runtime = sv_runtime_ptr ? *sv_runtime_ptr : &PL_sv_undef;
  void* runtime = INT2PTR(void*, SvIV(SvRV(sv_runtime)));

  AV* av_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_class_names = sv_2mortal(newRV_inc((SV*)av_class_names));
  
  int32_t classes_legnth = compiler_env->api->runtime->get_classes_length(runtime);
  for (int32_t class_id = 0; class_id < classes_legnth; class_id++) {
    const char* class_name = compiler_env->api->runtime->get_name(runtime, compiler_env->api->runtime->get_class_name_id(runtime, class_id));
    SV* sv_class_name = sv_2mortal(newSVpv(class_name, 0));
    av_push(av_class_names, SvREFCNT_inc(sv_class_name));
  }
  
  XPUSHs(sv_class_names);
  XSRETURN(1);
}

SV*
get_module_file(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);
  
  // Env
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(void*, SvIV(SvRV(sv_compiler_env)));

  // Runtime
  SV** sv_runtime_ptr = hv_fetch(hv_self, "runtime", strlen("runtime"), 0);
  SV* sv_runtime = sv_runtime_ptr ? *sv_runtime_ptr : &PL_sv_undef;
  void* runtime = INT2PTR(void*, SvIV(SvRV(sv_runtime)));

  // Copy class load path to builder
  int32_t class_id = compiler_env->api->runtime->get_class_id_by_name(runtime, class_name);
  const char* module_file;
  SV* sv_module_file;

  if (class_id >= 0) {
    int32_t module_rel_file_id = compiler_env->api->runtime->get_class_module_rel_file_id(runtime, class_id);
    int32_t module_dir_id = compiler_env->api->runtime->get_class_module_dir_id(runtime, class_id);
    const char* module_dir = NULL;
    const char* module_dir_sep;
    if (module_dir_id >= 0) {
      module_dir_sep = "/";
      module_dir = compiler_env->api->runtime->get_constant_string_value(runtime, module_dir_id, NULL);
    }
    else {
      module_dir_sep = "";
      module_dir = "";
    }
    const char* module_rel_file = compiler_env->api->runtime->get_constant_string_value(runtime, module_rel_file_id, NULL);

    sv_module_file = sv_2mortal(newSVpv(module_dir, 0));
    sv_catpv(sv_module_file, module_dir_sep);
    sv_catpv(sv_module_file, module_rel_file);
  }
  else {
    sv_module_file = &PL_sv_undef;
  }
  
  XPUSHs(sv_module_file);
  XSRETURN(1);
}

*/
