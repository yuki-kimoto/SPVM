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

MODULE = SPVM::Compiler		PACKAGE = SPVM::Compiler

SV*
compile(...)
  PPCODE:
{
  SV* sv_self = ST(0);

  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();

  HV* hv_self = (HV*)SvRV(sv_self);

  // Add package
  SV** sv_package_infos_ptr = hv_fetch(hv_self, "package_infos", strlen("package_infos"), 0);
  SV* sv_package_infos = sv_package_infos_ptr ? *sv_package_infos_ptr : &PL_sv_undef;
  AV* av_package_infos = (AV*)SvRV(sv_package_infos);
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
  SV** sv_include_paths_ptr = hv_fetch(hv_self, "include_paths", strlen("include_paths"), 0);
  SV* sv_include_paths = sv_include_paths_ptr ? *sv_include_paths_ptr : &PL_sv_undef;
  AV* av_include_paths = (AV*)SvRV(sv_include_paths);
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  for (int32_t i = 0; i < av_include_paths_length; i++) {
    SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
    SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
    const char* include_path = SvPV_nolen(sv_include_path);
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
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  hv_store(hv_self, "compiler", strlen("compiler"), SvREFCNT_inc(sv_compiler), 0);
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(runtime);
  
  XSRETURN(0);
}

SV*
DESTROY(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;

  // デリファレンス
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  
  // SV*型をsize_t型に変換
  size_t iv_compiler = SvIV(sviv_compiler);
  
  // size_t型をポインタに変換
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Set undef to compiler
  hv_store(hv_self, "compiler", strlen("compiler"), &PL_sv_undef, 0);
  
  XSRETURN(0);
}

MODULE = SPVM::Runtime		PACKAGE = SPVM::Runtime

MODULE = SPVM		PACKAGE = SPVM
