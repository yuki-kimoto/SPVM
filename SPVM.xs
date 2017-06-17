#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_data_api.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_my_var.h"
#include "spvm_type.h"
#include "spvm_resolved_type.h"

MODULE = SPVM::Compiler		PACKAGE = SPVM::Compiler

SV*
compile(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  SV* sv_spvm = ST(1);

  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();

  HV* hv_self = (HV*)SvRV(sv_self);
  HV* hv_spvm = (HV*)SvRV(sv_spvm);

  // Add package
  AV* av_package_infos = get_av("SPVM::PACKAGE_INFOS", 0);;
  int32_t av_package_infos_length = (int32_t)av_len(av_package_infos) + 1;
  for (int32_t i = 0; i < av_package_infos_length; i++) {
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
    SPVM_OP* op_use_package = SPVM_OP_new_op_use_from_package_name(compiler, name, file, line);
    SPVM_ARRAY_push(compiler->op_use_stack, op_use_package);
    SPVM_HASH_insert(compiler->op_use_symtable, name, strlen(name), op_use_package);
  }
  
  // Add include paths
  SV** sv_include_paths_ptr = hv_fetch(hv_spvm, "include_paths", strlen("include_paths"), 0);
  SV* sv_include_paths = sv_include_paths_ptr ? *sv_include_paths_ptr : &PL_sv_undef;
  AV* av_include_paths = (AV*)SvRV(sv_include_paths);
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  for (int32_t i = 0; i < av_include_paths_length; i++) {
    SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
    SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
    char* include_path = SvPV_nolen(sv_include_path);
    SPVM_ARRAY_push(compiler->include_pathes, include_path);
  }
  
  // Compile SPVM
  SPVM_COMPILER_compile(compiler);
  if (compiler->error_count > 0) {
    croak("SPVM compile error %d", compiler->error_count);
  }
  
  // Set compiler
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler_object = sv_2mortal(newRV_inc(sviv_compiler));
  hv_store(hv_self, "object", strlen("object"), SvREFCNT_inc(sv_compiler_object), 0);

  XSRETURN(0);
}

SV*
build_sub_infos(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Get compiler
  SV** sv_compiler_object_ptr = hv_fetch(hv_self, "object", strlen("object"), 0);
  SV* sv_compiler_object = sv_compiler_object_ptr ? *sv_compiler_object_ptr : &PL_sv_undef;
  SV* sviv_compiler = SvROK(sv_compiler_object) ? SvRV(sv_compiler_object) : sv_compiler_object;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Subroutine information
  HV* hv_sub_table = (HV*)sv_2mortal((SV*)newHV());
  
  // abs_name, arg_types, return_type, constant_pool_index, resolved_type_id
  SPVM_ARRAY* op_packages = compiler->op_packages;
  for (int32_t package_index = 0; package_index < op_packages->length; package_index++) {
    SPVM_OP* op_package = SPVM_ARRAY_fetch(op_packages, package_index);
    SPVM_ARRAY* op_subs = op_package->uv.package->op_subs;
    for (int32_t sub_index = 0; sub_index < op_subs->length; sub_index++) {
      // Sub information
      AV* av_sub_info = (HV*)sv_2mortal((SV*)newAV());
      
      SPVM_OP* op_sub = SPVM_ARRAY_fetch(op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      const char* sub_abs_name = sub->abs_name;
      
      // 1. Push subroutine name
      SV* sv_sub_abs_name = sv_2mortal(newSVpv(sub_abs_name, 0));
      av_push(av_sub_info, SvREFCNT_inc(sv_sub_abs_name));
      
      // arg_resolved_type_ids
      AV* av_arg_resolved_type_ids = (AV*)sv_2mortal((SV*)newAV());
      SPVM_ARRAY* op_args = sub->op_args;
      for (int32_t arg_index = 0; arg_index < op_args->length; arg_index++) {
        SPVM_OP* op_arg = SPVM_ARRAY_fetch(op_args, arg_index);
        SPVM_OP* op_arg_type = op_arg->uv.my_var->op_type;
        int32_t arg_resolved_type_id = op_arg_type->uv.type->resolved_type->id;
        
        SV* sv_arg_resolved_type_id = sv_2mortal(newSViv(arg_resolved_type_id));
        av_push(av_arg_resolved_type_ids, SvREFCNT_inc(sv_arg_resolved_type_id));
        SV* sv_arg_resolved_type_ids = sv_2mortal(newRV_inc((SV*)av_arg_resolved_type_ids));
        
        // 2. Push argment resolved type ids
        av_push(av_sub_info, SvREFCNT_inc(sv_arg_resolved_type_ids));
      }
      
      // Return type
      SPVM_OP* op_return_type = sub->op_return_type;
      SPVM_RESOLVED_TYPE* return_type_resolved_type = SPVM_OP_get_resolved_type(compiler, op_return_type);
      if (return_type_resolved_type) {
        int32_t return_resolved_type_id = op_return_type->uv.type->resolved_type->id;
        SV* sv_return_resolved_type_id = sv_2mortal(newSViv(return_resolved_type_id));
        // 3. Push return type resolved id
        av_push(av_sub_info, SvREFCNT_inc(sv_return_resolved_type_id));
      }
      else {
        av_push(av_sub_info, &PL_sv_undef);
      }
      
      int32_t constant_pool_index = sub->constant_pool_index;
      SV* sv_constant_pool_index = sv_2mortal(newSViv(constant_pool_index));
      
      SV* sv_sub_info = sv_2mortal(newRV_inc((SV*)av_sub_info));
      hv_store_ent(hv_sub_table, sv_constant_pool_index, SvREFCNT_inc(sv_sub_info), 0);
    }
  }
  
  SV* sv_sub_table = sv_2mortal(newRV_inc(hv_sub_table));
  
  sv_setsv(get_sv("SPVM::SUB_TABLE", 0), sv_sub_table);
  
  XSRETURN(0);
}

SV*
build_runtime(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  SV* sv_runtime = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  HV* hv_runtime = (HV*)SvRV(sv_runtime);
  
  // Get compiler
  SV** sv_compiler_object_ptr = hv_fetch(hv_self, "object", strlen("object"), 0);
  SV* sv_compiler_object = sv_compiler_object_ptr ? *sv_compiler_object_ptr : &PL_sv_undef;
  SV* sviv_compiler = SvROK(sv_compiler_object) ? SvRV(sv_compiler_object) : sv_compiler_object;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Runtime
  size_t iv_runtime = PTR2IV(runtime);
  SV* sviv_runtime = sv_2mortal(newSViv(iv_runtime));
  SV* sv_runtime_object = sv_2mortal(newRV_inc(sviv_runtime));
  
  XPUSHs(sv_runtime_object);
  XSRETURN(1);
}

SV*
DESTROY(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Get compiler
  SV** sv_compiler_object_ptr = hv_fetch(hv_self, "object", strlen("object"), 0);
  SV* sv_compiler_object = sv_compiler_object_ptr ? *sv_compiler_object_ptr : &PL_sv_undef;
  SV* sviv_compiler = SvROK(sv_compiler_object) ? SvRV(sv_compiler_object) : sv_compiler_object;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Set undef to compiler
  hv_store(hv_self, "object", strlen("object"), &PL_sv_undef, 0);
  
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM

SV*
int(...)
  PPCODE:
{
  SV* sv_value = ST(0);
  
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
call_sub(...)
  PPCODE:
{
  SV* sv_sub_constant_pool_index = ST(0);
  
  SV* sv_sub_table = get_sv("SPVM::SUB_TABLE", 0);
  HV* hv_sub_table = (HV*)SvRV(sv_sub_table);
  int32_t sub_constant_pool_index = (int32_t)SvIV(sv_sub_constant_pool_index);
  
  // Get runtime
  SV* sv_runtime = get_sv("SPVM::RUNTIME", 0);
  SV* sviv_runtime = SvROK(sv_runtime) ? SvRV(sv_runtime) : sv_runtime;
  size_t iv_runtime = SvIV(sviv_runtime);
  SPVM_RUNTIME* runtime = INT2PTR(SPVM_RUNTIME*, iv_runtime);
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(runtime);
  
  for (int32_t arg_index = 1; arg_index < items; arg_index++) {
    SPVM_RUNTIME_API_push_var_int(runtime, (int32_t)SvIV(ST(arg_index)));
  }
  
  SPVM_RUNTIME_call_sub(runtime, sub_constant_pool_index);
  
  int32_t ret = SPVM_RUNTIME_API_pop_return_value_int(runtime);
  
  SV* sv_ret = sv_2mortal(newSViv(ret));
  
  XPUSHs(sv_ret);
  XSRETURN(1);
}
