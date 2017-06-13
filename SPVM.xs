#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
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
  SV* sv_compiler = ST(0);
  
  HV* hv_compiler = (HV*)SvRV(sv_compiler);
  
  // Add package
  SV** sv_package_infos_ptr = hv_fetch(hv_compiler, "package_infos", strlen("package_infos"), 0);
  SV* sv_package_infos = sv_package_infos_ptr ? *sv_package_infos_ptr : &PL_sv_undef;
  AV* av_package_infos = (AV*)SvRV(sv_package_infos);
  int32_t av_package_infos_length = av_len(av_package_infos) + 1;
  for (int32_t i = 0; i < av_package_infos_length; i++) {
    SV* sv_package_info = av_fetch(av_package_infos, i, FALSE);
  }
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  SPVM_ARRAY_push(compiler->include_pathes, "lib");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    croak("SPVM compile error %d", compiler->error_count);
  }

  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(runtime);

  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM
