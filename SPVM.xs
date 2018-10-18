#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_my.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"
#include "spvm_object.h"
#include "spvm_native.h"
#include "spvm_opcode_builder.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_list.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_string_buffer.h"
#include "spvm_use.h"
#include "spvm_limit.h"
#include "spvm_portable.h"

#include "spvm_runtime_sub.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"

#include "spvm_portable.h"
#include "spvm_csource_builder_exe.h"

SV* SPVM_XS_UTIL_new_sv_object(SPVM_ENV* env, SPVM_OBJECT* object, const char* package) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  (void)hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));

  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  (void)hv_store(hv_data, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  HV* hv_class = gv_stashpv(package, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

SPVM_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = (HV*)SvRV(sv_data);
    
    SV** sv_object_ptr = hv_fetch(hv_data, "object", strlen("object"), 0);
    SV* sv_object = sv_object_ptr ? *sv_object_ptr : &PL_sv_undef;
    size_t iv_object = SvIV(SvRV(sv_object));
    SPVM_OBJECT* object = INT2PTR(SPVM_OBJECT*, iv_object);
    
    return object;
  }
  else {
    return NULL;
  }
}

SV* SPVM_XS_UTIL_create_sv_type_name(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension) {
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  const char* basic_type_name = runtime->symbols[basic_type->id];
  assert(basic_type);

  SV* sv_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sv_catpv(sv_type_name, "[]");
  }
  
  return sv_type_name;
}

MODULE = SPVM::Data		PACKAGE = SPVM::Data

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);

  assert(SvOK(sv_object));

  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(sv_object);

  SV** sv_env_ptr = hv_fetch(hv_object, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  assert(env->get_ref_count(env, object));
  
  // Decrement reference count
  env->dec_ref_count(env, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Builder		PACKAGE = SPVM::Builder

SV*
compile_spvm(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  SV** sv_package_infos_ptr = hv_fetch(hv_self, "package_infos", strlen("package_infos"), 0);
  SV* sv_package_infos = sv_package_infos_ptr ? *sv_package_infos_ptr : &PL_sv_undef;
  AV* av_package_infos = (AV*)SvRV(sv_package_infos);
  
  int32_t av_package_infos_length = (int32_t)av_len(av_package_infos) + 1;
  
  {
    int32_t i;
    for (i = 0; i < av_package_infos_length; i++) {
      SV** sv_package_info_ptr = av_fetch(av_package_infos, i, 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Name
      SV** sv_name_ptr = hv_fetch(hv_package_info, "name", strlen("name"), 0);
      SV* sv_name = sv_name_ptr ? *sv_name_ptr : &PL_sv_undef;
      const char* name = SvPV_nolen(sv_name);
      
      // File
      SV** sv_file_ptr = hv_fetch(hv_package_info, "file", strlen("file"), 0);
      SV* sv_file = sv_file_ptr ? *sv_file_ptr : &PL_sv_undef;
      const char* file = SvPV_nolen(sv_file);
      
      // Line
      SV** sv_line_ptr = hv_fetch(hv_package_info, "line", strlen("line"), 0);
      SV* sv_line = sv_line_ptr ? *sv_line_ptr : &PL_sv_undef;
      int32_t line = (int32_t)SvIV(sv_line);
      
      // push package to compiler use stack
      SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, name, file, line);
      SPVM_OP* op_type_package = SPVM_OP_build_basic_type(compiler, op_name_package);
      SPVM_OP* op_use_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file, line);
      SPVM_OP_build_use(compiler, op_use_package, op_type_package);
      SPVM_LIST_push(compiler->op_use_stack, op_use_package);
    }
  }
  
  // Add include paths
  AV* av_include_paths = get_av("main::INC", 0);;
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  {
    int32_t i;
    for (i = 0; i < av_include_paths_length; i++) {
      SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
      SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
      char* include_path = SvPV_nolen(sv_include_path);
      SPVM_LIST_push(compiler->module_include_pathes, include_path);
    }
  }

  // Compile SPVM
  SPVM_COMPILER_compile(compiler);
  SV* sv_compile_success;
  
  if (compiler->error_count > 0) {
    sv_compile_success = sv_2mortal(newSViv(0));
  }
  else {
    sv_compile_success = sv_2mortal(newSViv(1));
  }
  
  if (compiler->error_count == 0) {
    // Copy package load path to builder
    for (int32_t package_id = 0; package_id < compiler->packages->length; package_id++) {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
      const char* package_name = package->name;
      const char* package_load_path = package->load_path;
      SV* sv_package_load_path = sv_2mortal(newSVpv(package_load_path, 0));

      SV** sv_packages_ptr = hv_fetch(hv_self, "packages", strlen("packages"), 0);
      SV* sv_packages = sv_packages_ptr ? *sv_packages_ptr : &PL_sv_undef;
      HV* hv_packages = (HV*)SvRV(sv_packages);
      
      // Create package info hash reference if not exists
      {
        SV** sv_package_info_ptr = hv_fetch(hv_packages, package_name, strlen(package_name), 0);
        if (!sv_package_info_ptr) {
          HV* hv_package_info = (HV*)sv_2mortal((SV*)newHV());
          SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));
          (void)hv_store(hv_packages, package_name, strlen(package_name), SvREFCNT_inc(sv_package_info), 0);
        }
      }
      
      // Package
      SV** sv_package_info_ptr = hv_fetch(hv_packages, package_name, strlen(package_name), 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Package load path
      (void)hv_store(hv_package_info, "load_path", strlen("load_path"), SvREFCNT_inc(sv_package_load_path), 0);

      // Create subs hash reference if not exists
      {
        SV** sv_subs_ptr = hv_fetch(hv_package_info, "subs", strlen("subs"), 0);
        if (!sv_subs_ptr) {
          HV* hv_subs = (HV*)sv_2mortal((SV*)newHV());
          SV* sv_subs = sv_2mortal(newRV_inc((SV*)hv_subs));
          (void)hv_store(hv_package_info, "subs", strlen("subs"), SvREFCNT_inc(sv_subs), 0);
        }
      }

      // Subroutines
      SV** sv_subs_ptr = hv_fetch(hv_package_info, "subs", strlen("subs"), 0);
      SV* sv_subs = sv_subs_ptr ? *sv_subs_ptr : &PL_sv_undef;
      HV* hv_subs = (HV*)SvRV(sv_subs);
      
      for (int32_t sub_id = 0; sub_id < package->subs->length; sub_id++) {
        SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, sub_id);
        const char* sub_name = sub->name;
        SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, 0));

        // Create sub info hash reference if not exists
        {
          SV** sv_sub_info_ptr = hv_fetch(hv_subs, sub_name, strlen(sub_name), 0);
          if (!sv_sub_info_ptr) {
            HV* hv_sub_info = (HV*)sv_2mortal((SV*)newHV());
            SV* sv_sub_info = sv_2mortal(newRV_inc((SV*)hv_sub_info));
            (void)hv_store(hv_subs, sub_name, strlen(sub_name), SvREFCNT_inc(sv_sub_info), 0);
          }
        }
        SV** sv_sub_info_ptr = hv_fetch(hv_subs, sub_name, strlen(sub_name), 0);
        SV* sv_sub_info = sv_sub_info_ptr ? *sv_sub_info_ptr : &PL_sv_undef;
        HV* hv_sub_info = (HV*)SvRV(sv_sub_info);
        
        // Subroutine have_native_desc
        int32_t sub_have_native_desc = sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC;
        SV* sv_sub_have_native_desc = sv_2mortal(newSViv(sub_have_native_desc));

        // Subroutine have_precompile_desc
        int32_t sub_have_precompile_desc = sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC;
        SV* sv_sub_have_precompile_desc = sv_2mortal(newSViv(sub_have_precompile_desc));

        (void)hv_store(hv_sub_info, "have_native_desc", strlen("have_native_desc"), SvREFCNT_inc(sv_sub_have_native_desc), 0);
        (void)hv_store(hv_sub_info, "have_precompile_desc", strlen("have_precompile_desc"), SvREFCNT_inc(sv_sub_have_precompile_desc), 0);
      }
    }
    
    // Build portable info
    SPVM_PORTABLE* portable = SPVM_PORTABLE_build_portable(compiler);
    
    // Create run-time env
    SPVM_ENV* env = SPVM_RUNTIME_build_runtime_env(portable);
    
    // Set ENV
    size_t iv_env = PTR2IV(env);
    SV* sviv_env = sv_2mortal(newSViv(iv_env));
    SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
    (void)hv_store(hv_self, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
  }

  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  if (SvOK(sv_env)) {
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    SPVM_RUNTIME_free(env);
    free(env);
  }
}

