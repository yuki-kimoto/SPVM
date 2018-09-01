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
#include "spvm_csource_builder.h"
#include "spvm_list.h"
#include "spvm_csource_builder.h"
#include "spvm_string_buffer.h"
#include "spvm_use.h"
#include "spvm_limit.h"

#include "spvm_runtime_sub.h"
#include "spvm_runtime_builder.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"

SV* SPVM_XS_UTIL_new_sv_object(SPVM_ENV* env, SPVM_OBJECT* object, const char* package) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));

  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  hv_store(hv_data, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  HV* hv_class = gv_stashpv(package, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

SPVM_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = SvRV(sv_data);
    
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
  SV* hv_object = (HV*)SvRV(sv_object);

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

MODULE = SPVM::Data::Array		PACKAGE = SPVM::Data::Array

MODULE = SPVM::Build::Info		PACKAGE = SPVM::Build::Info

SV*
get_subs(...)
  PPCODE:
{
  (void)RETVAL;
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  
  AV* av_subs = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->subs->length; sub_index++) {
      
      SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);

      // Subroutine name
      const char* sub_name = runtime->symbols[sub->name_id];
      SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
      
      // Subroutine name
      const char* sub_abs_name = runtime->symbols[sub->abs_name_id];
      SV* sv_sub_abs_name = sv_2mortal(newSVpvn(sub_abs_name, strlen(sub_abs_name)));
      
      // Subroutine id
      int32_t sub_id = sub->id;
      SV* sv_sub_id = sv_2mortal(newSViv(sub_id));

      // Subroutine is_enum
      int32_t sub_is_enum = sub->flag & SPVM_SUB_C_FLAG_IS_ENUM;
      SV* sv_sub_is_enum = sv_2mortal(newSViv(sub_is_enum));

      // Subroutine have_native_desc
      int32_t sub_have_native_desc = sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC;
      SV* sv_sub_have_native_desc = sv_2mortal(newSViv(sub_have_native_desc));

      // Subroutine have_precompile_desc
      int32_t sub_have_precompile_desc = sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC;
      SV* sv_sub_have_precompile_desc = sv_2mortal(newSViv(sub_have_precompile_desc));

      // Subroutine
      HV* hv_sub = (HV*)sv_2mortal((SV*)newHV());
      
      hv_store(hv_sub, "name", strlen("name"), SvREFCNT_inc(sv_sub_name), 0);
      hv_store(hv_sub, "abs_name", strlen("abs_name"), SvREFCNT_inc(sv_sub_abs_name), 0);
      hv_store(hv_sub, "is_enum", strlen("is_enum"), SvREFCNT_inc(sv_sub_is_enum), 0);
      hv_store(hv_sub, "have_native_desc", strlen("have_native_desc"), SvREFCNT_inc(sv_sub_have_native_desc), 0);
      hv_store(hv_sub, "have_precompile_desc", strlen("have_precompile_desc"), SvREFCNT_inc(sv_sub_have_precompile_desc), 0);
      
      SV* sv_sub = sv_2mortal(newRV_inc((SV*)hv_sub));
      av_push(av_subs, SvREFCNT_inc((SV*)sv_sub));
    }
  }
  
  SV* sv_subs = sv_2mortal(newRV_inc((SV*)av_subs));
  
  XPUSHs(sv_subs);
  XSRETURN(1);
}

SV*
get_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  
  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->subs->length; sub_index++) {
      
      SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
      
      // Subroutine name
      const char* sub_name = runtime->symbols[sub->name_id];
      SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
      
      av_push(av_sub_names, SvREFCNT_inc((SV*)sv_sub_name));
    }
  }
  
  SV* sv_subs = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  XPUSHs(sv_subs);
  XSRETURN(1);
}

SV*
get_package_names(...)
  PPCODE:
{
  (void)RETVAL;
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
  AV* av_package_names = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t package_index;
    for (package_index = 0; package_index < runtime->packages_length; package_index++) {
      SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_index];
      
      // Package name
      const char* package_name = runtime->symbols[package->name_id];
      SV* sv_package_name = sv_2mortal(newSVpvn(package_name, strlen(package_name)));
      
      av_push(av_package_names, SvREFCNT_inc((SV*)sv_package_name));
    }
  }
  
  SV* sv_package_names = sv_2mortal(newRV_inc((SV*)av_package_names));
  
  XPUSHs(sv_package_names);
  XSRETURN(1);
}

SV*
get_package_load_path(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

  SV* sv_package_name = ST(1);
  
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Subroutine information
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));;
  
  const char* package_load_path = runtime->symbols[package->load_path_id];
  
  SV* sv_package_load_path = sv_2mortal(newSVpvn(package_load_path, strlen(package_load_path)));
  
  XPUSHs(sv_package_load_path);
  
  XSRETURN(1);
}

MODULE = SPVM::Build		PACKAGE = SPVM::Build

SV*
create_compiler(...)
  PPCODE:
{
  (void)RETVAL;

  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // Set compiler
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  
  XPUSHs(sv_compiler);
  XSRETURN(1);
}

SV*
compile_spvm(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
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
    // Build portable info
    SPVM_PORTABLE* portable = SPVM_PORTABLE_build_portable(compiler);
    
    // Create run-time
    SPVM_RUNTIME* runtime = SPVM_RUNTIME_BUILDER_build_runtime(portable);
    
    // Set ENV
    SPVM_ENV* env = runtime->env;
    size_t iv_env = PTR2IV(env);
    SV* sviv_env = sv_2mortal(newSViv(iv_env));
    SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
    hv_store(hv_self, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
  }
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
free_compiler(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  XSRETURN(0);
}

MODULE = SPVM::Build::CBuilder::Native		PACKAGE = SPVM::Build::CBuilder::Native

SV*
bind_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_native_sub_name = ST(1);
  SV* sv_native_address = ST(2);

  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

  // Native subroutine name
  const char* native_sub_name = SvPV_nolen(sv_native_sub_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  // Set native address to subroutine
  SPVM_RUNTIME_SUB* runtime_sub = SPVM_HASH_fetch(runtime->sub_symtable, native_sub_name, strlen(native_sub_name));
  runtime->sub_native_addresses[runtime_sub->id] = native_address;
  
  XSRETURN(0);
}

MODULE = SPVM::Build::CBuilder::Precompile		PACKAGE = SPVM::Build::CBuilder::Precompile

SV*
build_package_csource(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  int32_t package_id = package->id;
  
  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // Build package csource
  SPVM_CSOURCE_BUILDER_build_package_csource(runtime, string_buffer, package_name);
  
  SV* sv_package_csource = sv_2mortal(newSVpv(string_buffer->buffer, string_buffer->length));
  
  SPVM_STRING_BUFFER_free(string_buffer);
  
  XPUSHs(sv_package_csource);
  XSRETURN(1);
}

SV*
bind_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_sub_abs_name = ST(1);
  SV* sv_sub_native_address = ST(2);
  
  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  void* sub_precompile_address = INT2PTR(void*, SvIV(sv_sub_native_address));
  
  // Env
  SV** sv_build_ptr = hv_fetch(hv_self, "build", strlen("build"), 0);
  SV* sv_build = sv_build_ptr ? *sv_build_ptr : &PL_sv_undef;
  HV* hv_build = SvRV(sv_build);
  SV** sv_env_ptr = hv_fetch(hv_build, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

  SPVM_RUNTIME_SUB* runtime_sub = SPVM_HASH_fetch(runtime->sub_symtable, sub_abs_name, strlen(sub_abs_name));
  runtime_sub->flag |= SPVM_SUB_C_FLAG_IS_COMPILED;
  runtime->sub_precompile_addresses[runtime_sub->id] = sub_precompile_address;
  
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
  const char* package_name = SvPV_nolen(sv_package_name);
  const char* sub_name = SvPV_nolen(sv_sub_name);

  SPVM_RUNTIME_PACKAGE* runtime_package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (runtime_package == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  SPVM_RUNTIME_SUB* runtime_sub = SPVM_HASH_fetch(runtime_package->sub_symtable, sub_name, strlen(sub_name));
  if (runtime_sub == NULL) {
    croak("Subroutine not found %s %s", package_name, sub_name);
  }
  const char* runtime_sub_signature = runtime->symbols[runtime_sub->signature_id];
  int32_t runtime_sub_id = env->get_sub_id(env, package_name, runtime_sub_signature);
  if (runtime_sub_id < 0) {
    croak("Subroutine not found %s %s", package_name, runtime_sub_signature);
  }

  SPVM_VALUE stack[SPVM_LIMIT_C_STACK_MAX];
  
  int32_t ref_stack_top = 0;
  SPVM_VALUE ref_stack[SPVM_LIMIT_C_STACK_MAX];

  int32_t ref_stack_ids[SPVM_LIMIT_C_STACK_MAX];
  
  // Arguments
  _Bool args_contain_ref = 0;
  {
    // If class method, first argument is ignored
    if (runtime_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD) {
      arg_start++;
    }
    
    int32_t arg_index;
    // Check argument count
    if (items - arg_start != runtime_sub->arg_ids_length) {
      croak("Argument count is defferent");
    }
    
    int32_t arg_var_id = 0;
    for (arg_index = 0; arg_index < runtime_sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_MY* runtime_arg = &runtime->args[runtime_sub->arg_ids_base + arg_index];

      _Bool arg_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      _Bool arg_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      _Bool arg_type_is_ref_type = SPVM_RUNTIME_API_is_ref_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);

      SV* sv_value = ST(arg_index + arg_start);
      
      int32_t arg_basic_type_id = runtime_arg->basic_type_id;
      int32_t arg_type_dimension = runtime_arg->type_dimension;
      int32_t arg_type_flag = runtime_arg->type_flag;

      SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[runtime_arg->basic_type_id];
      
      if (arg_type_is_ref_type) {
        args_contain_ref = 1;
        _Bool arg_type_is_numeric_ref_type = SPVM_RUNTIME_API_is_numeric_ref_type(env, arg_basic_type_id, arg_type_dimension, arg_type_flag);
        _Bool arg_type_is_value_ref_type = SPVM_RUNTIME_API_is_value_ref_type(env, arg_basic_type_id, arg_type_dimension, arg_type_flag);
        
        if (arg_type_is_numeric_ref_type) {
          SV* sv_value_deref = SvRV(sv_value);
          switch (arg_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              int8_t value = (int8_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].bval = value;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              int16_t value = (int16_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].sval = value;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              int32_t value = (int32_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].ival = value;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              int64_t value = (int64_t)SvIV(sv_value_deref);
              ref_stack[ref_stack_top].lval = value;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              float value = (float)SvNV(sv_value_deref);
              ref_stack[ref_stack_top].fval = value;
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              double value = (double)SvNV(sv_value_deref);
              ref_stack[ref_stack_top].dval = value;
              break;
            }
            default:
              assert(0);
          }

          stack[arg_var_id].oval = &ref_stack[ref_stack_top];
          ref_stack_ids[arg_index] = ref_stack_top;

          ref_stack_top++;
          arg_var_id++;
        }
        else if (arg_type_is_value_ref_type) {
          SPVM_RUNTIME_PACKAGE* arg_package = &runtime->packages[arg_basic_type->package_id];
          assert(arg_package);
            
          if (sv_derived_from(sv_value, "REF") && sv_derived_from(SvRV(sv_value), "HASH")) {
            HV* hv_value = (HV*)SvRV(SvRV(sv_value));
            
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
              switch (first_field->basic_type_id) {
                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                  int8_t value = (int8_t)SvIV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].bval = value;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                  int16_t value = (int16_t)SvIV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].sval = value;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_INT: {
                  int32_t value = (int32_t)SvIV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].ival = value;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_LONG: {
                  int64_t value = (int64_t)SvIV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].lval = value;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                  float value = (float)SvNV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].fval = value;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                  double value = (double)SvNV(sv_field_value);
                  ref_stack[ref_stack_top + field_index].dval = value;
                  break;
                }
                default:
                  assert(0);
              }
            }
          }
          else {
            croak("%dth argument must be scalar reference to hash reference", arg_index + 1);
          }

          stack[arg_var_id].oval = &ref_stack[ref_stack_top];

          ref_stack_ids[arg_index] = ref_stack_top;

          int32_t fields_length = arg_package->fields->length;
          ref_stack_top += fields_length;
          arg_var_id++;
        }
        else {
          assert(0);
        }
      }
      else if (arg_type_is_value_type) {
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
            switch (arg_first_field->basic_type_id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                int8_t value = (int8_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].bval = value;
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                int16_t value = (int16_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].sval = value;
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                int32_t value = (int32_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].ival = value;
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                int64_t value = (int64_t)SvIV(sv_field_value);
                stack[arg_var_id + field_index].lval = value;
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                float value = (float)SvNV(sv_field_value);
                stack[arg_var_id + field_index].fval = value;
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                double value = (double)SvNV(sv_field_value);
                stack[arg_var_id + field_index].dval = value;
                break;
              }
              default:
                assert(0);
            }
          }
          arg_var_id += arg_package->fields->length;
        }
        else {
          croak("%dth argument must be hash reference", arg_index + 1);
        }
      }
      else if (arg_type_is_object_type) {
        if (!SvOK(sv_value)) {
          stack[arg_var_id].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::Data")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            _Bool check_cast = env->check_cast(env, arg_basic_type_id, arg_type_dimension, object);
            if (!check_cast) {
              croak("Can't cast %dth argument", arg_index);
            }
            
            stack[arg_var_id].oval = object;
          }
          else {
            croak("%dth argument must be SPVM::Data object", arg_index);
          }
        }
        arg_var_id++;
      }
      else {
        switch (arg_basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE : {
            int8_t value = (int8_t)SvIV(sv_value);
            stack[arg_var_id].bval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_SHORT : {
            int16_t value = (int16_t)SvIV(sv_value);
            stack[arg_var_id].sval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_INT : {
            int32_t value = (int32_t)SvIV(sv_value);
            stack[arg_var_id].ival = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_LONG : {
            int64_t value = (int64_t)SvIV(sv_value);
            stack[arg_var_id].lval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_FLOAT : {
            float value = (float)SvNV(sv_value);
            stack[arg_var_id].fval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_DOUBLE : {
            double value = (double)SvNV(sv_value);
            stack[arg_var_id].dval = value;
            break;
          }
          default:
            assert(0);
        }
        arg_var_id++;
      }
    }
  }
  
  // Return type id
  int32_t sub_return_basic_type_id = runtime_sub->return_basic_type_id;
  int32_t sub_return_type_dimension = runtime_sub->return_type_dimension;
  int32_t sub_return_type_flag = runtime_sub->return_type_flag;
  int32_t sub_return_type_width = SPVM_RUNTIME_API_get_width(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);

  int32_t sub_return_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);
  int32_t sub_return_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag);
  
  // Return count
  SV* sv_return_value = NULL;
  int32_t excetpion_flag;
  if (sub_return_type_is_value_type) {
    excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
    
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
      
      hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
      sv_return_value = sv_2mortal(newRV_inc((SV*)hv_value));
    }
  }
  else if (sub_return_type_is_object_type) {
    excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
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
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].bval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].sval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].ival));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSViv(stack[0].lval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
        if (!excetpion_flag) {
          sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
        }
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        excetpion_flag = env->call_sub(env, runtime_sub_id, stack);
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
    for (int32_t arg_index = 0; arg_index < runtime_sub->arg_ids_length; arg_index++) {
      SV* sv_value = ST(arg_index + arg_start);

      SPVM_RUNTIME_MY* runtime_arg = &runtime->args[runtime_sub->arg_ids_base + arg_index];

      _Bool arg_type_is_value_type = SPVM_RUNTIME_API_is_value_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      _Bool arg_type_is_object_type = SPVM_RUNTIME_API_is_object_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      _Bool arg_type_is_ref_type = SPVM_RUNTIME_API_is_ref_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
      
      int32_t arg_basic_type_id = runtime_arg->basic_type_id;
      int32_t arg_type_dimension = runtime_arg->type_dimension;
      int32_t arg_type_flag = runtime_arg->type_flag;

      SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = &runtime->basic_types[runtime_arg->basic_type_id];

      if (arg_type_is_ref_type) {
        int32_t ref_stack_id = ref_stack_ids[arg_index];
        
        _Bool arg_type_is_numeric_ref_type = SPVM_RUNTIME_API_is_numeric_ref_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
        _Bool arg_type_is_value_ref_type = SPVM_RUNTIME_API_is_value_ref_type(env, runtime_arg->basic_type_id, runtime_arg->type_dimension, runtime_arg->type_flag);
        
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
                sv_field_value = sv_2mortal(newSViv(ref_stack[ref_stack_id + field_index].bval));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                sv_field_value = sv_2mortal(newSViv(ref_stack[ref_stack_id + field_index].sval));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                sv_field_value = sv_2mortal(newSViv(ref_stack[ref_stack_id + field_index].ival));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                sv_field_value = sv_2mortal(newSViv(ref_stack[ref_stack_id + field_index].lval));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                sv_field_value = sv_2mortal(newSVnv(ref_stack[ref_stack_id + field_index].fval));
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                sv_field_value = sv_2mortal(newSVnv(ref_stack[ref_stack_id + field_index].dval));
                break;
              }
              default:
                assert(0);
            }
            hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
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
    croak("%s", SvPV_nolen(sv_exception));
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
          
          int32_t check_cast = env->check_cast(env, array_basic_type_id, element_type_dimension, object);
          
          if (check_cast) {
            env->set_object_array_element(env, array, index, object);
          }
          else {
            croak("Element must be cast");
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
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
        
        int32_t check_cast = env->check_cast(env, basic_type_id, element_type_dimension, object);
        
        if (check_cast) {
          env->set_object_array_element(env, array, index, object);
        }
        else {
          croak("Element must be cast");
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);
  
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

  SV* sv_value;
  _Bool is_object = 0;
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
        hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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
          hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
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
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)env->get_runtime(env);

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

MODULE = SPVM		PACKAGE = SPVM

