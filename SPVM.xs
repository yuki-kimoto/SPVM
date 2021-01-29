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

#include "spvm_api.h"

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
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
#include "spvm_compiler_allocator.h"
#include "spvm_my.h"

static const char* MFILE = "SPVM.xs";

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

MODULE = SPVM::BlessedObject		PACKAGE = SPVM::BlessedObject

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
create_compiler(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  (void)hv_store(hv_self, "compiler", strlen("compiler"), SvREFCNT_inc(sv_compiler), 0);
}

SV*
compile_spvm(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_name = ST(1);
  SV* sv_file = ST(2);
  SV* sv_line = ST(3);
  
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  
  // Include directries
  SV** sv_include_dirs_ptr = hv_fetch(hv_self, "include_dirs", strlen("include_dirs"), 0);
  SV* sv_include_dirs = sv_include_dirs_ptr ? *sv_include_dirs_ptr : &PL_sv_undef;
  
  // Name
  const char* name = SvPV_nolen(sv_name);
  char* name_copy = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sv_len(sv_name) + 1);
  memcpy(name_copy, name, sv_len(sv_name));
  
  // File
  const char* file = SvPV_nolen(sv_file);
  char* file_copy = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sv_len(sv_file) + 1);
  memcpy(file_copy, file, sv_len(sv_file));
  
  // Line
  int32_t line = (int32_t)SvIV(sv_line);
  
  // push package to compiler use stack
  SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, name_copy, file_copy, line);
  SPVM_OP* op_type_package = SPVM_OP_build_basic_type(compiler, op_name_package);
  SPVM_OP* op_use_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file_copy, line);
  SPVM_OP_build_use(compiler, op_use_package, op_type_package, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_package);
  
  // Add include paths
  AV* av_include_dirs;
  if (SvOK(sv_include_dirs)) {
    av_include_dirs = (AV*)SvRV(sv_include_dirs);
  }
  else {
    av_include_dirs = (AV*)sv_2mortal((SV*)newAV());
  }
  int32_t av_include_dirs_length = (int32_t)av_len(av_include_dirs) + 1;
  for (int32_t i = 0; i < av_include_dirs_length; i++) {
    SV** sv_include_dir_ptr = av_fetch(av_include_dirs, i, 0);
    SV* sv_include_dir = sv_include_dir_ptr ? *sv_include_dir_ptr : &PL_sv_undef;
    char* include_dir = SvPV_nolen(sv_include_dir);
    SPVM_LIST_push(compiler->module_include_dirs, include_dir);
  }

  // Compile SPVM
  compiler->cur_package_base = compiler->packages->length;
  SPVM_COMPILER_compile(compiler);

  SV* sv_compile_success;
  if (compiler->error_count > 0) {
    sv_compile_success = sv_2mortal(newSViv(0));
  }
  else {
    sv_compile_success = sv_2mortal(newSViv(1));
  }
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
get_precompile_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_precompile_sub_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_precompile_sub_names = sv_2mortal(newRV_inc((SV*)av_precompile_sub_names));
  
  // Copy package load path to builder
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));

  for (int32_t sub_index = 0; sub_index < package->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
    if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
      const char* sub_name = sub->name;
      SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, 0));
      av_push(av_precompile_sub_names, SvREFCNT_inc(sv_sub_name));
    }
  }
  
  XPUSHs(sv_precompile_sub_names);
  XSRETURN(1);
}

SV*
get_native_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_native_sub_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_native_sub_names = sv_2mortal(newRV_inc((SV*)av_native_sub_names));
  
  // Copy package load path to builder
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));

  for (int32_t sub_index = 0; sub_index < package->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
    if (sub->flag & SPVM_SUB_C_FLAG_NATIVE) {
      const char* sub_name = sub->name;
      SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, 0));
      av_push(av_native_sub_names, SvREFCNT_inc(sv_sub_name));
    }
  }
  
  XPUSHs(sv_native_sub_names);
  XSRETURN(1);
}

SV*
get_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_sub_names = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  // Copy package load path to builder
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));

  for (int32_t sub_index = 0; sub_index < package->subs->length; sub_index++) {
    SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, sub_index);
    const char* sub_name = sub->name;
    SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, 0));
    av_push(av_sub_names, SvREFCNT_inc(sv_sub_name));
  }
  
  XPUSHs(sv_sub_names);
  XSRETURN(1);
}

SV*
get_package_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_package_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_package_names = sv_2mortal(newRV_inc((SV*)av_package_names));
  
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    const char* package_name = package->name;
    SV* sv_package_name = sv_2mortal(newSVpv(package_name, 0));
    av_push(av_package_names, SvREFCNT_inc(sv_package_name));
  }
  
  XPUSHs(sv_package_names);
  XSRETURN(1);
}

SV*
get_added_package_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_added_package_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_added_package_names = sv_2mortal(newRV_inc((SV*)av_added_package_names));
  
  for (int32_t added_package_index = 0; added_package_index < compiler->added_packages->length; added_package_index++) {
    SPVM_PACKAGE* added_package = SPVM_LIST_fetch(compiler->added_packages, added_package_index);
    const char* added_package_name = added_package->name;
    SV* sv_added_package_name = sv_2mortal(newSVpv(added_package_name, 0));
    av_push(av_added_package_names, SvREFCNT_inc(sv_added_package_name));
  }
  
  XPUSHs(sv_added_package_names);
  XSRETURN(1);
}