MODULE = SPVM::Builder::C		PACKAGE = SPVM::Builder::C

SV*
bind_sub_native(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);
  SV* sv_native_address = ST(3);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  // Set native address to subroutine
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  runtime->sub_native_addresses[sub->id] = native_address;
  
  XSRETURN(0);
}

SV*
build_package_csource_precompile(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  int32_t package_id = package->id;
  
  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // Build package csource
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_package_csource(env, string_buffer, package_name);
  
  SV* sv_package_csource = sv_2mortal(newSVpv(string_buffer->buffer, string_buffer->length));
  
  SPVM_STRING_BUFFER_free(string_buffer);

  XPUSHs(sv_package_csource);
  XSRETURN(1);
}

SV*
bind_sub_precompile(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);
  SV* sv_precompile_address = ST(3);
  
  void* sub_precompile_address = INT2PTR(void*, SvIV(sv_precompile_address));
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  sub->flag |= SPVM_SUB_C_FLAG_IS_COMPILED;
  runtime->sub_precompile_addresses[sub->id] = sub_precompile_address;
  
  XSRETURN(0);
}

MODULE = SPVM::PerlAPI		PACKAGE = SPVM::PerlAPI

SV*
new_byte_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_byte_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
new_short_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_short_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
new_int_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_int_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
new_long_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_long_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
new_float_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_float_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
new_double_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // New array
  void* array =  env->new_double_array_raw(env, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
new_object_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_length = ST(2);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  int32_t length = (int32_t)SvIV(sv_length);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_HASH_fetch(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  assert(basic_type);
  
  // New array
  void* array = env->new_object_array_raw(env, basic_type->id, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_multi_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_element_type_dimension = ST(2);
  SV* sv_length = ST(3);
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  int32_t length = (int32_t)SvIV(sv_length);

  int32_t element_type_dimension = (int32_t)SvIV(sv_element_type_dimension);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_HASH_fetch(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  assert(basic_type);
  
  // New array
  void* array = env->new_multi_array_raw(env, basic_type->id, element_type_dimension, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_value_t_array_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_length = ST(2);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  int32_t length = (int32_t)SvIV(sv_length);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_HASH_fetch(runtime->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  
  if (basic_type == NULL) {
    const char* basic_type_name = runtime->symbols[basic_type->name_id];
    croak("Can't load %s", basic_type_name);
  }
  
  // New array
  void* array = env->new_value_t_array_raw(env, basic_type->id, length);
  
  // Increment reference count
  env->inc_ref_count(env, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::Data::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_exception_undef(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));

  env->set_exception(env, NULL);
  
  XSRETURN(0);
}

SV*
get_memory_blocks_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t memory_blocks_count = env->get_memory_blocks_count(env);
  SV* sv_memory_blocks_count = sv_2mortal(newSViv(memory_blocks_count));
  
  XPUSHs(sv_memory_blocks_count);
  XSRETURN(1);
}

SV*
call_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);

  int32_t arg_start = 3;

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  const char* package_name = SvPV_nolen(sv_package_name);
  const char* sub_name = SvPV_nolen(sv_sub_name);

  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (package == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  if (sub == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  const char* sub_signature = runtime->symbols[sub->signature_id];
  int32_t sub_id = env->get_sub_id(env, package_name, sub_signature);
  if (sub_id < 0) {
    croak("Subroutine not found %s %s", package_name, sub_signature);
  }

  SPVM_VALUE stack[SPVM_LIMIT_C_STACK_MAX];
  
  int32_t ref_stack_top = 0;
  SPVM_VALUE ref_stack[SPVM_LIMIT_C_STACK_MAX];

  int32_t ref_stack_ids[SPVM_LIMIT_C_STACK_MAX];
  
  // Arguments
  int32_t args_contain_ref = 0;
  {
    // If class method, first argument is ignored
    if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD) {
      arg_start++;
    }
    
    int32_t arg_index;
    // Check argument count
    if (items - arg_start != sub->arg_ids_length) {
      croak("Argument count is defferent");
    }
    
    int32_t arg_var_id = 0;
    for (arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_MY* arg = &runtime->args[sub->arg_ids_base + arg_index];

      int32_t arg_type_is_numeric_type = SPVM_RUNTIME_API_is_numeric_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      int32_t arg_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      int32_t arg_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      int32_t arg_type_is_ref_type = SPVM_RUNTIME_API_is_ref_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);

      SV* sv_value = ST(arg_index + arg_start);
      
      int32_t arg_basic_type_id = arg->basic_type_id;
      int32_t arg_type_dimension = arg->type_dimension;
      int32_t arg_type_flag = arg->type_flag;

      SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];
      
      int32_t type_width = arg->type_width;
      if (arg_type_is_numeric_type) {
        switch (arg_basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE : {
            int8_t value = (int8_t)SvIV(sv_value);
            stack[arg_var_id].bval = value;
            arg_var_id++;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_SHORT : {
            int16_t value = (int16_t)SvIV(sv_value);
            stack[arg_var_id].sval = value;
            arg_var_id++;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_INT : {
            int32_t value = (int32_t)SvIV(sv_value);
            stack[arg_var_id].ival = value;
            arg_var_id++;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_LONG : {
            int64_t value = (int64_t)SvIV(sv_value);
            stack[arg_var_id].lval = value;
            arg_var_id++;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_FLOAT : {
            float value = (float)SvNV(sv_value);
            stack[arg_var_id].fval = value;
            arg_var_id++;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_DOUBLE : {
            double value = (double)SvNV(sv_value);
            stack[arg_var_id].dval = value;
            arg_var_id++;
            break;
          }
          default:
            assert(0);
        }
      }
      else if (arg_type_is_value_type) {
        switch (arg->runtime_type) {
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                int8_t value = (int8_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].bval = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                int16_t value = (int16_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].sval = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                int32_t value = (int32_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].ival = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                int64_t value = (int64_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].lval = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                float value = (float)SvNV(sv_field_value);
                stack[arg_var_id + field_index].fval = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE: {
            if (sv_derived_from(sv_value, "HASH")) {
              HV* hv_value = (HV*)SvRV(sv_value);

              SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
              assert(arg_package);

              SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
              assert(arg_first_field);
              for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                const char* field_name = runtime->symbols[field->name_id];

                SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                SV* sv_field_value;
                if (sv_field_value_ptr) {
                  sv_field_value = *sv_field_value_ptr;
                }
                else {
                  sv_field_value = sv_2mortal(newSViv(0));
                }
                double value = (double)SvNV(sv_field_value);
                stack[arg_var_id + field_index].dval = value;
              }
              arg_var_id += arg_package->fields->length;
            }
            else {
              croak("%dth argument must be hash reference", arg_index + 1);
            }
            break;
          }
          default:
            assert(0);
        }
      }
      else if (arg_type_is_object_type) {
        if (!SvOK(sv_value)) {
          stack[arg_var_id].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::Data")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);

            if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
              croak("%dth argument is invalid object type", arg_index);
            }
            
            stack[arg_var_id].oval = object;
          }
          else {
            croak("%dth argument must be SPVM::Data object", arg_index);
          }
        }
        arg_var_id++;
      }
      else if (arg_type_is_ref_type) {
        args_contain_ref = 1;
        int32_t arg_type_is_numeric_ref_type = SPVM_RUNTIME_API_is_numeric_ref_type(env, arg_basic_type_id, arg_type_dimension, arg_type_flag);
        int32_t arg_type_is_value_ref_type = SPVM_RUNTIME_API_is_value_ref_type(env, arg_basic_type_id, arg_type_dimension, arg_type_flag);
        
        if (arg_type_is_numeric_ref_type) {
          SV* sv_value_deref = SvRV(sv_value);
          switch (arg_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              int8_t value = (int8_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].bval = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              int16_t value = (int16_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].sval = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              int32_t value = (int32_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].ival = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              int64_t value = (int64_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].lval = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              float value = (float)SvNV(sv_value_deref);
              ref_stack[ref_stack_top].fval = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              double value = (double)SvNV(sv_value_deref);
              ref_stack[ref_stack_top].dval = value;
              stack[arg_var_id].oval = &ref_stack[ref_stack_top];
              ref_stack_ids[arg_index] = ref_stack_top;
              ref_stack_top++;
              arg_var_id++;
              break;
            }
            default:
              assert(0);
          }
        }
        else if (arg_type_is_value_ref_type) {
          switch (arg->runtime_type) {
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  ((SPVM_VALUE_byte*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  ((SPVM_VALUE_short*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  ((SPVM_VALUE_int*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  ((SPVM_VALUE_long*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  float value = (float)SvNV(sv_field_value);
                  ((SPVM_VALUE_float*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE: {
              if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
                HV* hv_value = (HV*)SvRV(SvRV(sv_value));
                
                SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
                assert(arg_package);
            
                SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
                assert(first_field);
                
                for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
                  SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
                  const char* field_name = runtime->symbols[field->name_id];

                  SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
                  SV* sv_field_value;
                  if (sv_field_value_ptr) {
                    sv_field_value = *sv_field_value_ptr;
                  }
                  else {
                    sv_field_value = sv_2mortal(newSViv(0));
                  }
                  double value = (double)SvNV(sv_field_value);
                  ((SPVM_VALUE_double*)&ref_stack[ref_stack_top])[field_index] = value;
                }
                stack[arg_var_id].oval = &ref_stack[ref_stack_top];
                ref_stack_ids[arg_index] = ref_stack_top;
                int32_t fields_length = arg_package->fields->length;
                ref_stack_top += fields_length;
                arg_var_id++;
              }
              else {
                croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
              }
              break;
            }
            default:
              assert(0);
          }

        }
        else {
          assert(0);
        }
      }
    }
  }
  
  // Return type id
  int32_t sub_return_basic_type_id = sub->return_basic_type_id;
  int32_t sub_return_type_dimension = sub->return_type_dimension;
  int32_t sub_return_type_flag = sub->return_type_flag;

  int32_t sub_return_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);
  int32_t sub_return_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);
  
  // Return count
  SV* sv_return_value = NULL;
  int32_t excetpion_flag;
  if (sub_return_type_is_value_type) {
    excetpion_flag = env->call_sub(env, sub_id, stack);
    
    SPVM_RUNTIME_BASIC_TYPE* sub_return_basic_type = &runtime->basic_types[sub_return_basic_type_id];

    SPVM_RUNTIME_PACKAGE* sub_return_package = &runtime->packages[sub_return_basic_type->package_id];
    assert(sub_return_package);
    
    SPVM_RUNTIME_FIELD* sub_return_first_field = SPVM_LIST_fetch(sub_return_package->fields, 0);
    assert(sub_return_first_field);
    
    HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
    for (int32_t field_index = 0; field_index < sub_return_package->fields->length; field_index++) {
      SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(sub_return_package->fields, field_index);
      const char* field_name = runtime->symbols[field->name_id];
      
      SV* sv_field_value = NULL;
      switch (sub_return_first_field->basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          sv_field_value = sv_2mortal(newSViv(stack[field_index].bval));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          sv_field_value = sv_2mortal(newSViv(stack[field_index].sval));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          sv_field_value = sv_2mortal(newSViv(stack[field_index].ival));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          sv_field_value = sv_2mortal(newSViv(stack[field_index].lval));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          sv_field_value = sv_2mortal(newSVnv(stack[field_index].fval));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          sv_field_value = sv_2mortal(newSVnv(stack[field_index].dval));
          break;
        }
        default:
          assert(0);
      }
      
      (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
      sv_return_value = sv_2mortal(newRV_inc((SV*)hv_value));
    }
  }
  else if (sub_return_type_is_object_type) {
    excetpion_flag = env->call_sub(env, sub_id, stack);
    if (!excetpion_flag) {
      void* return_value = stack[0].oval;
      sv_return_value = NULL;
      if (return_value != NULL) {
        env->inc_ref_count(env, return_value);
        
        if (sub_return_type_dimension == 0) {
          SV* sv_return_type_name = SPVM_XS_UTIL_create_sv_type_name(env, sub_return_basic_type_id, sub_return_type_dimension);
          
          sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, SvPV_nolen(sv_return_type_name));
        }
        else if (sub_return_type_dimension > 0) {
          sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::Data::Array");
        }
      }
      else {
        sv_return_value = &PL_sv_undef;
      }
    }
  }
  else {
    switch (sub_return_basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_VOID:  {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].bval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].sval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].ival));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].lval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        excetpion_flag = env->call_sub(env, sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSVnv(stack[0].dval));
        }
        break;
      }
      default:
        assert(0);
    }
  }
  
  if (args_contain_ref) {
    int32_t arg_var_id = 0;
    for (int32_t arg_index = 0; arg_index < sub->arg_ids_length; arg_index++) {
      SV* sv_value = ST(arg_index + arg_start);

      SPVM_RUNTIME_MY* arg = &runtime->args[sub->arg_ids_base + arg_index];

      int32_t arg_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      int32_t arg_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      int32_t arg_type_is_ref_type = SPVM_RUNTIME_API_is_ref_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
      
      int32_t arg_basic_type_id = arg->basic_type_id;
      int32_t arg_type_dimension = arg->type_dimension;
      int32_t arg_type_flag = arg->type_flag;

      SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[arg->basic_type_id];

      if (arg_type_is_ref_type) {
        int32_t ref_stack_id = ref_stack_ids[arg_index];
        
        int32_t arg_type_is_numeric_ref_type = SPVM_RUNTIME_API_is_numeric_ref_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
        int32_t arg_type_is_value_ref_type = SPVM_RUNTIME_API_is_value_ref_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
        
        if (arg_type_is_numeric_ref_type) {
          SV* sv_value_deref = SvRV(sv_value);
          
          switch (arg_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE : {
              sv_setiv(sv_value_deref, ref_stack[ref_stack_id].bval);
              break;
            }
            case  SPVM_BASIC_TYPE_C_ID_SHORT : {
              sv_setiv(sv_value_deref, ref_stack[ref_stack_id].sval);
              break;
            }
            case  SPVM_BASIC_TYPE_C_ID_INT : {
              sv_setiv(sv_value_deref, ref_stack[ref_stack_id].ival);
              break;
            }
            case  SPVM_BASIC_TYPE_C_ID_LONG : {
              sv_setiv(sv_value_deref, ref_stack[ref_stack_id].lval);
              break;
            }
            case  SPVM_BASIC_TYPE_C_ID_FLOAT : {
              sv_setnv(sv_value_deref, ref_stack[ref_stack_id].fval);
              break;
            }
            case  SPVM_BASIC_TYPE_C_ID_DOUBLE : {
              sv_setnv(sv_value_deref, ref_stack[ref_stack_id].dval);
              break;
            }
            default:
              assert(0);
          }
        }
        else if (arg_type_is_value_ref_type) {
          int32_t ref_stack_id = ref_stack_ids[arg_index];
          
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));

          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);

          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = runtime->symbols[field->name_id];
            
            SV* sv_field_value;
            switch (arg_first_field->basic_type_id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_byte*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_short*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_int*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                sv_field_value = sv_2mortal(newSViv(((SPVM_VALUE_long*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                sv_field_value = sv_2mortal(newSVnv(((SPVM_VALUE_float*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                sv_field_value = sv_2mortal(newSVnv(((SPVM_VALUE_double*)&ref_stack[ref_stack_id])[field_index]));
                break;
              }
              default:
                assert(0);
            }
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
        }
        else {
          assert(0);
        }
      }
    }
  }

  // Exception
  if (excetpion_flag) {
    void* exception = env->get_exception(env);
    int32_t length = env->get_array_length(env, exception);
    const char* exception_bytes = (char*)env->get_byte_array_elements(env, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_bytes, length));
    croak("%s\n ", SvPV_nolen(sv_exception));
  }
  // Success
  else {
    int32_t return_count;
    if (sub_return_type_dimension == 0 && sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
      return_count = 0;
    }
    else {
      XPUSHs(sv_return_value);
      return_count = 1;
    }
    
    XSRETURN(return_count);
  }
}

SV*
set_array_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_values = ST(2);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array object
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object)");
  }

  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Values must be array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece)");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);

  int32_t length = env->get_array_length(env, array);

  // Check length
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length)");
  }
  
  int32_t array_basic_type_id  = array->basic_type_id;
  int32_t array_type_dimension = array->type_dimension;
  int32_t array_type_flag = array->type_flag;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, array_basic_type_id, array_type_dimension, array_type_flag);
  
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array_basic_type_id];
    int32_t element_type_dimension = array_type_dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, array_basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, array_basic_type_id, element_type_dimension, 0);
    
    if (element_type_is_value_type) {
      for (int32_t index = 0; index < length; index++) {
        SV** sv_value_ptr = av_fetch(av_values, index, 0);
        SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;

        if (sv_derived_from(sv_value, "HASH")) {
          
          SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
          assert(package);
          
          SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
          assert(first_field);

          void* elements = (void*)env->get_int_array_elements(env, array);
          
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t field_length = package->fields->length;
          for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
            const char* field_name = runtime->symbols[field->name_id];

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = sv_2mortal(newSViv(0));
            }

            switch (first_field->basic_type_id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                ((SPVM_VALUE_byte*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_byte)SvIV(sv_field_value);
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                ((SPVM_VALUE_short*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_short)SvIV(sv_field_value);
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                ((SPVM_VALUE_int*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_int)SvIV(sv_field_value);
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                ((SPVM_VALUE_long*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_long)SvIV(sv_field_value);
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                ((SPVM_VALUE_float*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_float)SvNV(sv_field_value);
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                ((SPVM_VALUE_double*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_double)SvNV(sv_field_value);
                break;
              }
              default:
                assert(0);
            }
          }
        }
        else {
          croak("Element must be hash reference");
        }
      }
    }
    else if (element_type_is_object_type) {
      for (int32_t index = 0; index < length; index++) {
        SV** sv_value_ptr = av_fetch(av_values, index, 0);
        SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
        
        if (!SvOK(sv_value)) {
          env->set_object_array_element(env, array, index, NULL);
        }
        else if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::Data")) {
          SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
          
          if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
            env->set_object_array_element(env, array, index, object);
          }
          else {
            croak("Element is invalid object type");
          }
        }
        else {
          croak("Element must be SPVM::Data object");
        }
      }
    }
    else {
      switch (array_basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elements = env->get_byte_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (int8_t)SvIV(sv_value);
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elements = env->get_short_array_elements(env, array);

          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (int16_t)SvIV(sv_value);
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elements = env->get_int_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (int32_t)SvIV(sv_value);
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elements = env->get_long_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (int64_t)SvIV(sv_value);
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elements = env->get_float_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (float)SvNV(sv_value);
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elements = env->get_double_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV** sv_value_ptr = av_fetch(av_values, i, 0);
              SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
              elements[i] = (double)SvNV(sv_value);
            }
          }
          break;
        }
        default:
          croak("Invalid type");
      }
    }
  }
  else {
    croak("Argument must be array type");
  }
  
  XSRETURN(0);
}

SV*
set_array_elements_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_bin = ST(2);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array object
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object)");
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->get_array_length(env, array);
  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, dimension, 0);

  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, basic_type_id, element_type_dimension, 0);
    
    if (element_type_is_value_type) {
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
      assert(package);
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      assert(first_field);


      int32_t field_length = package->fields->length;
      
      switch (first_field->basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          // Check range
          if ((int32_t)sv_len(sv_bin) != field_length * length) {
            croak("Data total byte size must be same as %d * array length)", field_length);
          }

          int8_t* elements = env->get_byte_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          if ((int32_t)sv_len(sv_bin) != field_length * length * 2) {
            croak("Data total byte size must be same as %d * array length * 2)", field_length);
          }
          int16_t* elements = env->get_short_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length * 2);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          if ((int32_t)sv_len(sv_bin) != field_length * length * 4) {
            croak("Data total byte size must be same as %d * array length * 4)", field_length);
          }
          int32_t* elements = env->get_int_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length * 4);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          if ((int32_t)sv_len(sv_bin) != field_length * length * 8) {
            croak("Data total byte size must be same as %d * array length * 8)", field_length);
          }
          int64_t* elements = env->get_long_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length * 8);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          if ((int32_t)sv_len(sv_bin) != field_length * length * 4) {
            croak("Data total byte size must be same as %d * array length * 4)", field_length);
          }
          float* elements = env->get_float_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length * 4);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          if ((int32_t)sv_len(sv_bin) != field_length * length * 8) {
            croak("Data total byte size must be same as %d * array length * 8)", field_length);
          }
          double* elements = env->get_double_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), field_length * length * 8);
          }
          break;
        }
        default:
          assert(0);
      }
    }
    else if (element_type_is_object_type) {
      croak("Object array is not supported");
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          // Check range
          if ((int32_t)sv_len(sv_bin) != length) {
            croak("Data total byte size must be same as array length)");
          }

          int8_t* elements = env->get_byte_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          if ((int32_t)sv_len(sv_bin) != length * 2) {
            croak("Data total byte size must be same as array length * 2)");
          }
          int16_t* elements = env->get_short_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length * 2);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          if ((int32_t)sv_len(sv_bin) != length * 4) {
            croak("Data total byte size must be same as array length * 4)");
          }
          int32_t* elements = env->get_int_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length * 4);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          if ((int32_t)sv_len(sv_bin) != length * 8) {
            croak("Data total byte size must be same as array length * 8)");
          }
          int64_t* elements = env->get_long_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length * 8);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          if ((int32_t)sv_len(sv_bin) != length * 4) {
            croak("Data total byte size must be same as array length * 4)");
          }
          float* elements = env->get_float_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length * 4);
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          if ((int32_t)sv_len(sv_bin) != length * 8) {
            croak("Data total byte size must be same as array length * 8)");
          }
          double* elements = env->get_double_array_elements(env, array);
          if (length > 0) {
            memcpy(elements, SvPV_nolen(sv_bin), length * 8);
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array type");
  }
  
  XSRETURN(0);
}

SV*
set_array_element(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);
  SV* sv_value = ST(3);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Check undef
  if (!SvOK(sv_array)) {
    croak("Array nust not be NULL");
  }
  
  // Check array object
  if (!(sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object");
  }

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->get_array_length(env, array);
   
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, dimension, 0);

  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, basic_type_id, element_type_dimension, 0);
    
    if (element_type_is_value_type) {
      if (sv_derived_from(sv_value, "HASH")) {
        SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
        assert(package);
        
        SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
        assert(first_field);

        void* elements = (void*)env->get_int_array_elements(env, array);
        
        HV* hv_value = (HV*)SvRV(sv_value);
        int32_t field_length = package->fields->length;
        for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
          const char* field_name = runtime->symbols[field->name_id];

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = sv_2mortal(newSViv(0));
          }

          switch (first_field->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              ((SPVM_VALUE_byte*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_byte)SvIV(sv_field_value);
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              ((SPVM_VALUE_short*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_short)SvIV(sv_field_value);
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              ((SPVM_VALUE_int*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_int)SvIV(sv_field_value);
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              ((SPVM_VALUE_long*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_long)SvIV(sv_field_value);
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              ((SPVM_VALUE_float*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_float)SvNV(sv_field_value);
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              ((SPVM_VALUE_double*)elements)[(field_length * index) + field_index] = (SPVM_VALUE_double)SvNV(sv_field_value);
              break;
            }
            default:
              assert(0);
          }
        }
      }
      else {
        croak("Element must be hash reference");
      }
    }
    else if (element_type_is_object_type) {
      if (!SvOK(sv_value)) {
        env->set_object_array_element(env, array, index, NULL);
      }
      else if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::Data")) {
        SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
        
        if (object->basic_type_id == basic_type_id && object->type_dimension == element_type_dimension) {
          env->set_object_array_element(env, array, index, object);
        }
        else {
          croak("Element is invalid object type");
        }
      }
      else {
        croak("Element must be SPVM::Data object");
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          // Value
          int8_t value = (int8_t)SvIV(sv_value);
          
          // Set element
          int8_t* elements = env->get_byte_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          // Value
          int16_t value = (int16_t)SvIV(sv_value);
          
          // Set element
          int16_t* elements = env->get_short_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          // Value
          int32_t value = (int32_t)SvIV(sv_value);
          
          // Set element
          int32_t* elements = env->get_int_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          // Value
          int64_t value = (int64_t)SvIV(sv_value);
          
          // Set element
          int64_t* elements = env->get_long_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          // Value
          float value = (float)SvNV(sv_value);
          
          // Set element
          float* elements = env->get_float_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          // Value
          double value = (double)SvNV(sv_value);
          
          // Set element
          double* elements = env->get_double_array_elements(env, array);
          
          elements[index] = value;
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument is not array type");
  }
  
  XSRETURN(0);
}

SV*
get_array_element(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Check undef
  if (!SvOK(sv_array)) {
    croak("Array nust not be NULL");
  }
  
  // Check array object
  if (!(sv_isobject(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object");
  }

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->get_array_length(env, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, dimension, 0);

  SV* sv_value = NULL;
  int32_t is_object = 0;
  if (is_array_type) {
    int32_t element_type_dimension = dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, basic_type_id, element_type_dimension, 0);

    if (element_type_is_value_type) {
      SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];
      
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
      assert(package);
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      assert(first_field);

      void* elements = (void*)env->get_int_array_elements(env, array);
      
      HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
      int32_t field_length = package->fields->length;
      for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
        SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
        const char* field_name = runtime->symbols[field->name_id];

        SV* sv_field_value;
        switch (first_field->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            SPVM_VALUE_byte field_value = ((SPVM_VALUE_byte*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSViv(field_value));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            SPVM_VALUE_short field_value = ((SPVM_VALUE_short*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSViv(field_value));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            SPVM_VALUE_int field_value = ((SPVM_VALUE_int*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSViv(field_value));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            SPVM_VALUE_long field_value = ((SPVM_VALUE_long*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSViv(field_value));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            SPVM_VALUE_float field_value = ((SPVM_VALUE_float*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSVnv(field_value));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            SPVM_VALUE_double field_value = ((SPVM_VALUE_double*)elements)[(field_length * index) + field_index];
            sv_field_value = sv_2mortal(newSVnv(field_value));
            break;
          }
          default:
            assert(0);
        }
        (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
        sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
      }
    }
    else if (element_type_is_object_type) {
      
      // Element type id
      SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];

      // Index
      SPVM_OBJECT* value = env->get_object_array_element(env, array, index);
      if (value != NULL) {
        env->inc_ref_count(env, value);
      }
      
      int32_t element_type_is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, element_type_dimension, 0);
      if (element_type_is_array_type) {
        sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::Data::Array");
      }
      else {
        const char* basic_type_name = runtime->symbols[basic_type->name_id];
        SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
        sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_basic_type_name));
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          // Get element
          int8_t* elements = env->get_byte_array_elements(env, array);
          int8_t value = elements[index];
          sv_value = sv_2mortal(newSViv(value));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          // Get element
          int16_t* elements = env->get_short_array_elements(env, array);
          int16_t value = elements[index];
          sv_value = sv_2mortal(newSViv(value));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          // Get element
          int32_t* elements = env->get_int_array_elements(env, array);
          int32_t value = elements[index];
          sv_value = sv_2mortal(newSViv(value));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          // Get element
          int64_t* elements = env->get_long_array_elements(env, array);
          int64_t value = elements[index];
          sv_value = sv_2mortal(newSViv(value));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          // Get element
          float* elements = env->get_float_array_elements(env, array);
          float value = elements[index];
          sv_value = sv_2mortal(newSVnv(value));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          // Get element
          double* elements = env->get_double_array_elements(env, array);
          double value = elements[index];
          sv_value = sv_2mortal(newSVnv(value));
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array reference");
  }
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_array_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array object
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object)");
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->get_array_length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, dimension, 0);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, basic_type_id, element_type_dimension, 0);

    if (element_type_is_value_type) {
      
      for (int32_t index = 0; index < length; index++) {
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];
        
        SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
        assert(package);
        
        SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
        assert(first_field);

        void* elements = (void*)env->get_int_array_elements(env, array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t field_length = package->fields->length;
        for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
          const char* field_name = runtime->symbols[field->name_id];

          SV* sv_field_value;
          switch (first_field->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_VALUE_byte field_value = ((SPVM_VALUE_byte*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_VALUE_short field_value = ((SPVM_VALUE_short*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_VALUE_int field_value = ((SPVM_VALUE_int*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_VALUE_long field_value = ((SPVM_VALUE_long*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_VALUE_float field_value = ((SPVM_VALUE_float*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_VALUE_double field_value = ((SPVM_VALUE_double*)elements)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            default:
              assert(0);
          }
          SvREFCNT_inc(sv_field_value);
          (void)hv_store(hv_value, field_name, strlen(field_name), sv_field_value, 0);
        }
        SV* sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else if (element_type_is_object_type) {
      for (int32_t index = 0; index < length; index++) {
        // Element type id
        SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[array->basic_type_id];

        // Index
        SPVM_OBJECT* value = env->get_object_array_element(env, array, index);
        if (value != NULL) {
          env->inc_ref_count(env, value);
        }
        
        int32_t element_type_is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, element_type_dimension, 0);
        SV* sv_value;
        if (element_type_is_array_type) {
          sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::Data::Array");
        }
        else {
          const char* basic_type_name = runtime->symbols[basic_type->name_id];
          SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
          sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_basic_type_name));
        }
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elements = env->get_byte_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elements = env->get_short_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elements = env->get_int_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elements = env->get_long_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSViv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elements = env->get_float_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSVnv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elements = env->get_double_array_elements(env, array);
          {
            int32_t i;
            for (i = 0; i < length; i++) {
              SV* sv_value = sv_2mortal(newSVnv(elements[i]));
              av_push(av_values, SvREFCNT_inc(sv_value));
            }
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array type");
  }

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_array_elements_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->runtime;

  // Array must be SPVM::Data::Array object
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::Data::Array"))) {
    croak("Array must be SPVM::Data::Array object)");
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->get_array_length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = SPVM_RUNTIME_API_is_array_type(env, basic_type_id, dimension, 0);
  
  SV* sv_bin;
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    int32_t element_type_dimension = dimension - 1;
    int32_t element_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, basic_type_id, element_type_dimension, 0);
    int32_t element_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, basic_type_id, element_type_dimension, 0);

    if (element_type_is_value_type) {
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
      assert(package);
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      assert(first_field);

      int32_t field_length = package->fields->length;

      switch (first_field->basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elements = env->get_byte_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elements = env->get_short_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elements = env->get_int_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elements = env->get_long_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elements = env->get_float_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elements = env->get_double_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, field_length * length * 8));
          break;
        }
        default:
          croak("Invalid type");
      }
    }
    else if (element_type_is_object_type) {
      croak("Objec type is not supported");
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elements = env->get_byte_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elements = env->get_short_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elements = env->get_int_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elements = env->get_long_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elements = env->get_float_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elements = env->get_double_array_elements(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elements, length * 8));
          break;
        }
        default:
          croak("Invalid type");
      }
    }
  }
  else {
    croak("Argument must be array type");
  }
  
  XPUSHs(sv_bin);
  XSRETURN(1);
}

MODULE = SPVM::Builder::Exe		PACKAGE = SPVM::Builder::Exe

SV*
build_main_csource(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = (HV*)SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_PORTABLE* portable = runtime->portable;

  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);

  SPVM_CSOURCE_BUILDER_EXE_build_exe_csource(env, string_buffer, portable, package_name);

  SV* sv_main_csource = sv_2mortal(newSVpv(string_buffer->buffer, string_buffer->length));

  SPVM_STRING_BUFFER_free(string_buffer);
  
  XPUSHs(sv_main_csource);
  XSRETURN(1);
}


MODULE = SPVM		PACKAGE = SPVM