SV*
get_module_file(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Copy package load path to builder
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));
  const char* module_file = package->module_file;
  SV* sv_module_file = sv_2mortal(newSVpv(module_file, 0));

  XPUSHs(sv_module_file);
  XSRETURN(1);
}

SV*
get_module_source(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Copy package load path to builder
  SV* sv_module_source;
  const char* module_source = SPVM_HASH_fetch(compiler->module_source_symtable, package_name, strlen(package_name));
  if (module_source) {
    sv_module_source = sv_2mortal(newSVpv(module_source, 0));
  }
  else {
    sv_module_source = &PL_sv_undef;
  }

  XPUSHs(sv_module_source);
  XSRETURN(1);
}

SV*
get_loaded_module_file(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_package_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Name
  const char* package_name = SvPV_nolen(sv_package_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Copy package load path to builder
  SV* sv_loaded_module_file;
  const char* loaded_module_file = SPVM_HASH_fetch(compiler->loaded_module_file_symtable, package_name, strlen(package_name));
  if (loaded_module_file) {
    sv_loaded_module_file = sv_2mortal(newSVpv(loaded_module_file, 0));
  }
  else {
    sv_loaded_module_file = &PL_sv_undef;
  }

  XPUSHs(sv_loaded_module_file);
  XSRETURN(1);
}

SV*
_init(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Create env
  SPVM_ENV* env = SPVM_API_create_env(compiler);
  if (env == NULL) {
    croak("Can't create SPVM env");
  }
  
  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  (void)hv_store(hv_self, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
  
  SPVM_API_call_begin_blocks(env);
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
  
  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  // Basic type
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, package_name, strlen(package_name));
  
  // Package name
  SPVM_PACKAGE* package = basic_type->package;

  SPVM_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  sub->precompile_address = sub_precompile_address;
  
  XSRETURN(0);
}

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

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Package name
  const char* package_name = SvPV_nolen(sv_package_name);

  // Subroutine name
  const char* sub_name = SvPV_nolen(sv_sub_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  // Basic type
  SPVM_BASIC_TYPE* basic_type = (SPVM_BASIC_TYPE*)SPVM_HASH_fetch(compiler->basic_type_symtable, package_name, strlen(package_name));
  
  // Package name
  SPVM_PACKAGE* package = basic_type->package;
  
  // Set native address to subroutine
  SPVM_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  sub->native_address = native_address;
  
  XSRETURN(0);
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
    SPVM_COMPILER* compiler = env->compiler;
    
    SPVM_API_free_env(env);
  }
}

MODULE = SPVM::Builder::CC		PACKAGE = SPVM::Builder::CC

SV*
build_package_csource_precompile(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_package_name = ST(1);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Env
  SV** sv_builder_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_builder = sv_builder_ptr ? *sv_builder_ptr : &PL_sv_undef;
  HV* hv_builder = (HV*)SvRV(sv_builder);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_builder, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);

  // Build package csource
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_package_csource(compiler, string_buffer, package_name);
  
  SV* sv_package_csource = sv_2mortal(newSVpv(string_buffer->buffer + 1, string_buffer->length - 1));
  
  SPVM_STRING_BUFFER_free(string_buffer);

  XPUSHs(sv_package_csource);
  XSRETURN(1);
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
new_string_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);

  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_string_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }

    AV* av_elems = (AV*)SvRV(sv_elems);

    int32_t length = av_len(av_elems) + 1;

    // New array
    SPVM_OBJECT* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_STRING, length);

    for (int32_t i = 0; i < length; i++) {
      SV** sv_str_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_str_value = sv_str_value_ptr ? *sv_str_value_ptr : &PL_sv_undef;
      if (SvOK(sv_str_value)) {
        // Copy
        sv_str_value = sv_2mortal(newSVsv(sv_str_value));
        
        // Encode to UTF-8
        sv_utf8_encode(sv_str_value);
        
        int32_t length = sv_len(sv_str_value);
        const char* chars = SvPV_nolen(sv_str_value);
        
        void* string = env->new_string_raw(env, chars, length);
        env->set_elem_object(env, array, i, string);
      }
      else {
        env->set_elem_object(env, array, i, NULL);
      }
    }

    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_byte_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_byte_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int8_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_byte_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_byte_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint8_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_byte_array(env, length);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
new_byte_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length;
    int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_byte_array(env, array_length);

    int8_t* elems = env->get_elems_byte(env, array);
    memcpy(elems, binary, array_length);
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_value = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_value)) {
    
    if (SvROK(sv_value)) {
      croak("Argument must not be reference at %s line %d\n", MFILE, __LINE__);
    }
    else {
      // Environment
      SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
      
      // Copy
      SV* sv_value_tmp = sv_2mortal(newSVsv(sv_value));
      
      // Encode to UTF-8
      sv_utf8_encode(sv_value_tmp);
      
      int32_t length = sv_len(sv_value_tmp);
      
      const char* value = SvPV_nolen(sv_value_tmp);
      
      void* string = env->new_string(env, value, length);
      
      sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
new_string_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_binary)) {
    if (SvROK(sv_binary)) {
      croak("Argument must not be reference at %s line %d\n", MFILE, __LINE__);
    }
    else {
      int32_t binary_length = sv_len(sv_binary);
      int32_t string_length = binary_length;
      int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
      
      // Environment
      SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
      
      // New string
      void* string = env->new_string(env, (const char*)binary, string_length);

      const char* chars = env->get_chars(env, string);
      memcpy((char*)chars, binary, string_length);
      
      // New sv string
      sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
new_short_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_short_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_short_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int16_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_short_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_short_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_short_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint16_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_short_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_short_array(env, length);
  
  // New sv array
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
new_short_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int16_t);
    int16_t* binary = (int16_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_short_array(env, array_length);

    int16_t* elems = env->get_elems_short(env, array);
    memcpy(elems, binary, array_length * sizeof(int16_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_int_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_int_array(env, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int32_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_int_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_int_array(env, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint32_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_int_array(env, length);
  
  // New sv array
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
new_int_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int32_t);
    int32_t* binary = (int32_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_int_array(env, array_length);

    int32_t* elems = env->get_elems_int(env, array);
    memcpy(elems, binary, array_length * sizeof(int32_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_long_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_long_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int64_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_long_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_long_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint64_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_long_array(env, length);
  
  // New sv array
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
new_long_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int64_t);
    int64_t* binary = (int64_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_long_array(env, array_length);

    int64_t* elems = env->get_elems_long(env, array);
    memcpy(elems, binary, array_length * sizeof(int64_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_float_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_float_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_float_array(env, length);

    float* elems = env->get_elems_float(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (float)SvNV(sv_value);
    }
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_float_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_float_array(env, length);
  
  // New sv array
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
new_float_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(float);
    float* binary = (float*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_float_array(env, array_length);

    float* elems = env->get_elems_float(env, array);
    memcpy(elems, binary, array_length * sizeof(float));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_double_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_double_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_double_array(env, length);

    double* elems = env->get_elems_double(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (double)SvNV(sv_value);
    }
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_double_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_double_array(env, length);
  
  // New sv array
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
new_double_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(double);
    double* binary = (double*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_double_array(env, array_length);

    double* elems = env->get_elems_double(env, array);
    memcpy(elems, binary, array_length * sizeof(double));
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_string_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = "string";
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  void* array = env->new_object_array(env, basic_type->id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
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

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  void* array = env->new_object_array(env, basic_type->id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_object_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Second argument of SPVM::new_object_array must be array reference at %s line %d\n", MFILE, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_object_array(env, basic_type->id, length);

  int32_t array_basic_type_id  = array->basic_type_id;
  int32_t array_type_dimension = array->type_dimension;
  int32_t element_type_dimension = array_type_dimension - 1;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject::Package")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_elem_object(env, array, index, object);
      }
      else {
        croak("Element is invalid object type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else {
      croak("Element must be SPVM::BlessedObject object at %s line %d\n", MFILE, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_muldim_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_element_type_dimension = ST(2);
  SV* sv_elems = ST(3);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference at %s line %d\n", MFILE, __LINE__);
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  int32_t element_type_dimension = (int32_t)SvIV(sv_element_type_dimension);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_muldim_array(env, basic_type->id, element_type_dimension, length);
  
  int32_t array_basic_type_id = array->basic_type_id;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_elem_object(env, array, index, object);
      }
      else {
        croak("Element is invalid object type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else {
      croak("Element must be inherit SPVM::BlessedObject object at %s line %d\n", MFILE, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_mulnum_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference at %s line %d\n", MFILE, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    croak("Not found %s at %s line %d\n", basic_type_name, MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_mulnum_array(env, basic_type->id, length);

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;

    if (sv_derived_from(sv_element, "HASH")) {
      
      SPVM_PACKAGE* package = basic_type->package;
      assert(package);
      
      SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      assert(first_field);

      void* elems = (void*)env->get_elems_int(env, array);
      
      HV* hv_value = (HV*)SvRV(sv_element);
      int32_t fields_length = package->fields->length;
      // Field exists check
      int32_t hash_keys_length = 0;
      while (hv_iternext(hv_value)) {
        hash_keys_length++;
      }
      if (hash_keys_length != fields_length) {
        croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
      }

      for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
        const char* field_name = field->name;
        
        SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
        SV* sv_field_value;
        if (sv_field_value_ptr) {
          sv_field_value = *sv_field_value_ptr;
        }
        else {
          croak("Value element must be defined at %s line %d\n", MFILE, __LINE__);
        }

        switch (first_field->type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            ((int8_t*)elems)[(fields_length * index) + field_index] = (int8_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            ((int16_t*)elems)[(fields_length * index) + field_index] = (int16_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            ((int32_t*)elems)[(fields_length * index) + field_index] = (int32_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            ((int64_t*)elems)[(fields_length * index) + field_index] = (int64_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            ((float*)elems)[(fields_length * index) + field_index] = (float)SvNV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            ((double*)elems)[(fields_length * index) + field_index] = (double)SvNV(sv_field_value);
            break;
          }
          default:
            assert(0);
        }
      }
    }
    else {
      croak("Element must be hash reference at %s line %d\n", MFILE, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_mulnum_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_binary = ST(2);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* binary = (void*)SvPV_nolen(sv_binary);
  
  int32_t binary_length = sv_len(sv_binary);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    const char* basic_type_name = basic_type->name;
    croak("Can't load %s at %s line %d\n", basic_type_name, MFILE, __LINE__);
  }

  SPVM_PACKAGE* package = basic_type->package;
  assert(package);
  
  SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
  assert(first_field);

  int32_t field_length = package->fields->length;

  int32_t array_length;
  
  
  int32_t field_width;
  switch (first_field->type->basic_type->id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      field_width = 1;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      field_width = 2;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      field_width = 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      field_width = 8;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      field_width = 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      field_width = 8;
      break;
    }
    default:
      croak("Unexpected error:set field width");
  }
  
  if (binary_length % (field_length * field_width) != 0) {
    croak("Invalid binary data size at %s line %d", MFILE, __LINE__);
  }
  
  array_length = binary_length / field_length / field_width;

  SPVM_OBJECT* array = env->new_mulnum_array(env, basic_type->id, array_length);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  
  switch (first_field->type->basic_type->id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      int8_t* elems = env->get_elems_byte(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      int16_t* elems = env->get_elems_short(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      int32_t* elems = env->get_elems_int(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      int64_t* elems = env->get_elems_long(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      float* elems = env->get_elems_float(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      double* elems = env->get_elems_double(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    default:
      assert(0);
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_get_exception(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  void* str_exception = env->get_exception(env);
  
  SV* sv_exception;
  if (str_exception) {
    const char* exception_chars = env->get_chars(env, str_exception);
    int32_t length = env->length(env, str_exception);
    
    sv_exception = sv_2mortal(newSVpv(exception_chars, length));
  }
  else {
    sv_exception = &PL_sv_undef;
  }
  
  XPUSHs(sv_exception);
  XSRETURN(1);
}

SV*
_set_exception(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_exception = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  if (SvOK(sv_exception)) {
    const char* exception = SvPV_nolen(sv_exception);
    int32_t length = (int32_t)sv_len(sv_exception);
    
    void* str_exception = env->new_string_raw(env, exception, length);
    env->set_exception(env, str_exception);
  }
  else {
    env->set_exception(env, NULL);
  }
  
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
  
  // Arguments
  SV* sv_env = ST(0);
  SV* sv_package_name = ST(1);
  SV* sv_sub_name = ST(2);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  // Package Name
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // Sub name
  const char* sub_name = SvPV_nolen(sv_sub_name);

  // Basic type
  SPVM_BASIC_TYPE* basic_type = SPVM_API_basic_type(env, package_name);
  
  // Package
  SPVM_PACKAGE* package = basic_type->package;
  
  // Subroutine not found
  int32_t sub_not_found;
  SPVM_SUB* sub = NULL;
  if (package == NULL) {
    sub_not_found = 1;
  }
  else {
    sub = SPVM_API_sub(env, package, sub_name);
    if (sub == NULL) {
      sub_not_found = 1;
    }
    else {
      sub_not_found = 0;
    }
  }
  if (sub_not_found) {
    croak("%s->%s method not found at %s line %d\n", package_name, sub_name, MFILE, __LINE__);
  }
  
  // Argument stack
  SPVM_VALUE stack[SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT];
  
  // Reference stack
  int32_t ref_stack_top = 0;
  SPVM_VALUE ref_stack[SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT];
  int32_t ref_stack_ids[SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT];

  // Base index of SPVM arguments
  int32_t spvm_args_base = 3;

  // If class method, first argument is ignored
  if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_STATIC_METHOD) {
    spvm_args_base++;
  }
  
  // Check argument count
  if (items - spvm_args_base < sub->args->length) {
    croak("Too few arguments %s->%s at %s line %d\n", package_name, sub_name, MFILE, __LINE__);
  }
  else if (items - spvm_args_base > sub->args->length) {
    croak("Too many arguments %s->%s at %s line %d\n", package_name, sub_name, MFILE, __LINE__);
  }
  
  // If Argument contains reference type, this value become 1
  int32_t args_contain_ref = 0;
  
  // In SPVM, argument index is different from value offset because multi numeric type have width.
  int32_t arg_values_offset = 0;

  // Arguments
  for (int32_t arg_index = 0; arg_index < sub->args->length; arg_index++) {
    
    // Get value from Perl argument stack
    SV* sv_value = ST(spvm_args_base + arg_index);
    
    // Argument information
    SPVM_MY* arg = SPVM_LIST_fetch(sub->args, arg_index);
    int32_t arg_basic_type_id = arg->type->basic_type->id;
    int32_t arg_type_dimension = arg->type->dimension;
    
    // Process argument corresponding to the type category
    switch (arg->type_category) {
      case SPVM_TYPE_C_TYPE_CATEGORY_BYTE : {
        int8_t value = (int8_t)SvIV(sv_value);
        stack[arg_values_offset].bval = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_SHORT : {
        int16_t value = (int16_t)SvIV(sv_value);
        stack[arg_values_offset].sval = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_INT : {
        int32_t value = (int32_t)SvIV(sv_value);
        stack[arg_values_offset].ival = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_LONG : {
        int64_t value = (int64_t)SvIV(sv_value);
        stack[arg_values_offset].lval = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_FLOAT : {
        float value = (float)SvNV(sv_value);
        stack[arg_values_offset].fval = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE : {
        double value = (double)SvNV(sv_value);
        stack[arg_values_offset].dval = value;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_STRING: {
        // Perl value is undef
        if (!SvOK(sv_value)) {
          stack[arg_values_offset].oval = NULL;
        }
        else {
          // If Perl value is non ref scalar, the value is converted to string object
          if (!SvROK(sv_value)) {
          
            // Copy
            SV* sv_value_tmp = sv_2mortal(newSVsv(sv_value));
            
            // Encode to UTF-8
            sv_utf8_encode(sv_value_tmp);
            
            int32_t length = sv_len(sv_value_tmp);
            const char* chars = SvPV_nolen(sv_value_tmp);
            
            void* string = env->new_string(env, chars, length);
            
            SV* sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
            
            sv_value = sv_string;
          }
          
          // Check type
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
              croak("%dth argument of %s->%s() is invalid object type at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
            }
            
            stack[arg_values_offset].oval = object;
          }
          else {
            croak("%dth argument of %s->%s() must be inherit SPVM::BlessedObject at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
          }
        }
        arg_values_offset++;
        break;
      }
      // Array Object type
      case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
      case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
      {
        // Perl value is undef
        if (!SvOK(sv_value)) {
          stack[arg_values_offset].oval = NULL;
        }
        else {
          // Perl value is array refence
          if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
            
            SV* sv_elems = sv_value;
            
            AV* av_elems = (AV*)SvRV(sv_elems);
            
            int32_t length = av_len(av_elems) + 1;
            
            if (arg_type_dimension == 1) {
              switch (arg_basic_type_id) {
                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                  // New array
                  void* array = env->new_byte_array(env, length);

                  int8_t* elems = env->get_elems_byte(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int8_t)SvIV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                  // New array
                  void* array = env->new_short_array(env, length);

                  int16_t* elems = env->get_elems_short(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int16_t)SvIV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_INT: {
                  
                  // New array
                  void* array = env->new_int_array(env, length);
                  
                  int32_t* elems = env->get_elems_int(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int32_t)SvIV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_LONG: {
                  // New array
                  void* array = env->new_long_array(env, length);

                  int64_t* elems = env->get_elems_long(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int64_t)SvIV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                  // New array
                  void* array = env->new_float_array(env, length);

                  float* elems = env->get_elems_float(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (float)SvNV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                  // New array
                  void* array = env->new_double_array(env, length);

                  double* elems = env->get_elems_double(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (double)SvNV(sv_value);
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_STRING: {
                  // New array
                  void* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_STRING, length);
                  
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;

                    // Perl value is undef
                    if (!SvOK(sv_value)) {
                      env->set_elem_object(env, array, i, NULL);
                    }
                    else {
                      // If Perl value is non ref scalar, the value is converted to string object
                      if (!SvROK(sv_value)) {
                      
                        // Copy
                        SV* sv_value_tmp = sv_2mortal(newSVsv(sv_value));
                        
                        // Encode to UTF-8
                        sv_utf8_encode(sv_value_tmp);
                        
                        int32_t length = sv_len(sv_value_tmp);
                        const char* chars = SvPV_nolen(sv_value_tmp);
                        
                        void* string = env->new_string(env, chars, length);
                        
                        SV* sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
                        
                        sv_value = sv_string;
                      }
                      
                      // Check type
                      if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
                        SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
                        
                        if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
                          croak("%dth argument of %s->%s() is invalid object type at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
                        }
                        
                        env->set_elem_object(env, array, i, object);
                      }
                      else {
                        croak("%dth argument of %s->%s() must be inherit SPVM::BlessedObject at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
                      }
                    }
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  
                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_ANY_OBJECT: {
                  // New array
                  void* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT, length);

                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    if (SvOK(sv_value)) {
                      
                      // Convert non-ref scalar to byte[]
                      if (!SvROK(sv_value)) {
                        // Copy
                        sv_value = sv_2mortal(newSVsv(sv_value));
                        
                        // Encode to UTF-8
                        sv_utf8_encode(sv_value);
                        
                        int32_t length = sv_len(sv_value);
                        const char* chars = SvPV_nolen(sv_value);
                        
                        void* string = env->new_string_raw(env, chars, length);
                        env->inc_ref_count(env, string);
                        
                        sv_value = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::Array");
                      }
                      
                      if (!sv_derived_from(sv_value, "SPVM::BlessedObject")) {
                        croak("Element of %dth argument of %s->%s() must inherit SPVM::BlessedObject object at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
                      }
                      
                      env->set_elem_object(env, array, i, SPVM_XS_UTIL_get_object(sv_value));
                    }
                    else {
                      env->set_elem_object(env, array, i, NULL);
                    }
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                default:
                  assert(0);
              }
            }
          }
          
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            if (arg_basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY) {
              if (object->type_dimension == 0) {
                croak("%dth argument of %s->%s() is invalid object type at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
              }
            }
            else {
              if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
                croak("%dth argument of %s->%s() is invalid object type at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
              }
            }
            
            stack[arg_values_offset].oval = object;
          }
          else {
            croak("%dth argument of %s->%s() must be inherit SPVM::BlessedObject at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
          }
        }
        
        arg_values_offset++;
        break;
      }
      // Object type except array object
      case SPVM_TYPE_C_TYPE_CATEGORY_PACKAGE:
      case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
      {
        // Perl value is undef
        if (!SvOK(sv_value)) {
          stack[arg_values_offset].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            assert(arg_type_dimension == 0);
            if (arg_basic_type_id != SPVM_BASIC_TYPE_C_ID_ANY_OBJECT) {
              if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
                croak("%dth argument of %s->%s() is invalid object type at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
              }
            }
            
            stack[arg_values_offset].oval = object;
          }
          else {
            croak("%dth argument of %s->%s() must be inherit SPVM::BlessedObject at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
          }
        }
        
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            int8_t value = (int8_t)SvIV(sv_field_value);
            stack[arg_values_offset + field_index].bval = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }
          
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            int16_t value = (int16_t)SvIV(sv_field_value);
            stack[arg_values_offset + field_index].sval = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }

          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            int32_t value = (int32_t)SvIV(sv_field_value);
            stack[arg_values_offset + field_index].ival = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            int64_t value = (int64_t)SvIV(sv_field_value);
            stack[arg_values_offset + field_index].lval = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            float value = (float)SvNV(sv_field_value);
            stack[arg_values_offset + field_index].fval = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE: {
        if (sv_derived_from(sv_value, "HASH")) {
          HV* hv_value = (HV*)SvRV(sv_value);

          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);

          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          
          int32_t fields_length = arg_package->fields->length;
          // Field exists check
          int32_t hash_keys_length = 0;
          while (hv_iternext(hv_value)) {
            hash_keys_length++;
          }
          if (hash_keys_length != fields_length) {
            croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
          }
          
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;

            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              sv_field_value = &PL_sv_undef;
            }
            double value = (double)SvNV(sv_field_value);
            stack[arg_values_offset + field_index].dval = value;
          }
          arg_values_offset += arg_package->fields->length;
        }
        else {
          croak("%dth argument of %s->%s() must be hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int8_t value = (int8_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_top].bval = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int16_t value = (int16_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_top].sval = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_INT: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int32_t value = (int32_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_top].ival = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int64_t value = (int64_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_top].lval = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        float value = (float)SvNV(sv_value_deref);
        ref_stack[ref_stack_top].fval = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE: {
        args_contain_ref = 1;
        if (!SvROK(sv_value)) {
          croak("%dth argument of %s->%s() must be scalar reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        double value = (double)SvNV(sv_value_deref);
        ref_stack[ref_stack_top].dval = value;
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top++;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        
        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);
        
        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          int8_t value = (int8_t)SvIV(sv_field_value);
          ((int8_t*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        
        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);
        
        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          int16_t value = (int16_t)SvIV(sv_field_value);
          ((int16_t*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }
        
        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);

        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          int32_t value = (int32_t)SvIV(sv_field_value);
          ((int32_t*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }

        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);

        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          int64_t value = (int64_t)SvIV(sv_field_value);
          ((int64_t*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }

        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);

        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          float value = (float)SvNV(sv_field_value);
          ((float*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE: {
        args_contain_ref = 1;
        int32_t is_hash_ref_ref;
        HV* hv_value;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              is_hash_ref_ref = 1;
              hv_value = (HV*)SvRV(hv_value_ref);
            }
            else {
              is_hash_ref_ref = 0;
            }
          }
          else {
            is_hash_ref_ref = 0;
          }
        }
        else {
          is_hash_ref_ref = 0;
        }
        if (!is_hash_ref_ref) {
          croak("%dth argument of %s->%s() must be scalar reference to hash reference at %s line %d\n", arg_index + 1, package_name, sub_name, MFILE, __LINE__);
        }

        SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);

        SPVM_PACKAGE* arg_package = arg_basic_type->package;
        assert(arg_package);
    
        SPVM_FIELD* first_field = SPVM_LIST_fetch(arg_package->fields, 0);
        assert(first_field);

        int32_t fields_length = arg_package->fields->length;
        // Field exists check
        int32_t hash_keys_length = 0;
        while (hv_iternext(hv_value)) {
          hash_keys_length++;
        }
        if (hash_keys_length != fields_length) {
          croak("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__);
        }
        
        for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
          const char* field_name = field->name;

          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            sv_field_value = &PL_sv_undef;
          }
          double value = (double)SvNV(sv_field_value);
          ((double*)&ref_stack[ref_stack_top])[field_index] = value;
        }
        stack[arg_values_offset].oval = &ref_stack[ref_stack_top];
        ref_stack_ids[arg_index] = ref_stack_top;
        ref_stack_top += fields_length;
        arg_values_offset++;
        break;
      }
      default:
        assert(0);
    }
  }
  
  // Return

  int32_t sub_return_basic_type_id = sub->return_type->basic_type->id;
  int32_t sub_return_type_dimension = sub->return_type->dimension;

  SV* sv_return_value = NULL;
  int32_t excetpion_flag = 0;
  switch (sub->return_type_category) {
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE:
    {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      
      SPVM_BASIC_TYPE* sub_return_basic_type = SPVM_LIST_fetch(compiler->basic_types, sub_return_basic_type_id);

      SPVM_PACKAGE* sub_return_package = sub_return_basic_type->package;
      assert(sub_return_package);
      
      SPVM_FIELD* sub_return_first_field = SPVM_LIST_fetch(sub_return_package->fields, 0);
      assert(sub_return_first_field);
      
      HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
      for (int32_t field_index = 0; field_index < sub_return_package->fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_fetch(sub_return_package->fields, field_index);
        const char* field_name = field->name;
        
        SV* sv_field_value = NULL;
        switch (sub_return_first_field->type->basic_type->id) {
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
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_PACKAGE:
    {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        void* return_value = stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          SPVM_BASIC_TYPE* sub_return_basic_type = SPVM_LIST_fetch(compiler->basic_types, env->get_object_basic_type_id(env, return_value));
          const char* basic_type_name = sub_return_basic_type->name;

          SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
          
          sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, SvPV_nolen(sv_basic_type_name));
        }
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
    {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        void* return_value = stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::BlessedObject::Array");
        }
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_STRING: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        void* return_value = stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::BlessedObject::String");
        }
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
    {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        SPVM_OBJECT* return_value = (SPVM_OBJECT*)stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          if (return_value->type_dimension > 0) {
            sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::BlessedObject::Array");
          }
          else {
            
            if (return_value->basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING) {
              const char* chars = env->get_chars(env, return_value);
              int32_t length = env->length(env, return_value);
              
              sv_return_value = sv_2mortal(newSVpv(chars, length));
              
              sv_utf8_decode(sv_return_value);
              
              env->dec_ref_count(env, return_value);
            }
            else {
              SPVM_BASIC_TYPE* sub_return_basic_type = SPVM_LIST_fetch(compiler->basic_types, return_value->basic_type_id);
              const char* basic_type_name = sub_return_basic_type->name;
              SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
              sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, SvPV_nolen(sv_basic_type_name));
            }
          }
        }
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_VOID: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_BYTE: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].bval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_SHORT: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].sval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_INT: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].ival));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_LONG: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(stack[0].lval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_FLOAT: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(stack[0].fval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE: {
      excetpion_flag = env->call_sub(env, sub->id, stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(stack[0].dval));
      }
      break;
    }
    default:
      assert(0);
  }

  // Restore reference value
  if (args_contain_ref) {
    for (int32_t arg_index = 0; arg_index < sub->args->length; arg_index++) {
      SV* sv_value = ST(spvm_args_base + arg_index);
      
      SPVM_MY* arg = SPVM_LIST_fetch(sub->args, arg_index);
      
      // Convert to runtime type
      int32_t arg_basic_type_id = arg->type->basic_type->id;
      int32_t arg_type_dimension = arg->type->dimension;

      int32_t ref_stack_id = ref_stack_ids[arg_index];
      switch (arg->type_category) {
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].bval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].sval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_INT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].ival);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_id].lval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_id].fval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_id].dval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int8_t*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int16_t*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int32_t*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int64_t*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSVnv(((float*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE: {
          SPVM_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_PACKAGE* arg_package = arg_basic_type->package;
          assert(arg_package);
          SPVM_FIELD* arg_first_field = SPVM_LIST_fetch(arg_package->fields, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(arg_package->fields, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSVnv(((double*)&ref_stack[ref_stack_id])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
      }
    }
  }
  
  // Exception
  if (excetpion_flag) {
    void* exception = env->get_exception(env);
    int32_t length = env->length(env, exception);
    const char* exception_chars = env->get_chars(env, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_chars, length));
    croak("%s\n at %s line %d\n", SvPV_nolen(sv_exception), MFILE, __LINE__);
  }
  // Success
  else {
    int32_t return_count;
    if (sub->return_type_category == SPVM_TYPE_C_TYPE_CATEGORY_VOID) {
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
array_to_elems(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Array must be SPVM::BlessedObject::Array object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    int32_t element_type_dimension = dimension - 1;

    if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY) {
      
      for (int32_t index = 0; index < length; index++) {
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, array->basic_type_id);
        
        SPVM_PACKAGE* package = basic_type->package;
        assert(package);
        
        SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
        assert(first_field);

        void* elems = (void*)env->get_elems_int(env, array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t field_length = package->fields->length;
        for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
          const char* field_name = field->name;

          SV* sv_field_value;
          switch (first_field->type->basic_type->id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              int8_t field_value = ((int8_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              int16_t field_value = ((int16_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              int32_t field_value = ((int32_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              int64_t field_value = ((int64_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              float field_value = ((float*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              double field_value = ((double*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            default:
              croak("Unexpected error: set field value");
          }
          SvREFCNT_inc(sv_field_value);
          (void)hv_store(hv_value, field_name, strlen(field_name), sv_field_value, 0);
        }
        SV* sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY) {
      if (basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING) {
        for (int32_t i = 0; i < length; i++) {
          void* object = env->get_elem_object(env, array, i);
          
          SV* sv_value;
          if (object != NULL) {
            const char* string_chars = env->get_chars(env, object);
            int32_t length = env->length(env, object);
            
            sv_value = sv_2mortal(newSVpv(string_chars, length));
            
            sv_utf8_decode(sv_value);
          }
          else {
            sv_value = &PL_sv_undef;
          }
          
          av_push(av_values, SvREFCNT_inc(sv_value));
        }
      }
      else {
        for (int32_t index = 0; index < length; index++) {
          // Element type id
          SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, array->basic_type_id);

          // Index
          SPVM_OBJECT* value = env->get_elem_object(env, array, index);
          if (value == NULL) {
            av_push(av_values, &PL_sv_undef);
          }
          else {
            env->inc_ref_count(env, value);
            int32_t element_type_is_array_type = element_type_dimension > 0;
            SV* sv_value;
            if (element_type_is_array_type) {
              sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::BlessedObject::Array");
            }
            else {
              const char* basic_type_name = basic_type->name;
              SV* sv_basic_type_name = sv_2mortal(newSVpv(basic_type_name, 0));
              sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_basic_type_name));
            }
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
        }
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array type at %s line %d\n", MFILE, __LINE__);
  }

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
array_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array object or SPVM::BlessedObject::Sgtring
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Data must be SPVM::BlessedObject::Array at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  SV* sv_bin;
  if (is_array_type) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    int32_t element_type_dimension = dimension - 1;

    if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY) {
      SPVM_PACKAGE* package = basic_type->package;
      assert(package);
      
      SPVM_FIELD* first_field = SPVM_LIST_fetch(package->fields, 0);
      assert(first_field);

      int32_t field_length = package->fields->length;

      switch (first_field->type->basic_type->id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        default:
          croak("Invalid type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY) {
      croak("Objec type is not supported at %s line %d\n", MFILE, __LINE__);
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        default:
          croak("Invalid type at %s line %d\n", MFILE, __LINE__);
      }
    }
  }
  else {
    croak("Argument must be array type at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_bin);
  XSRETURN(1);
}

SV*
string_object_to_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_string = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // String must be SPVM::BlessedObject::String or SPVM::BlessedObject::String
  if (!(SvROK(sv_string) && sv_derived_from(sv_string, "SPVM::BlessedObject::String"))) {
    croak("String must be SPVM::BlessedObject::String object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* string = SPVM_XS_UTIL_get_object(sv_string);
  
  int32_t length = env->length(env, string);
  const char* chars = env->get_chars(env, string);

  SV* sv_return_value = sv_2mortal(newSVpv(chars, length));

  sv_utf8_decode(sv_return_value);

  XPUSHs(sv_return_value);
  XSRETURN(1);
}

SV*
array_length(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Array must be SPVM::BlessedObject::Array object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);


  SV* sv_length = sv_2mortal(newSViv(length));
  
  XPUSHs(sv_length);
  XSRETURN(1);
}

SV*
array_set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);
  SV* sv_value = ST(3);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->length(env, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;

  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        // Value
        int8_t value = (int8_t)SvIV(sv_value);
        
        // Set element
        int8_t* elements = env->get_elems_byte(env, array);
        
        elements[index] = value;
        
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        // Value
        int16_t value = (int16_t)SvIV(sv_value);
        
        // Set element
        int16_t* elements = env->get_elems_short(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        // Value
        int32_t value = (int32_t)SvIV(sv_value);
        
        // Set element
        int32_t* elements = env->get_elems_int(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        // Value
        int64_t value = (int64_t)SvIV(sv_value);
        
        // Set element
        int64_t* elements = env->get_elems_long(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        // Value
        float value = (float)SvNV(sv_value);
        
        // Set element
        float* elements = env->get_elems_float(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        // Value
        double value = (double)SvNV(sv_value);
        
        // Set element
        double* elements = env->get_elems_double(env, array);
        
        elements[index] = value;
        break;
      }
      default: {
        // Get object
        SPVM_OBJECT* value = SPVM_XS_UTIL_get_object(sv_value);
        
        env->set_elem_object(env, array, index, value);
      }
    }
  }
  else if (dimension > 1) {
    
    // Get object
    SPVM_OBJECT* value = SPVM_XS_UTIL_get_object(sv_value);
    
    env->set_elem_object(env, array, index, value);
  }
  else {
    assert(0);
  }
  
  XSRETURN(0);
}

SV*
array_get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->length(env, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;

  SV* sv_value = NULL;
  _Bool is_object = 0;
  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        // Get element
        int8_t* elements = env->get_elems_byte(env, array);
        int8_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        // Get element
        int16_t* elements = env->get_elems_short(env, array);
        int16_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        // Get element
        int32_t* elements = env->get_elems_int(env, array);
        int32_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        // Get element
        int64_t* elements = env->get_elems_long(env, array);
        int64_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        // Get element
        float* elements = env->get_elems_float(env, array);
        float value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        // Get element
        double* elements = env->get_elems_double(env, array);
        double value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      default:
        is_object = 1;
    }
  }
  else if (dimension > 1) {
    is_object = 1;
  }
  else {
    assert(0);
  }
  
  if (is_object) {
    SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
    
    // Element dimension
    int32_t element_dimension = array->type_dimension - 1;
    
    // Element type id
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, array->basic_type_id);

    // Index
    SPVM_OBJECT* value = env->get_elem_object(env, array, index);
    if (value != NULL) {
      env->inc_ref_count(env, value);
    }
    
    if (element_dimension == 0) {
      SV* sv_basic_type_name = sv_2mortal(newSVpv("SPVM::", 0));
      sv_catpv(sv_basic_type_name, basic_type->name);
      
      sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_basic_type_name));
    }
    else if (element_dimension > 0) {
      sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::Data::Array");
    }
  }
  
  XPUSHs(sv_value);
  XSRETURN(1);
}


MODULE = SPVM		PACKAGE = SPVM
